#pragma once
#ifndef SIMULATION_CLASSES_OBJECTSHAPES_H_
#define SIMULATION_CLASSES_OBJECTSHAPES_H_

#include "object.h"

class Circle : public Object {
 public:
    Circle(bool statical, float position_x, float position_y, float radius);
    ShapeType GetType() const override;

    void Render() override;

    float GetRadius() override;

 protected:
     void UpdateVertices() override;

 private: 
    float radius_;
    const int kCircleSides = 360;
};
class Rectangle : public Object {
 public:
    Rectangle(bool statical, float position_x, float position_y, float width, float height);
    ShapeType GetType() const override;

    void Render() override;
    float GetRadius() override;

 protected:
    void UpdateVertices() override;

 private:        
    float width_;
    float height_;
};

#endif //SIMULATION_CLASSES_OBJECTSHAPES_H_