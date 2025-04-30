#pragma once
#include <glm/glm.hpp>
#include <limits>

class BoundingBox {
public:
    BoundingBox() :
            min(std::numeric_limits<float>::max()),
            max(-std::numeric_limits<float>::max()) {}

    bool intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const;
    void expand(const glm::vec3& point);
    void expand(const BoundingBox& box);

    glm::vec3 min;
    glm::vec3 max;
};
