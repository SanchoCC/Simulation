#ifndef SIMULATION_CLASSES_OBJECTSHAPES_H_
#define SIMULATION_CLASSES_OBJECTSHAPES_H_

#include "object.h"

class Circle : public Object {
public:
	Circle(float position_x, float position_y, float radius, MaterialType material_type);
	Circle();
	~Circle();
	void Render() const override;
	ShapeType GetType() const override;
	
	float GetRadius() const;

private:
	void UpdateVertices() override;
	void CalculateMass() override;

	float radius_;
	const int kCircleSides = 360;
	const float kMinSidesKoef = 0.01f;
};
class Rectangle : public Object {
public:
	Rectangle(float position_x, float position_y, float width, float height, MaterialType material_type);
	~Rectangle();
	ShapeType GetType() const override;
	
	float GetWidth() const;
	float GetHeight() const;

private:
	void UpdateVertices() override;
	void CalculateMass() override;

	float width_;
	float height_;
};

#endif  // SIMULATION_CLASSES_OBJECTSHAPES_H_