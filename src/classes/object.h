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

	virtual void Render() = 0;

	static std::list <std::shared_ptr<Object>>& GetObjectsList();

	virtual ShapeType GetType() const = 0;

	std::pair <float, float> GetMaxVertices() const;
	std::pair <float, float> GetMinVertices() const;

	float GetRotationAngle() const;
	void AddRotationAngle(float rotation_angle);
	void SetRotationAngle(float rotation_angle);

	float GetMass() const;
	void SetMass(float mass);

	std::pair<float, float> GetVelocity() const;
	void AddVelocity(float velocity_x, float velocity_y);
	void SetVelocity(float velocity_x, float velocity_y);

	float GetRestitution() const;
	void SetRestitution(float restitution);	

	virtual float GetRadius() = 0;

	std::pair<float, float> GetPosition();
	void AddPosition(float position_x, float position_y);
	void SetPosition(float position_x, float position_y);

	std::vector <std::pair<float, float>> GetVertices() const;

	bool GetStatical();

	float GetAngularVelocity() const;
	void AddAngularVelocity(float angular_velocity);
	void SetAngularVelocity(float angular_velocity);

 protected:
	virtual void UpdateVertices() = 0;

	std::shared_ptr <Object> shared_this_;
	static std::list<std::shared_ptr<Object>> objects_list_;
	std::pair<float, float> position_{0, 0};
	std::pair<float, float> velocity_{0, 0};
	std::pair<float, float> impulse_{0, 0};
	std::vector<std::pair<float, float>> vertices_;
	bool statical_ = false;
	float restitution_ = 0.5f;
	float density_ = 700;
	float mass_ = 1000;
	float rotation_angle_ = 0;
	float angular_velocity_ = 0;

	Color color_;
};

#endif // !SIMULATION_CLASSES_OBJECT_H_
