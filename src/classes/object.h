#ifndef SIMULATION_CLASSES_OBJECT_H_
#define SIMULATION_CLASSES_OBJECT_H_

#include <list>
#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "color.h"
#include "settings.h"
#include "material.h"

enum class ShapeType {
	kRectangle,
	kCircle,
};

class Object {
 public:
	Object(float position_x, float position_y, MaterialType material_type);
	Object() {};
	virtual ~Object();

	virtual void Render() const;
	virtual ShapeType GetType() const = 0;
	virtual void CalculateMass() = 0;

	static std::list <Object*>& GetObjectsList();	

	float GetRotationAngle() const;
	void AddRotationAngle(float rotation_angle);
	void SetRotationAngle(float rotation_angle);

	float GetInvertedMass() const;
	float GetInvertedInertia() const;

	glm::vec2 GetVelocity() const;
	void AddVelocity(glm::vec2 velocity);
	void SetVelocity(glm::vec2 velocity);	

	glm::vec2 GetPosition() const;
	void AddPosition(glm::vec2 position);
	void SetPosition(glm::vec2 position);

	std::vector <glm::vec2> GetVertices() const;
	void SetVertices(std::vector<glm::vec2> vertices);

	bool GetStatical();
	void SetStatical(bool statical);

	float GetAngularVelocity() const;
	void AddAngularVelocity(float angular_velocity);
	void SetAngularVelocity(float angular_velocity);

	void SetMaterial(MaterialType material_type);
	Material GetMaterial() const;
 protected:	
	static std::list<Object*> objects_list_;

	glm::vec2 position_{0, 0};
	
	std::vector<glm::vec2> vertices_;
	
	bool statical_ = false;
	
	float inverted_mass_ = 0; 
	float inverted_inertia_ = 0;
	float rotation_angle_ = 0;
	
	Material material_;

 private:
	virtual void UpdateVertices() = 0;

	glm::vec2 velocity_{ 0, 0 };
	float angular_velocity_ = 0;
};

#endif // !SIMULATION_CLASSES_OBJECT_H_
