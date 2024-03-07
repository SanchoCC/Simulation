#include "object.h"

std::list<std::shared_ptr<Object>> Object::objects_list_;

Object::Object(bool statical, float position_x, float position_y) { 
    this->statical_ = statical;
    this->position_x_ = position_x;
    this->position_y_ = position_y;     
}
Object::~Object() {   
}
void Object::GravityAcceleration(double delta_time) {
    velocity_y_ -= 9.8f;
    velocity_x_ += 0;
}
void Object::Move(double delta_time) {
    if (!statical_) {        
        position_x_ += (velocity_x_*0.001f) * delta_time;
        position_y_ += (velocity_y_*0.001f) * delta_time;
        UpdateVertices();
    } else {
        velocity_x_ = 0;
        velocity_y_ = 0;
    }    
}
std::list <std::shared_ptr<Object>>& Object::GetObjectsList() { 
    return objects_list_; 
}
std::pair <float, float> Object::GetMaxVertices() const {
    auto max_x = *std::max_element(vertices_.cbegin(), vertices_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });   
    auto max_y = *std::max_element(vertices_.cbegin(), vertices_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    return std::make_pair(max_x.first, max_y.second);
}
std::pair <float, float> Object::GetMinVertices() const {
    auto min_x = *std::min_element(vertices_.cbegin(), vertices_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });   
    auto min_y = *std::min_element(vertices_.cbegin(), vertices_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    return std::make_pair(min_x.first, min_y.second);
}
float Object::GetRotationAngle() const {
    return this->rotation_angle_;
}
float Object::GetMass() const {
    return mass_;
}
void Object::SetMass(float mass) {
    this->mass_ = mass;
}
float Object::GetVelocityX() const {
    return velocity_x_;
}
float Object::GetVelocityY() const {
    return velocity_y_;
}
void Object::SetVelocityX(float velocity_x) {
    this->velocity_x_ = velocity_x;
}
void Object::SetVelocityY(float velocity_y) {
    this->velocity_y_ = velocity_y;
}
float Object::GetTension() const {
    return this->tension_;
}
void Object::SetTension(float tension) {
    this->tension_ = tension;
}

