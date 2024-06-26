#pragma once
#ifndef SIMULATION_CLASSES_OBJECT_H_
#define SIMULATION_CLASSES_OBJECT_H_

#include <list>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

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
	std::vector<glm::vec2> normals_;
	void Render();

	static std::list <std::shared_ptr<Object>>& GetObjectsList();

	virtual ShapeType GetType() const = 0;	

	float GetRotationAngle() const;
	void AddRotationAngle(float rotation_angle);
	void SetRotationAngle(float rotation_angle);

	float GetMass() const;
	void SetMass(float mass);

	float GetInvertedMass() const;
	float GetInvertedInertia() const;

	glm::vec2 GetVelocity() const;
	void AddVelocity(glm::vec2 velocity);
	void SetVelocity(glm::vec2 velocity);

	float GetRestitution() const;
	void SetRestitution(float restitution);	

	glm::vec2 GetPosition();
	void AddPosition(glm::vec2 position);
	void SetPosition(glm::vec2 position);

	std::vector <glm::vec2> GetVertices() const;
	void SetVertices(std::vector<glm::vec2> vertices);

	bool GetStatical();

	float GetAngularVelocity() const;
	void AddAngularVelocity(float angular_velocity);
	void SetAngularVelocity(float angular_velocity);
 protected:
	virtual void UpdateVertices() = 0;

	std::shared_ptr <Object> shared_this_;
	static std::list<std::shared_ptr<Object>> objects_list_;
	glm::vec2 position_{0, 0};
	glm::vec2 velocity_{0, 0};
	std::vector<glm::vec2> vertices_;
	
	bool statical_ = false;
	float restitution_ = 0.5f;
	float density_ = 0.6f;
	float mass_ = 0;
	float inverted_mass_ = 0; 
	float inertia_ = 0;
	float inverted_inertia_ = 0;
	float rotation_angle_ = 0;
	float angular_velocity_ = 0;

	Color color_;
};

#endif // !SIMULATION_CLASSES_OBJECT_H_
