#pragma once
#ifndef SIMULATION_CLASSES_OBJECT_H_
#define SIMULATION_CLASSES_OBJECT_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include <list>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include <iostream>

class Object {
public:
	Object(bool Collision, bool Static, float PositionX, float PositionY);
	virtual ~Object();

	static void ObjectsMain(double deltaTime);

	std::vector<std::pair<float, float>> Angles;	
protected:
	static std::list<std::shared_ptr<Object>> ObjectsList;

	bool Collision;
	bool Static;
	bool IsRectangle = false;	
	
	float Mass = 0;
	float VelocityX = 0;
	float VelocityY = 0;
	float RotationAngle = 0;
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
public:
	Color Color;
private:
	void GravityAcceleration(double deltaTime);
	void Move(double deltaTime);

	virtual void Render() = 0;
	virtual bool CheckCollision(const std::shared_ptr <Object>& Other) = 0;
public:
	bool GetIsRectangle();
	double GetRotationAngle();
};

#endif // !SIMULATION_CLASSES_OBJECT_H_