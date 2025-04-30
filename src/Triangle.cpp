#include "Triangle.h"

bool Triangle::intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const {
    glm::vec3 e1 = vertices[1] - vertices[0];
    glm::vec3 e2 = vertices[2] - vertices[0];
    glm::vec3 s = origin - vertices[0];
    glm::vec3 s1 = cross(direction, e2);
    glm::vec3 s2 = cross(s, e1);

    glm::vec3 result = (1 / dot(s1, e1)) * glm::vec3(dot(s2, e2), dot(s1, s), dot(s2, direction));
    t = result.x;
    return result.x >= 0;
}

glm::vec3 Triangle::getNormal(const glm::vec3& point) const {
    glm::vec3 u = vertices[1] - vertices[0];
    glm::vec3 v = vertices[2] - vertices[0];
    glm::vec3 normal = cross(u, v);
    return glm::normalize(normal);
}

