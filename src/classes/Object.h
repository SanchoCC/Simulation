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

	std::shared_ptr <Object> operator->() {
		return shared_this_;
	}
		
protected:
	static std::list<std::shared_ptr<Object>> objects_list_;
	static std::list<std::shared_ptr<Object>> objects_list_2;
	std::vector<std::pair<float, float>> angles_;

	bool collision_;
	bool statical_;
	bool is_rectangle_ = false;	

	float density_ = 700;
	float mass_ = 1;
	float velocity_x_ = 0;
	float velocity_y_ = 0;
	float rotation_angle_ = 0;
	float position_x_ = 0;
	float position_y_ = 0;

	std::shared_ptr <Object> shared_this_;

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
	void Move(double deltaTime);
protected:
	
private:
	void GravityAcceleration(double deltaTime);

	virtual void Render() = 0;
	virtual bool CheckCollision(const Object* other) = 0;
	virtual void CollisionEffect(Object* other, double deltaTime) = 0;
public:
	bool GetIsRectangle() const;

	float GetRotationAngle() const;
	
	float GetMaxAngleX() const;
	float GetMinAngleX() const;
	float GetMaxAngleY() const;
	float GetMinAngleY() const;

	float GetMass() const;
	void SetMass(float mass) { this->mass_ = mass; }

	float GetVelocityX() const;
	float GetVelocityY() const;
	void SetVelocityX(float velocity_x); 
	void SetVelocityY(float velocity_y);
};

#endif // !SIMULATION_CLASSES_OBJECT_H_