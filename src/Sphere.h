#pragma once
#include "Shape.h"

class Sphere : public Shape {
public:
	Sphere() : center(glm::vec3(0.0f)), radius(1.0f) {}
	Sphere(const glm::vec3& center, float radius) : center(center), radius(radius) {}

	bool intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const override;
	glm::vec3 getNormal(const glm::vec3& point) const override;

private:
	glm::vec3 center;
	float radius;
};

