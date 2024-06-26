#include "object.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

std::list<std::shared_ptr<Object>> Object::objects_list_;

Object::Object(bool statical, float position_x, float position_y) {
    this->statical_ = statical;
    this->position_.x = position_x;
    this->position_.y = position_y;
}

Object::~Object() {}

void Object::Render() {
    glColor3f(color_.red_, color_.green_, color_.blue_);
    glBegin(GL_POLYGON);
    for (const auto& it : vertices_) {
        glVertex2f(it.x, it.y);
    }
    glEnd();
    glColor3f(100, 0, 0);
    /*glBegin(GL_LINES);
    for (const auto& it : normals_) {
        glVertex2f(position_.x, position_.y);
        glVertex2f(it.x, it.y);
    }*/
    glBegin(GL_TRIANGLES);
    {
        glVertex2f(position_.x, position_.y);
        glVertex2f(vertices_[0].x, vertices_[0].y);
        glVertex2f(vertices_[1].x, vertices_[1].y);
    }
    glEnd();
}

std::list<std::shared_ptr<Object>>& Object::GetObjectsList() {
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

float Object::GetMass() const {
    return mass_;
}

void Object::SetMass(float mass) {
    mass_ = mass;
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

float Object::GetRestitution() const {
    return restitution_;
}

void Object::SetRestitution(float restitution) {
    restitution_ = restitution;
}

glm::vec2 Object::GetPosition() {
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

float Object::GetAngularVelocity() const {
    return angular_velocity_;
}

void Object::AddAngularVelocity(float angular_velocity) {
    angular_velocity_ += angular_velocity;
}

void Object::SetAngularVelocity(float angular_velocity) {
    angular_velocity_ = angular_velocity;
}
