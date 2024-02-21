#include "Object.h"

int Object::counter = 0;

std::list<Object> Object::ObjectsList;

Object::Object(bool Collision, bool Static, double Mass, int Sides, double Radius, float PositionX, float PositionY) {
    this->index = counter;    
	this->Collision = Collision;
	this->Static = Static;
	this->Mass = Mass;
    this->PositionX = PositionX;
    this->PositionY = PositionY;
    this->Sides = Sides;
    this->Radius = Radius; 
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> color_dist(0.0f, 1.0f);
    this->Color_Red = color_dist(rng); 
    this->Color_Green = color_dist(rng);
    this->Color_Blue = color_dist(rng);
    ++counter;
    ObjectsList.push_back(*this);
}
Object::~Object() {
    auto it = std::find(ObjectsList.begin(), ObjectsList.end(), *this);
    if (it != ObjectsList.end()) {
        ObjectsList.erase(it);
    }
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
void Object::Render() {
    Angles.clear();
    glColor3f(Color_Red, Color_Green, Color_Blue);
    glBegin(GL_POLYGON); 
    for (int i = 0; i < Sides; ++i) {        
        float theta = 2.0f * M_PI * i / Sides-(M_PI/4+(RotationAngle/180*M_PI));
        glm::vec2 angle(Radius * cosf(theta)+PositionX, Radius * sinf(theta)+PositionY); 
        Angles.push_back(angle);        
        glVertex2f(angle.x, angle.y);
    }
    glEnd(); 
}
void Object::ObjectsMain(double deltaTime)
{
    for (auto it = ObjectsList.begin(); it != ObjectsList.end(); ++it) {
        it->GravityAcceleration(deltaTime);
        it->Move(deltaTime);
        it->Render();
    }
}

