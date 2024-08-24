#include "color.h"

#include <random>

Color::Color() {
	SetRandomColor();
}

Color::Color(float red, float green, float blue) {
	SetColor(red, green, blue);
}

Color::Color(glm::vec3 color) {
	this->color_ = color;
}

void Color::SetRandomColor() {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> color_dist(0.5f, 1.0f);
	float red = color_dist(rng);
	float green = color_dist(rng);
	float blue = color_dist(rng);
	this->color_ = glm::vec3 (red, green, blue);
}

void Color::SetColor(float red, float green, float blue) {
	float red_ = red;
	float green_ = green;
	float blue_ = blue;
	this->color_ = glm::vec3(red, green, blue);
}

void Color::SetColor(glm::vec3 color) {
	this->color_ = color;
}

glm::vec3 Color::GetColor() const {
	return color_;
}