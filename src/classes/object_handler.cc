#include "object_handler.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <glm/gtc/matrix_transform.hpp>

#include "math_defines.h"
#include "object_shapes.h"

ObjectHandler& ObjectHandler::Get() {
	static ObjectHandler instance;

	return instance;
}

ObjectHandler::ObjectHandler() {}

ObjectHandler::~ObjectHandler() {
	for (auto it : created_objects_) {
		delete it;
	}
}

void ObjectHandler::MainCycle(float delta_time) {
	for (auto it = objects_.begin(); it != objects_.end(); ++it) {		
		auto object1 = *it;
		object1->Render();
		if (!object1->GetStatical()) {
			Accelerate(object1, glm::vec2{0.0f, gravity_}, delta_time);
			Rotate(object1, delta_time);
			Move(object1, delta_time);
		}
		for (auto inner_it = objects_.begin(); inner_it != objects_.end(); ++inner_it) {
			if (inner_it == it) {
				continue;
			}
			auto object2 = *inner_it;
			CollisionResult collision_result = CheckCollision(object1, object2);
			if (collision_result.contacts.size() > 0) {
				HandleCollision(object1, object2, collision_result);
				SeparateObjects(object1, object2, collision_result);
			}
		}
	}
}

void ObjectHandler::AddInObjects(Object* object) {
	objects_.push_back(object);
}

void ObjectHandler::AddInCreatedObjects(Object* object) {
	created_objects_.push_back(object);
}

void ObjectHandler::Move(Object* object, float delta_time) {
	object->AddPosition(object->GetVelocity() * delta_time);
}

void ObjectHandler::Rotate(Object* object, float delta_time) {
	object->AddRotationAngle(object->GetAngularVelocity() * delta_time);
	float rotation_angle = object->GetRotationAngle();
	if (rotation_angle > 2.0f * M_PI || rotation_angle < -2.0f * M_PI) {
		object->SetRotationAngle(rotation_angle - 2.0f * M_PI * 
			static_cast<float>(static_cast<int>(rotation_angle / (2.0f * M_PI))));
	}
}

void ObjectHandler::Accelerate(Object* object, glm::vec2 acceleration, float delta_time) {
	object->AddVelocity(acceleration * delta_time);
}

void ObjectHandler::ApplyImpulse(Object* object, glm::vec2 impulse, glm::vec2 contact_vector) {
	if (!object->GetStatical()) {
		object->AddVelocity(object->GetInvertedMass() * impulse);
		object->AddAngularVelocity(object->GetInvertedInertia() * sim::Cross2D(contact_vector, impulse));
	}
}

CollisionResult ObjectHandler::CheckCollision(const Object* object1, const Object* object2) const {
	ShapeType type_1 = object1->GetType();
	ShapeType type_2 = object2->GetType();
	switch (type_1)
	{
	case ShapeType::kRectangle:
		if (type_2 == ShapeType::kRectangle) {
			return SATCollision(object1, object2);
		} else if (type_2 == ShapeType::kCircle) {
			return CircleRectangle(object2, object1);
		}		
		break;
	case ShapeType::kCircle:
		if (type_2 == ShapeType::kRectangle) {
			return CircleRectangle(object1, object2);
		} else if (type_2 == ShapeType::kCircle) {
			return CircleCircle(object1, object2);
		}
		break;
	default:
		break;
	}
	return {};	
}

CollisionResult ObjectHandler::SATCollision(const Object* object1,
	const Object* object2) const {
	CollisionResult collision_result;
	auto calculateAxes = [](const std::vector<glm::vec2>& vertices) {
		std::vector<glm::vec2> axes;
		for (size_t i = 0; i < vertices.size(); ++i) {
			size_t j = (i + 1) % vertices.size();
			glm::vec2 edge = vertices[j] - vertices[i];
			axes.push_back(glm::normalize(glm::vec2(-edge.y, edge.x)));
		}
		return axes;
	};

	auto projectVertices = [](const std::vector<glm::vec2>& vertices,
		const glm::vec2& axis) {
			float minProjection = glm::dot(vertices[0], axis);
			float maxProjection = minProjection;
			for (size_t i = 1; i < vertices.size(); ++i) {
				float projection = glm::dot(vertices[i], axis);
				minProjection = std::min(minProjection, projection);
				maxProjection = std::max(maxProjection, projection);
			}
			return std::make_pair(minProjection, maxProjection);
	};

	auto vertices1 = object1->GetVertices();
	auto vertices2 = object2->GetVertices();
	glm::vec2 position1 = object1->GetPosition();
	glm::vec2 position2 = object2->GetPosition();
	std::vector<glm::vec2> axes1 = calculateAxes(vertices1);
	std::vector<glm::vec2> axes2 = calculateAxes(vertices2);

	float min_overlap = std::numeric_limits<float>::max();
	glm::vec2 normal{};
	bool found_collision = true;

	for (const auto& axis : axes1) {
		auto [min1, max1] = projectVertices(vertices1, axis);
		auto [min2, max2] = projectVertices(vertices2, axis);

		float overlap = glm::min(max1, max2) - glm::max(min1, min2);
		if (overlap < 0) {
			found_collision = false;
			break;
		}

		if (overlap < min_overlap) {
			min_overlap = overlap;
			normal = axis;
		}
	}

	if (found_collision) {
		for (const auto& axis : axes2) {
			auto [min1, max1] = projectVertices(vertices1, axis);
			auto [min2, max2] = projectVertices(vertices2, axis);

			float overlap = glm::min(max1, max2) - glm::max(min1, min2);
			if (overlap < 0) {
				found_collision = false;
				break;
			}

			if (overlap < min_overlap) {
				min_overlap = overlap;
				normal = axis;
			}
		}
	}

	if (!found_collision) {
		return {};
	}

	glm::vec2 closest_point{};
	float min_distance = std::numeric_limits<float>::max();
	for (const auto& vertex : vertices1) {
		float distance = glm::dot(vertex - position2, normal);
		if (distance < min_distance) {
			min_distance = distance;
			closest_point = vertex;
		}
	}

	collision_result.penetration = min_overlap;
	collision_result.normal = normal;
	collision_result.contacts.push_back(closest_point);

	return collision_result;
}

CollisionResult ObjectHandler::CircleCircle(const Object* object1,
	const Object* object2) const {
	CollisionResult result{};
	Circle* circle1 = static_cast<Circle*>(const_cast<Object*>(object1));
	Circle* circle2 = static_cast<Circle*>(const_cast<Object*>(object2));
	glm::vec2 normal = object2->GetPosition() - object1->GetPosition();

	float distance_pow2 = glm::dot(normal, normal);
	float radius = circle1->GetRadius() + circle2->GetRadius();

	if (distance_pow2 >= radius * radius) {
		return result;
	}

	float distance = std::sqrtf(distance_pow2);

	if (distance == 0.0f) {
		result.penetration = circle1->GetRadius();
		result.normal = glm::vec2(1, 0);
		result.contacts.push_back(object1->GetPosition());
	} else {
		result.penetration = radius - distance;
		result.normal = normal / distance;
		result.contacts.push_back(result.normal * circle1->GetRadius() +
			object1->GetPosition());
	}
	return result;
}

CollisionResult ObjectHandler::CircleRectangle(const Object* object1,
	const Object* object2) const {
	CollisionResult result{};

	Circle* circle = static_cast<Circle*>(const_cast<Object*>(object1));
	Rectangle* rectangle = static_cast<Rectangle*>(const_cast<Object*>(object2));

	glm::vec4 circle_position(circle->GetPosition(), 0.0f, 1.0f);
	glm::vec4 rectangle_position(rectangle->GetPosition(), 0.0f, 1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	float rotation2 = rectangle->GetRotationAngle();
	model = glm::translate(model, glm::vec3(rectangle_position));
	model = glm::rotate(model, rotation2, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 inverse_model = glm::inverse(model);

	glm::vec4 transformed_position = inverse_model * circle_position;
	glm::vec2 new_circle_position = glm::vec2(transformed_position);
	glm::vec2 new_rectangle_position = glm::vec2(0.0f, 0.0f);
	circle->SetPosition(new_circle_position);
	rectangle->SetPosition(new_rectangle_position);
	rectangle->SetRotationAngle(0.0f);

	glm::vec2 n = new_circle_position - new_rectangle_position;
	glm::vec2 closest = n;
	float x_extent = rectangle->GetWidth() * 0.5f;
	float y_extent = rectangle->GetHeight() * 0.5f;
	closest.x = sim::Clamp(-x_extent, x_extent, closest.x);
	closest.y = sim::Clamp(-y_extent, y_extent, closest.y);

	bool inside = false;

	if (n == closest) {
		inside = true;
		if (abs(n.x) > abs(n.y)) {
			closest.x = (closest.x > 0) ? x_extent : -x_extent;
		} else {
			closest.y = (closest.y > 0) ? y_extent : -y_extent;
		}
	}

	glm::vec2 normal = n - closest;
	float distance = glm::length(normal);
	float radius = circle->GetRadius();

	if (distance > radius && !inside) {
		circle->SetPosition(glm::vec2(circle_position));
		rectangle->SetPosition(glm::vec2(rectangle_position));
		rectangle->SetRotationAngle(rotation2);
		return result;
	}

	if (inside) {
		result.normal = -glm::normalize(normal);
		result.penetration = radius - distance;
	} else {
		result.normal = glm::normalize(normal);
		result.penetration = radius - distance;
	}

	glm::vec4 transformed_normal(result.normal, 0.0f, 0.0f);
	transformed_normal = model * transformed_normal;
	result.normal = glm::vec2(transformed_normal);

	glm::vec4 transformed_contact(closest, 0.0f, 1.0f);
	transformed_contact = model * transformed_contact;
	result.contacts.push_back(glm::vec2(transformed_contact));

	circle->SetPosition(glm::vec2(circle_position));
	rectangle->SetPosition(glm::vec2(rectangle_position));
	rectangle->SetRotationAngle(rotation2);

	return result;
}

void ObjectHandler::HandleCollision(Object* object1, Object* object2,
	CollisionResult collision_result) {
	if (object1->GetStatical() && object2->GetStatical()) {
		return;
	}
	for (int i = 0; i < collision_result.contacts.size(); ++i) {
		glm::vec2 collision_point = collision_result.contacts[i];

		glm::vec2 position1 = object1->GetPosition();
		glm::vec2 position2 = object2->GetPosition();

		glm::vec2 r1 = collision_point - position1;
		glm::vec2 r2 = collision_point - position2;

		glm::vec2 velocity1 = object1->GetVelocity();
		glm::vec2 velocity2 = object2->GetVelocity();

		float angular_velocity1 = object1->GetAngularVelocity();
		float angular_velocity2 = object2->GetAngularVelocity();

		glm::vec2 relative_velocity =
			velocity2 + sim::Cross2D(angular_velocity2, r2) - velocity1 -
			sim::Cross2D(angular_velocity1, r1);

		glm::vec2 normal = collision_result.normal;

		float vel_along_normal = glm::dot(relative_velocity, normal);

		if (vel_along_normal > 0) {
			return;
		}

		float r1_cross_normal = sim::Cross2D(r1, normal);
		float r2_cross_normal = sim::Cross2D(r2, normal);

		float inverse_mass_sum =
			object1->GetInvertedMass() + object2->GetInvertedMass() +
			(r1_cross_normal * r1_cross_normal) * object1->GetInvertedInertia() +
			(r2_cross_normal * r2_cross_normal) * object2->GetInvertedInertia();

		Material material1 = object1->GetMaterial();
		Material material2 = object2->GetMaterial();
		float restitution = (material1.GetRestitution() + material2.GetRestitution()) * 0.5f;

		float j = -(1.0f + restitution) * vel_along_normal;
		j /= inverse_mass_sum;
		j /= collision_result.contacts.size();

		glm::vec2 impulse = j * normal;

		ApplyImpulse(object1, -impulse, r1);
		ApplyImpulse(object2, impulse, r2);

		relative_velocity = velocity2 + sim::Cross2D(angular_velocity2, r2) -
			velocity1 - sim::Cross2D(angular_velocity1, r1);

		glm::vec2 tangent =
			relative_velocity - (normal * glm::dot(relative_velocity, normal));
		if (std::abs(glm::length(tangent)) > 0.0001f) {
			tangent = glm::normalize(tangent);

			float tangent_magnitude = -glm::dot(relative_velocity, tangent);
			tangent_magnitude /= inverse_mass_sum;
			tangent_magnitude /= collision_result.contacts.size();

			glm::vec2 tangent_impulse;
			float static_friction = (material1.GetStaticFriction() + material2.GetStaticFriction()) * 0.5f;
			float dynamic_friction = (material1.GetDynamicFriction() + material2.GetDynamicFriction()) * 0.5f;
			if (std::abs(tangent_magnitude) < j * static_friction) {
				tangent_impulse = tangent * tangent_magnitude;
			} else {
				tangent_impulse = tangent * -j * dynamic_friction;
			}

			ApplyImpulse(object1, -tangent_impulse, r1);
			ApplyImpulse(object2, tangent_impulse, r2);
		}
	}
}

void ObjectHandler::SeparateObjects(Object* object1, Object* object2,
	CollisionResult collision_result) {
	glm::vec2 normal = glm::normalize(collision_result.normal);
	float separation_distance = collision_result.penetration;
	if (!object1->GetStatical()) {
		object1->AddPosition(separation_distance/2 * -normal);
	}
	if (!object2->GetStatical()) {
		object2->AddPosition(separation_distance/2 * normal);
	}
}