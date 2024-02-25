#ifndef SIMULATION_CLASSES_OBJECT_H_
#define SIMULATION_CLASSES_OBJECT_H_

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include <list>
#include <vector>
#include <memory>

class Object {
public:
	Object(bool Collision, bool Static, float PositionX, float PositionY);

	virtual ~Object();
	
	std::vector<glm::vec2> Angles;

protected:
	bool Collision;
	bool Static;

	double VelocityX = 0;
	double VelocityY = 0;
	double Mass = 0;		
	double Energy = 0; 
	double RotationAngle = 0;

	float PositionX = 0;
	float PositionY = 0;

	struct Color {
		Color()
		{
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_real_distribution<float> color_dist(0.0f, 1.0f);
			this->Red = color_dist(rng);
			this->Green = color_dist(rng);
			this->Blue = color_dist(rng);
		}
		float Red;
		float Green;
		float Blue;
	};
	Color Color;

	static std::list<std::shared_ptr<Object>> ObjectsList;
private:
	void GravityAcceleration(double deltaTime);
	void Move(double deltaTime);
	virtual void Render() = 0;
public:
	static void ObjectsMain(double deltaTime);
};

#endif // !SIMULATION_CLASSES_OBJECT_H_