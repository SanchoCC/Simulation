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
        this->Energy = (Mass * (pow((VelocityY + VelocityX) * 100, 2))) / 2;
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

