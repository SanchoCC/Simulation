#include "color.h"

#include <random>

Color::Color() {
	SetRandomColor();
}

Color::Color(float red, float green, float blue) {
	SetColor(red, green, blue);
}

void Color::SetRandomColor() {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> color_dist(0.5f, 1.0f);
	this->red_ = color_dist(rng);
	this->green_ = color_dist(rng);
	this->blue_ = color_dist(rng);
}

void Color::SetColor(float red, float green, float blue) {
	this->red_ = red;
	this->green_ = green;
	this->blue_ = blue;
}