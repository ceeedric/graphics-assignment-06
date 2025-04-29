#include "Plane.h"

#include <algorithm>

bool Plane::intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const {
    t = dot(center - origin, normal) / glm::dot(direction, normal);
    return t >= 0;
}

glm::vec3 Plane::getNormal(const glm::vec3& point) const {
    return normal;
}