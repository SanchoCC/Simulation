#include "object_shapes.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <random>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "object_handler.h"

Circle::Circle(float position_x, float position_y, float radius, MaterialType material_type) : Object(position_x, position_y, material_type) {
	radius_ = radius;
	CalculateMass();
	UpdateVertices();
	ObjectHandler::Get().AddInObjects(this);
}

Circle::~Circle() = default;

void Circle::Render() const {
	Object::Render();

	glColor3f(material_.GetColor().GetRed() * 0.5f, material_.GetColor().GetGreen() * 0.5f, material_.GetColor().GetBlue() * 0.5f);
	glBegin(GL_TRIANGLES);
	glVertex2f(position_.x, position_.y);
	glVertex2f(vertices_[0].x, vertices_[0].y);
	glVertex2f(vertices_[1].x, vertices_[1].y);
	glEnd();
}

ShapeType Circle::GetType() const {
	return ShapeType::kCircle;
}

void Circle::CalculateMass() {
	if (statical_) {
		inverted_mass_ = inverted_inertia_ = 0.0f;
	} else {
		float mass_ = M_PI * radius_ * radius_ * material_.GetDensity();
		inverted_mass_ = 1.0f / mass_;
		float inertia_ = 0.5f * mass_ * radius_;
		inverted_inertia_ = 1.0f / inertia_;
	}
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

Rectangle::Rectangle(float position_x, float position_y, float width, float height, MaterialType material_type) : Object(position_x, position_y, material_type) {
	width_ = width;
	height_ = height;
	CalculateMass();
	UpdateVertices();
	ObjectHandler::Get().AddInObjects(this);
}

Rectangle::~Rectangle() = default;

ShapeType Rectangle::GetType() const {
	return ShapeType::kRectangle;
}

void Rectangle::CalculateMass() {
	if (statical_) {
		inverted_mass_ = inverted_inertia_ = 0.0f;
	} else {
		float mass_ = (width_ * height_) * material_.GetDensity();
		inverted_mass_ = 1.0f / mass_;
		float inertia_ = 1.0f / 12.0f * mass_ * (width_ * width_ + height_ * height_);
		inverted_inertia_ = 1.0f / inertia_;
	}
}

float Rectangle::GetWidth() const {
	return width_;
}

float Rectangle::GetHeight() const {
	return height_;
}

void Rectangle::UpdateVertices() {
	vertices_.clear();
	std::vector<glm::vec2> original_vertices = {
		glm::vec2(-width_ / 2.0f, -height_ / 2.0f),
		glm::vec2(width_ / 2.0f, -height_ / 2.0f),
		glm::vec2(width_ / 2.0f, height_ / 2.0f),
		glm::vec2(-width_ / 2.0f, height_ / 2.0f)
	};
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position_, 0.0f));
	model = glm::rotate(model, rotation_angle_, glm::vec3(0.0f, 0.0f, 1.0f));
	for (const auto& it : original_vertices) {
		glm::vec4 vertex = glm::vec4(it, 0.0f, 1.0f);
		vertex = model * vertex;
		vertices_.push_back(glm::vec2(vertex.x, vertex.y));
	}
}
