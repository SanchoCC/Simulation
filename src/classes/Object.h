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

class Object {
public:
	Object(bool collision, bool statical, float position_x, float position_y);
	virtual ~Object();

	static void ObjectsMain(double deltaTime);
		
protected:
	static std::list<std::shared_ptr<Object>> objects_list_;
	std::vector<std::pair<float, float>> angles_;

	bool collision_;
	bool statical_;
	bool is_rectangle_ = false;	

	float mass_ = 0;
	float velocity_x_ = 0;
	float velocity_y_ = 0;
	float rotation_angle_ = 0;
	float position_x_ = 0;
	float position_y_ = 0;

	struct Color {
		Color();
		Color(float red, float green, float blue);
		void SetRandomColor();
		void SetColor(float red, float green, float blue);
		float red_;
		float green_;
		float blue_;
	};
public:
	Color color_;
protected:
	void Move(double deltaTime);
private:
	void GravityAcceleration(double deltaTime);

	virtual void Render() = 0;
	virtual bool CheckCollision(const std::shared_ptr <Object>& other) = 0;
	virtual void CollisionEffect(const std::shared_ptr <Object>& other, double deltaTime) = 0;
public:
	bool GetIsRectangle() const;
	double GetRotationAngle() const;
	
	float GetMaxAngleX() const;
	float GetMinAngleX() const;
	float GetMaxAngleY() const;
	float GetMinAngleY() const;
};

#endif // !SIMULATION_CLASSES_OBJECT_H_