#pragma once
#include <glm/glm.hpp>

class Shape {
public:
	Shape() :
		ka(glm::vec3(0.1f)),     // Default ambient coefficient
		kd(glm::vec3(1.0f)),     // Default diffuse coefficient
		ks(glm::vec3(0.0f)),     // Default specular coefficient
		km(glm::vec3(0.0f)),     // Default mirror reflection coefficient
		n(1.0f)                  // Default specular exponent
	{}

	virtual ~Shape() {}

	// Material properties
	glm::vec3 ka;    // Ambient coefficient
	glm::vec3 kd;    // Diffuse coefficient
	glm::vec3 ks;    // Specular coefficient
	glm::vec3 km;    // Mirror reflection coefficient
	float n;         // Specular exponent (shininess)

	// Pure virtual functions that must be implemented by derived classes

	/**
	 * Tests for intersection between a ray and this shape
	 * @param origin The starting point of the ray
	 * @param direction The normalized direction of the ray
	 * @param t The distance along the ray to the intersection point (if found)
	 * @return true if an intersection was found, false otherwise
	 */
	virtual bool intersect(const glm::vec3& origin,
						 const glm::vec3& direction,
						 float& t) const = 0;

	/**
	 * Gets the surface normal at a given point on the shape
	 * @param point The point at which to calculate the normal
	 * @return The normalized surface normal vector
	 */
	virtual glm::vec3 getNormal(const glm::vec3& point) const = 0;

protected:
	// Small value used for floating point comparisons
	static constexpr float EPSILON = 0.0001f;
};


