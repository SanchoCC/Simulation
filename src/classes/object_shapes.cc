#include "object_shapes.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>
#include <random>

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Circle::Circle(float position_x, float position_y, float radius, MaterialType material_type) : Object(position_x, position_y, material_type) {
	radius_ = radius;
	CalculateMass();
	UpdateVertices();
	Render();
	objects_list_.push_back(this);
}

Circle::Circle() {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> position_x_dist(-0.5f, 0.5f);
	std::uniform_real_distribution<float> position_y_dist(1.f, 2.f);
	position_ = glm::vec2(position_x_dist(rng), position_y_dist(rng));
	std::uniform_real_distribution<float> radius_dist(0.03f, 0.3f);
	radius_ = radius_dist(rng);
	std::uniform_real_distribution<float> angular_velocity_dist(-1.f, 1.f);
	SetAngularVelocity(angular_velocity_dist(rng));
	std::uniform_real_distribution<float> velocity_x_dist(-0.2f, 0.2f);
	std::uniform_real_distribution<float> velocity_y_dist(-0.2f, 0.2f);
	SetVelocity(glm::vec2(velocity_x_dist(rng), velocity_y_dist(rng)));
	std::uniform_int_distribution<int> material_dist(0, 5);
	SetMaterial(static_cast<MaterialType>(material_dist(rng)));
	CalculateMass();
	UpdateVertices();
	Render();
	objects_list_.push_back(this);
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
	Render();
	objects_list_.push_back(this);
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
