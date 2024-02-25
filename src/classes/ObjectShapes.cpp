#include "ObjectShapes.h"

Circle::Circle(bool Collision, bool Static, float PositionX, float PositionY, float Radius) :Object(Collision, Static, PositionX, PositionY)
{
    this->Radius = Radius;
    ObjectsList.push_back(std::make_shared<Circle>(*this));
}

void Circle::Render() {
    Angles.clear();
    int Sides = kCircleSides * Radius;
    glColor3f(Color.Red, Color.Green, Color.Blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < Sides; ++i) {
        float theta = 2.0f * M_PI * i / Sides - (M_PI / 4 + (RotationAngle / 180 * M_PI));
        glm::vec2 angle(Radius * cosf(theta) + PositionX, Radius * sinf(theta) + PositionY);
        Angles.push_back(angle);
        glVertex2f(angle.x, angle.y);
    }
    glEnd();
}