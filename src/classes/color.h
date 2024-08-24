#ifndef SIMULATION_CLASSES_COLOR_H_
#define SIMULATION_CLASSES_COLOR_H_

#include "glm/vec3.hpp"

class Color {
public:
	Color();
	Color(float red, float green, float blue);
	Color(glm::vec3 color);
	void SetRandomColor();
	void SetColor(float red, float green, float blue);
	void SetColor(glm::vec3 color);

	glm::vec3 GetColor() const;
private:
	glm::vec3 color_;
};

#endif //SIMULATION_CLASSES_COLOR_H_