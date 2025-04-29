#pragma once
#include "Shape.h"

class Plane : public Shape {
public:
	Plane() : center(glm::vec3(0.0f)), normal(glm::vec3(0.0f, 1.0f, 0.0f)) {}

	Plane(const glm::vec3& center, const glm::vec3& normal)
		: center(center), normal(glm::normalize(normal)) {}

	bool intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const override;
	glm::vec3 getNormal(const glm::vec3& point) const override;

private:
	glm::vec3 center;
	glm::vec3 normal;
};

