#include "BoundingBox.h"

#include <algorithm>
#include <iostream>
#include "glm/gtx/string_cast.hpp"

bool BoundingBox::intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const {
    float tMin = -std::numeric_limits<float>::max();
    float tMax = std::numeric_limits<float>::max();

    for (int i = 0; i < 3; ++i) {

        float t0 = (min[i] - origin[i]) / direction[i];
        float t1 = (max[i] - origin[i]) / direction[i];

        float tEnter;
        float tExit;
        if (direction[i] >= 0.0f) {
            tEnter = t0;
            tExit  = t1;
        } else {
            tEnter = t1;
            tExit  = t0;
        }

        if (tEnter > tMin)
            tMin = tEnter;

        if (tExit  < tMax)
            tMax = tExit;

        if (tMax < tMin) {
            return false;
        }
    }

    return true;
}


void BoundingBox::expand(const glm::vec3& point) {
    min = glm::min(min, point);
    max = glm::max(max, point);
}

void BoundingBox::expand(const BoundingBox& box) {
    expand(box.min);
    expand(box.max);
}

