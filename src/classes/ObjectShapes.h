#pragma once
#ifndef SIMULATION_CLASSES_OBJECTSHAPES_H_
#define SIMULATION_CLASSES_OBJECTSHAPES_H_

#include "Object.h"

class Circle :public Object
{
public:
    Circle(bool collision, bool statical, float position_x, float position_y, float radius);
private:
    void Render() override;
    bool CheckCollision(const std::shared_ptr <Object>& Other) override { return false; };
    void CollisionEffect(std::shared_ptr <Object>& other, double deltaTime) override {};
private: 
    float radius_;
    const int kCircleSides = 360;
};
class Rectangle:public Object
{
public:
    Rectangle(bool collision, bool statical, float position_x, float position_y, float width, float height);
private:
    void Render() override;
    bool CheckCollision(const std::shared_ptr <Object>& other) override;
    void CollisionEffect(std::shared_ptr <Object>& other, double deltaTime) override;
private:        
    float width_;
    float height_;
};

#endif //SIMULATION_CLASSES_OBJECTSHAPES_H_