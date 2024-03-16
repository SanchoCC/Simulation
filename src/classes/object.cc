#include "object.h"

std::list<std::shared_ptr<Object>> Object::objects_list_;

Object::Object(bool statical, float position_x, float position_y) {
    this->statical_ = statical;
    this->position_.first = position_x;
    this->position_.second = position_y;
}

Object::~Object() {}

std::list<std::shared_ptr<Object>>& Object::GetObjectsList() {
    return objects_list_;
}

std::pair<float, float> Object::GetMaxVertices() const {
    auto max_x = std::max_element(vertices_.cbegin(), vertices_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });
    auto max_y = std::max_element(vertices_.cbegin(), vertices_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    return std::make_pair(max_x->first, max_y->second);
}

std::pair<float, float> Object::GetMinVertices() const {
    auto min_x = std::min_element(vertices_.cbegin(), vertices_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });
    auto min_y = std::min_element(vertices_.cbegin(), vertices_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    return std::make_pair(min_x->first, min_y->second);
}

std::vector<std::pair<float, float>> Object::GetVertices() const {
    return vertices_;
}

float Object::GetRotationAngle() const {
    return rotation_angle_;
}

void Object::SetRotationAngle(float rotation_angle) {
    rotation_angle_ = rotation_angle;
}

float Object::GetMass() const {
    return mass_;
}

void Object::SetMass(float mass) {
    mass_ = mass;
}

std::pair <float,float> Object::GetVelocity() const {
    return velocity_;
}

void Object::AddVelocity(float velocity_x, float velocity_y) {
    velocity_.first += velocity_x;
    velocity_.second += velocity_y;
}

void Object::SetVelocity(float velocity_x, float velocity_y) {
    velocity_.first = velocity_x;
    velocity_.second = velocity_y;
}

float Object::GetRestitution() const {
    return restitution_;
}

void Object::SetRestitution(float restitution) {
    restitution_ = restitution;
}

std::pair <float,float> Object::GetPosition() {
    return position_;
}
void Object::AddPosition(float position_x, float position_y) {
    position_.first += position_x;
    position_.second += position_y;
    UpdateVertices();
}
void Object::SetPosition(float position_x, float position_y) {
    position_.first = position_x;
    position_.second = position_y;
    UpdateVertices();
}
bool Object::GetStatical() {
    return statical_;
}
