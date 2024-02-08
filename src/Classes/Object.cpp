#include "Object.h"

Object::Object(bool Collision, bool Static, double Mass, int Sides, double Radius, float PositionX, float PositionY)
{
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
    

}
void Object::Move(double AccelerationX, double AccelerationY, double deltaTime)
{
    if (Static)
    {
    
    }
    else
    {
        VelocityX += AccelerationX * deltaTime;
        VelocityY += AccelerationY * deltaTime;
        PositionX += VelocityX * deltaTime;
        PositionY += VelocityY * deltaTime;
        this->Energy = (Mass * (pow((VelocityY + VelocityX) * 100, 2))) / 2;
    }
}

void Object::Render()
{
    Angles.clear();
    glColor3f(Color_Red, Color_Green, Color_Blue);
    glBegin(GL_POLYGON); // Начало описания полигона
    for (int i = 0; i < Sides; i++) {

        
        float theta = 2.0f * M_PI * i / Sides+(M_PI/4); // Угол текущего сегмента
        float x = Radius * cosf(theta); // Вычисление координаты x для текущего сегмента
        float y = Radius * sinf(theta); // Вычисление координаты y для текущего сегмента
        Angles.push_back(std::make_pair(PositionX + x, PositionY + y));
        auto it = Angles.begin();
        std::advance(it, i);
        glVertex2f(it->first, it->second); // Добавление вершины
    }

    glEnd(); // Завершение описания полигона
}