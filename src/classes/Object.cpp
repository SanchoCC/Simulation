#include "Object.h"

std::list<std::shared_ptr<Object>> Object::objects_list_;

Object::Object(bool collision, bool statical, float position_x, float position_y) { 
    this->collision_ = collision;
    this->statical_ = statical;
    this->position_x_ = position_x;
    this->position_y_ = position_y;  
}
Object::~Object() {   
}
void Object::GravityAcceleration(double deltaTime) {
    velocity_y_ -= 9.8;
}
void Object::Move(double deltaTime) {
    if (!statical_) {        
        position_x_ += (velocity_x_*0.001f) * deltaTime;
        position_y_ += (velocity_y_*0.001f) * deltaTime;
    }
}
void Object::ObjectsMain(double deltaTime)
{
    for (auto it = objects_list_.begin(); it != objects_list_.end(); ++it) {
        (*it)->GravityAcceleration(deltaTime);
        (*it)->Move(deltaTime);        
        for (auto innerit = objects_list_.begin(); innerit != objects_list_.end(); ++innerit) {
            if (innerit == it) {
                continue;
            } else if ((*it)->CheckCollision(*innerit)) {
                (*it)->CollisionEffect(*innerit, deltaTime);
            }
        }
        (*it)->Render();
    }
}
Object::Color::Color() {
    SetRandomColor();
}
Object::Color::Color(float red, float green, float blue) {
    SetColor(red, green, blue);
}
void Object::Color::SetRandomColor() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> color_dist(0.0f, 1.0f);
    this->red_ = color_dist(rng);
    this->green_ = color_dist(rng);
    this->blue_ = color_dist(rng);
}
void Object::Color::SetColor(float red, float green, float blue) {
    this->red_ = red;
    this->green_ = green;
    this->blue_ = blue;
}
bool Object::GetIsRectangle() const {
    return this->is_rectangle_;
}
double Object::GetRotationAngle() const {
    return this->rotation_angle_;
}
float Object::GetMaxAngleX() const {
    auto max = *std::max_element(angles_.cbegin(), angles_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });   
    return max.first;
}
float Object::GetMinAngleX() const {
    auto min = *std::min_element(angles_.cbegin(), angles_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.first < rhs.first; });   
    return min.first;
}
float Object::GetMaxAngleY() const {
    auto max = *std::max_element(angles_.cbegin(), angles_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    return max.second;
}
float Object::GetMinAngleY() const {
    auto min = *std::min_element(angles_.cbegin(), angles_.cend(), [](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });
    return min.second;
}

