#ifndef SIMULATION_CLASSES_OBJECTSHAPES_H_
#define SIMULATION_CLASSES_OBJECTSHAPES_H_

#include "object.h"

class Circle : public Object {
 public:
    Circle(bool statical, float position_x, float position_y, float radius);
    ~Circle();
    ShapeType GetType() const override;
    float GetRadius() const;
 private: 
    void UpdateVertices() override;
    
    float radius_;
    const int kCircleSides = 180;
    const float kMinSidesKoef = 0.01f;
};
class Rectangle : public Object {
 public:
    Rectangle(bool statical, float position_x, float position_y, float width, float height);
    ~Rectangle();
    ShapeType GetType() const override;
    float GetWidth() const;
    float GetHeight() const;
 private: 
    void UpdateVertices() override;

    float width_;
    float height_;
};

#endif //SIMULATION_CLASSES_OBJECTSHAPES_H_