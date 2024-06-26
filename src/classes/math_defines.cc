#include "math_defines.h"

#include <algorithm>

float sim::Cross2D(const glm::vec2& vector1, const glm::vec2& vector2) {
	return vector1.x * vector2.y - vector1.y * vector2.x;
}

glm::vec2 sim::Cross2D(const glm::vec2& vector, float scalar) {
	return glm::vec2(scalar * vector.y, -scalar * vector.x);
}

glm::vec2 sim::Cross2D(float scalar, const glm::vec2& vector) {
	return glm::vec2(-scalar * vector.y, scalar * vector.x);
}

float sim::Clamp(float min, float max, float value) {
	return std::max(min, std::min(max, value));
}
