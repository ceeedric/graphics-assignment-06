#include "Sphere.h"

#include <algorithm>
#include <iostream>
#include <ostream>

bool Sphere::intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const {
    float a = dot(direction, direction);
    float b = 2.0f * dot(origin - center, direction);
    float c = dot(origin - center, origin - center) - (radius * radius);
    float discriminant = (b * b) - (4.0f * a * c);

    float t0 = (-b - sqrt(discriminant)) / (2.0f * a);
    float t1 = (-b + sqrt(discriminant)) / (2.0f * a);

    if (t0 > EPSILON) {
        t = t0;
        // std::cout << "t0 = " << t0 << std::endl;
        return true;
    }
    if (t1 > EPSILON) {
        t = t1;
        // std::cout << "t1 = " << t1 << std::endl;
        return true;
    }

    return false;
}

glm::vec3 Sphere::getNormal(const glm::vec3& point) const {
    return normalize(point - center);
}
