#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#include <list>

class Object {
public:

	static int counter;

	Object(bool Collision, bool Static, double Mass, int Sides, double Radius, float PositionX, float PositionY);

	virtual ~Object();
	
	std::vector<glm::vec2> Angles;
	
	bool operator==(const Object& other) const {
		return (this->index == other.index);
	}
protected:
	bool Collision;
	bool Static;

	double VelocityX = 0;
	double VelocityY = 0;
	double Mass;		
	double Energy = 0; 
	double RotationAngle = 0;

	float Color_Red;
	float Color_Green;
	float Color_Blue;
private:
	static std::list<Object> ObjectsList;

	void GravityAcceleration(double deltaTime);

	void Move(double deltaTime);

	void Render();

	int index;

	float PositionX = 0;
	float PositionY = 0;

	int Sides;
	float Radius;
		
public:
	static void ObjectsMain(double deltaTime);


};
