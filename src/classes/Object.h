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
	static std::list<std::shared_ptr<Object>> ObjectsList;

	bool Collision;
	bool Static;

	double VelocityX = 0;
	double VelocityY = 0;
	double Mass = 0;		
	double RotationAngle = 0;

	float PositionX = 0;
	float PositionY = 0;

	struct Color {
		Color();
		Color(float Red, float Green, float Blue);
		void SetRandomColor();
		void SetColor(float Red, float Green, float Blue);
		float Red;
		float Green;
		float Blue;
	};
	Color Color;
private:
	void GravityAcceleration(double deltaTime);
	void Move(double deltaTime);
	virtual void Render() = 0;
public:
	static void ObjectsMain(double deltaTime);
};

#endif // !SIMULATION_CLASSES_OBJECT_H_