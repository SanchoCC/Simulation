#include "object_shapes.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>

Circle::Circle(bool statical, float position_x, float position_y, float radius) : Object(statical, position_x, position_y) {
	radius_ = radius;
	if (statical_) {
		mass_ = inverted_mass_ = inertia_ = inverted_inertia_ = 0.0f;
	} else {
		mass_ = M_PI * radius * radius * density_;
		inverted_mass_ = 1.0f / mass_;
		inertia_ = 0.5f * mass_ * radius_;
		inverted_inertia_ = 1.0f / inertia_;
	}
	UpdateVertices();
	Render();
	objects_list_.push_back(this);
}
Circle::Circle() {
	statical_ = 0;
	position_ = glm::vec2(0, 1);
	radius_ = 0.1f;
	if (statical_) {
		mass_ = inverted_mass_ = inertia_ = inverted_inertia_ = 0.0f;
	} else {
		mass_ = M_PI * radius_ * radius_ * density_;
		inverted_mass_ = 1.0f / mass_;
		inertia_ = 0.5f * mass_ * radius_;
		inverted_inertia_ = 1.0f / inertia_;
	}
	UpdateVertices();
	Render();
	objects_list_.push_back(this);
}

Circle::~Circle() = default;

ShapeType Circle::GetType() const {
	return ShapeType::kCircle;
}

void Circle::Render() const {
	Object::Render();

	glColor3f(color_.red_ / 1.5f, color_.green_ / 1.5f, color_.blue_ / 1.5f);
	glBegin(GL_TRIANGLES);
	glVertex2f(position_.x, position_.y);
	glVertex2f(vertices_[0].x, vertices_[0].y);
	glVertex2f(vertices_[1].x, vertices_[1].y);
	glEnd();
}

void Circle::UpdateVertices() {
	vertices_.clear();

	float koef = 1.0f;
	if (radius_ < 1.0f) {
		koef = radius_;
	} else {
		koef += std::logf(radius_) / std::logf(100.0f);
	}
	int sides = kCircleSides * (koef + kMinSidesKoef);
	for (int i = 0; i < sides; ++i) {
		float theta = 2.0f * M_PI * i / sides + rotation_angle_;
		vertices_.push_back(glm::vec2(radius_ * cosf(theta) + position_.x, radius_ * sinf(theta) + position_.y));
	}
}

float Circle::GetRadius() const {
	return radius_;
}

Rectangle::Rectangle(bool statical, float position_x, float position_y, float width, float height) : Object(statical, position_x, position_y) {
	width_ = width;
	height_ = height;
	if (statical_) {
		mass_ = inverted_mass_ = inertia_ = inverted_inertia_ = 0.0f;
	} else {
		mass_ = (width_ * height_) * density_;
		inverted_mass_ = 1.0f / mass_;
		inertia_ = 1.0f / 12.0f * mass_ * (width * width + height * height);
		inverted_inertia_ = 1.0f / inertia_;
	}
	UpdateVertices();
	Render();
	objects_list_.push_back(this);
}

Rectangle::~Rectangle() = default;

ShapeType Rectangle::GetType() const {
	return ShapeType::kRectangle;
}

float Rectangle::GetWidth() const {
	return width_;
}

float Rectangle::GetHeight() const {
	return height_;
}

void Rectangle::UpdateVertices() {
	vertices_.clear();
	normals_.clear();
	std::vector<glm::vec2> original_vertices = {
		glm::vec2(-width_ / 2.0f, -height_ / 2.0f),
		glm::vec2(width_ / 2.0f, -height_ / 2.0f),
		glm::vec2(width_ / 2.0f, height_ / 2.0f),
		glm::vec2(-width_ / 2.0f, height_ / 2.0f)
	};
	std::vector<glm::vec2> original_normals = {
		glm::vec2(0.0f, -1.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(-1.0f, 0.0f)
	};
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position_, 0.0f));
	model = glm::rotate(model, rotation_angle_, glm::vec3(0.0f, 0.0f, 1.0f));
	for (const auto& it : original_vertices) {
		glm::vec4 vertex = glm::vec4(it, 0.0f, 1.0f);
		vertex = model * vertex;
		vertices_.push_back(glm::vec2(vertex.x, vertex.y));
	}
	for (const auto& it : original_normals) {
		glm::vec4 normal = glm::vec4(it, 0.0f, 1.0f);
		normal = model * normal;
		normals_.push_back(glm::vec2(normal.x, normal.y));
	}
}
