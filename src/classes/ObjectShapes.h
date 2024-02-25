#ifndef SIMULATION_CLASSES_OBJECTSHAPES_H_
#define SIMULATION_CLASSES_OBJECTSHAPES_H_

#pragma once

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

#endif //SIMULATION_CLASSES_OBJECTSHAPES_H_