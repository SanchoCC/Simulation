#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include <list>

class Object {
public:

	Object(bool Collision, bool Static, double Mass, int Sides, double Radius, float PositionX, float PositionY);

	void Move(double AccelerationX, double AccelerationY, double deltaTime);

	void Render();
	std::vector<std::pair<float, float>> Angles;

	double VelocityX = 0;
	double VelocityY = 0;

protected:
	bool Collision;
	bool Static;

	int Sides;
	float Radius;

	double Mass;

	float PositionX = 0;
	float PositionY = 0;

	

	double Energy = 0; 

	float Color_Red;
	float Color_Green;
	float Color_Blue;

	

};