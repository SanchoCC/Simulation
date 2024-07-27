#ifndef SIMULATION_CLASSES_COLOR_H_
#define SIMULATION_CLASSES_COLOR_H_
class Color {
public:
	Color();
	Color(float red, float green, float blue);
	void SetRandomColor();
	void SetColor(float red, float green, float blue);

	float red_;
	float green_;
	float blue_;
};

#endif //SIMULATION_CLASSES_COLOR_H_