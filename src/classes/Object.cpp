#include "Object.h"

std::list<std::shared_ptr<Object>> Object::ObjectsList;

Object::Object(bool Collision, bool Static, float PositionX, float PositionY) { 
    this->Collision = Collision;
    this->Static = Static;
    this->PositionX = PositionX;
    this->PositionY = PositionY;  
}
Object::~Object() {
}
void Object::GravityAcceleration(double deltaTime) {
    VelocityY -= 9.8;
}
void Object::Move(double deltaTime) {
    if (!Static) {
        PositionX += (VelocityX*0.001) * deltaTime;
        PositionY += (VelocityY*0.001) * deltaTime;
    }
}
void Object::ObjectsMain(double deltaTime)
{
    for (auto it = ObjectsList.begin(); it != ObjectsList.end(); ++it) {
        (*it)->GravityAcceleration(deltaTime);
        (*it)->Move(deltaTime);
        (*it)->Render();
    }
}
Object::Color::Color() {
    SetRandomColor();
}
Object::Color::Color(float Red, float Green, float Blue) {
    SetColor(Red, Green, Blue);
}
void Object::Color::SetRandomColor() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> color_dist(0.0f, 1.0f);
    this->Red = color_dist(rng);
    this->Green = color_dist(rng);
    this->Blue = color_dist(rng);
}
void Object::Color::SetColor(float Red, float Green, float Blue) {
    this->Red = Red;
    this->Green = Green;
    this->Blue = Blue;
}

