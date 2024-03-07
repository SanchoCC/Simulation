#pragma once
#ifndef SIMULATION_CLASSES_OBJECT_H_
#define SIMULATION_CLASSES_OBJECT_H_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <vector>
#include <memory>
#include <algorithm>

#include "color.h"

enum class ShapeType {
	kRectangle,
	kCircle,
};

class Object {
 public:
	Object(bool statical, float position_x, float position_y);
	virtual ~Object();

	std::shared_ptr <Object> operator->() {
		return shared_this_;
	}
	
	void GravityAcceleration(double delta_time);

	void Move(double delta_time);

	virtual void Render() = 0;

	static std::list <std::shared_ptr<Object>>& GetObjectsList();

	virtual ShapeType GetType() const = 0;

	std::pair <float, float> GetMaxVertices() const;
	std::pair <float, float> GetMinVertices() const;

	float GetRotationAngle() const;

	float GetMass() const;
	void SetMass(float mass);

	float GetVelocityX() const;
	void SetVelocityX(float velocity_x);
	float GetVelocityY() const;
	void SetVelocityY(float velocity_y);

	float GetTension() const;
	void SetTension(float tension);	

	virtual float GetRadius() = 0;

	glm::vec2 GetPositionVec2();

 protected:
	virtual void UpdateVertices() = 0;

	std::shared_ptr <Object> shared_this_;
	static std::list<std::shared_ptr<Object>> objects_list_;
	std::vector<std::pair<float, float>> vertices_;
	bool statical_;
	float tension_ = 0.8f;
	float density_ = 700;
	float mass_ = 1000;
	float velocity_x_ = 0;
	float velocity_y_ = 0;
	float rotation_angle_ = 0;
	float position_x_ = 0;
	float position_y_ = 0;
	Color color_;
};

#endif // !SIMULATION_CLASSES_OBJECT_H_
