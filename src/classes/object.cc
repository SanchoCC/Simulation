#include "object.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

std::list<Object*> Object::objects_list_;

Object::Object(float position_x, float position_y, MaterialType material_type) {
	position_.x = position_x;
	position_.y = position_y;	
	material_.SetMaterial(material_type);
}

Object::~Object() = default;

void Object::Render() const {
	glColor3f(material_.GetColor().GetRed(), material_.GetColor().GetGreen(), material_.GetColor().GetBlue());
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vertices_.data());
	glDrawArrays(GL_POLYGON, 0, vertices_.size());
	glDisableClientState(GL_VERTEX_ARRAY);
}

std::list<Object*>& Object::GetObjectsList() {
	return objects_list_;
}

std::vector<glm::vec2> Object::GetVertices() const {
	return vertices_;
}

void Object::SetVertices(std::vector<glm::vec2> vertices) {
	vertices_ = vertices;
}

float Object::GetRotationAngle() const {
	return rotation_angle_;
}
void Object::AddRotationAngle(float rotation_angle) {
	rotation_angle_ += rotation_angle;
	UpdateVertices();
}
void Object::SetRotationAngle(float rotation_angle) {
	rotation_angle_ = rotation_angle;
	UpdateVertices();
}

float Object::GetInvertedMass() const {
	return inverted_mass_;
}
float Object::GetInvertedInertia() const {
	return inverted_inertia_;
}

glm::vec2 Object::GetVelocity() const {
	return velocity_;
}

void Object::AddVelocity(glm::vec2 velocity) {
	velocity_ += velocity;
}

void Object::SetVelocity(glm::vec2 velocity) {
	velocity_ = velocity;
}

glm::vec2 Object::GetPosition() const {
	return position_;
}

void Object::AddPosition(glm::vec2 position) {
	position_ += position;
	UpdateVertices();
}

void Object::SetPosition(glm::vec2 position) {
	position_ = position;
	UpdateVertices();
}

bool Object::GetStatical() {
	return statical_;
}

void Object::SetStatical(bool statical) {
	statical_ = statical;
	CalculateMass();
}

float Object::GetAngularVelocity() const {
	return angular_velocity_;
}

void Object::AddAngularVelocity(float angular_velocity) {
	angular_velocity_ += angular_velocity;
}

void Object::SetAngularVelocity(float angular_velocity) {
	angular_velocity_ = angular_velocity;
}

Material Object::GetMaterial() const {
	return material_;
}

void Object::SetMaterial(MaterialType material_type) {
	material_.SetMaterial(material_type);
}
