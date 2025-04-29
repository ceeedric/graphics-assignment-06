#pragma once
#include <glm/glm.hpp>

class Light {
public:
	Light() : position(glm::vec3(0.0f)), color(glm::vec3(1.0f)) {}
	Light(const glm::vec3& pos, const glm::vec3& col) : position(pos), color(col) {}

	glm::vec3 position;
	glm::vec3 color;
};
