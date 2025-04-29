#include "Sphere.h"

#include <algorithm>
#include <iostream>
#include <ostream>

bool Sphere::intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const {
    float a = dot(direction, direction);
    float b = 2 * dot(origin - center, direction);
    float c = dot(origin - center, origin - center) - (radius * radius);
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return false;

    float t0 = (-b - discriminant) / (2 * a);
    float t1 = (-b + discriminant) / (2 * a);

    if (t0 > EPSILON) {
        t = t0;
        return true;
    }
    if (t1 > EPSILON) {
        t = t1;
        return true;
    }

    return false;
}

glm::vec3 Sphere::getNormal(const glm::vec3& point) const {
    return normalize(point - center);
}
