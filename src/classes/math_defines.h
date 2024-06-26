#ifndef SIMULATION_CLASSES_MATH_DEFINES_H_
#define SIMULATION_CLASSES_MATH_DEFINES_H_

#include <glm/glm.hpp>

namespace sim {
	float Cross2D(const glm::vec2& vector1, const glm::vec2& vector2);
	glm::vec2 Cross2D(const glm::vec2& vector, float scalar);
	glm::vec2 Cross2D(float scalar, const glm::vec2& vector);	
	float Clamp(float min, float max, float value);
}

#endif // SIMULATION_CLASSES_MATH_DEFINES_H_