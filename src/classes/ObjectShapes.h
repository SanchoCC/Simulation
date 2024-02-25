#pragma once
#ifndef SIMULATION_CLASSES_OBJECTSHAPES_H_
#define SIMULATION_CLASSES_OBJECTSHAPES_H_

#include "Object.h"

class Circle :public Object
{
public:
    Circle(bool Collision, bool Static, float PositionX, float PositionY, float Radius);
private:
    void Render() override;
private: 
    float Radius;
    const int kCircleSides = 360;
};
class Rectangle:public Object
{
public:
    Rectangle(bool Collision, bool Static, float PositionX, float PositionY, float Height, float Width);
private:
    void Render() override;
private:
    float Height; 
    float Width;
};

#endif //SIMULATION_CLASSES_OBJECTSHAPES_H_