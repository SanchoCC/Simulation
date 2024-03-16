#include "object_handler.h"

void ObjectHandler::MainCycle(std::list<std::shared_ptr<Object>>& object_list, float delta_time) {
    for (auto it = object_list.begin(); it != object_list.end(); ++it) {
        auto first = it->get();        
       
        for (auto inner_it = std::next(it); inner_it != object_list.end(); ++inner_it) {

            auto second = inner_it->get();
            if (CheckCollision(first, second)) {
                HandleCollision(first, second, delta_time);
            }
        }
        Accelerate(first, 0, kGravity, delta_time);
        Move(first, delta_time);
        first->Render();
    }
}

void ObjectHandler::Move(Object* object, float delta_time) {
    if (object->GetStatical()) {
        object->SetVelocity(0, 0);
    } else {
        object->AddPosition(object->GetVelocity().first * delta_time, object->GetVelocity().second * delta_time);       
    }
}

void ObjectHandler::Accelerate(Object* object, float acceleration_x, float acceleration_y, float delta_time) {
    object->AddVelocity(acceleration_x*delta_time, acceleration_y*delta_time);
}

bool ObjectHandler::CheckCollision(Object* first, Object* second) const {
    if (first->GetType() == ShapeType::kRectangle || second->GetType() == ShapeType::kRectangle) {
        return SATCollision(first, second)>0;
    } else if (first->GetType() == ShapeType::kCircle && second->GetType() == ShapeType::kCircle) {
            glm::vec2 first_glm_position(first->GetPosition().first, first->GetPosition().second);
            glm::vec2 second_glm_position(second->GetPosition().first, second->GetPosition().second);

            float distance = glm::distance(first_glm_position, second_glm_position);
            float sum_radius = first->GetRadius() + second->GetRadius();
            return distance <= sum_radius;
    }
    return false;
}

float ObjectHandler::SATCollision(Object* first, Object* second) const {
    auto calculateAxes = [](const std::vector<std::pair<float, float>>& vertices) {
        std::vector<glm::vec2> axes;
        for (size_t i = 0; i < vertices.size(); ++i) {
            size_t j = (i + 1) % vertices.size();
            glm::vec2 edge = glm::vec2(vertices[j].first - vertices[i].first, vertices[j].second - vertices[i].second);
            axes.push_back(glm::normalize(glm::vec2(-edge.y, edge.x)));
        }
        return axes;
    };

    auto vertices1 = first->GetVertices();
    auto vertices2 = second->GetVertices();
    std::vector<glm::vec2> axes1 = calculateAxes(vertices1);
    std::vector<glm::vec2> axes2 = calculateAxes(vertices2);

    float minOverlap = std::numeric_limits<float>::max();

    for (const auto& axis : axes1) {
        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::min();
        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::min();

        for (const auto& vertex : vertices1) {
            float projection = glm::dot(glm::vec2(vertex.first, vertex.second), axis);
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        for (const auto& vertex : vertices2) {
            float projection = glm::dot(glm::vec2(vertex.first, vertex.second), axis);
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        float overlap = glm::min(max1, max2) - glm::max(min1, min2);
        if (overlap < 0) {
            return 0.0f;
        }

        minOverlap = glm::min(minOverlap, overlap);
    }

    for (const auto& axis : axes2) {
        float min1 = std::numeric_limits<float>::max();
        float max1 = std::numeric_limits<float>::min();
        float min2 = std::numeric_limits<float>::max();
        float max2 = std::numeric_limits<float>::min();

        for (const auto& vertex : vertices1) {
            float projection = glm::dot(glm::vec2(vertex.first, vertex.second), axis);
            min1 = std::min(min1, projection);
            max1 = std::max(max1, projection);
        }

        for (const auto& vertex : vertices2) {
            float projection = glm::dot(glm::vec2(vertex.first, vertex.second), axis);
            min2 = std::min(min2, projection);
            max2 = std::max(max2, projection);
        }

        float overlap = glm::min(max1, max2) - glm::max(min1, min2);
        if (overlap < 0) {         
            return 0.0f;
        }

        minOverlap = glm::min(minOverlap, overlap);
    }

    return minOverlap;
}

void ObjectHandler::HandleCollision(Object* first, Object* second, float delta_time) {

    float first_mass = first->GetMass();
    float second_mass = second->GetMass();
    std::pair<float, float> velocity1 = first->GetVelocity();
    std::pair<float, float> velocity2 = second->GetVelocity();    
    float penetration_depth = SATCollision(first, second);

    if (penetration_depth > 0.001f) {
        SeparateObjects(first, second, penetration_depth, delta_time);
    }
    if (first->GetStatical() || second->GetStatical()) {
        Move(first, -delta_time);
        Move(second, -delta_time);

        float restitution_sum = 0.5f * first->GetRestitution() + second->GetRestitution();

        first->SetVelocity(((first_mass - second_mass) * velocity1.first + 2 * second_mass * velocity2.first) / (first_mass + second_mass) * -restitution_sum,
            ((first_mass - second_mass) * velocity1.second + 2 * second_mass * velocity2.second) / (first_mass + second_mass) * restitution_sum);
        second->SetVelocity(((second_mass - first_mass) * velocity2.first + 2 * first_mass * velocity1.first) / (first_mass + second_mass) * -restitution_sum,
            ((second_mass - first_mass) * velocity2.second + 2 * first_mass * velocity1.second) / (first_mass + second_mass) * restitution_sum);
    }
    else {
        
        float relative_velocity_x = velocity2.first - velocity1.first;
        float relative_velocity_y = velocity2.second - velocity1.second;

        glm::vec2 normal = glm::normalize(glm::vec2(second->GetPosition().first - first->GetPosition().first, second->GetPosition().second - first->GetPosition().second));

        float vel_along_normal = relative_velocity_x * normal.x + relative_velocity_y * normal.y;

        if (vel_along_normal > 0)
            return;

        float Restitution1 = first->GetRestitution();
        float Restitution2 = second->GetRestitution();

        float j = -(1 + std::min(Restitution1, Restitution2)) * vel_along_normal;
        j /= 1 / first_mass + 1 / second_mass;

        glm::vec2 impulse = j * normal;

        first->AddVelocity(-impulse.x / first_mass, -impulse.y / first_mass);
        second->AddVelocity(impulse.x / second_mass, impulse.y / second_mass);
    }
}

void ObjectHandler::SeparateObjects(Object* first, Object* second, float penetration_depth, float delta_time) {
    glm::vec2 normal = glm::normalize(glm::vec2(second->GetPosition().first - first->GetPosition().first, second->GetPosition().second - first->GetPosition().second));
    float separation_distance = penetration_depth;
    if (!first->GetStatical()) {
        first->AddPosition(-separation_distance * normal.x, -separation_distance * normal.y);
    }
    if (!second->GetStatical()) {
        second->AddPosition(separation_distance * normal.x, separation_distance * normal.y);
    }
}
