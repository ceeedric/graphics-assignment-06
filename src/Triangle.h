#pragma once
#include "Shape.h"
#include <glm/glm.hpp>

class Triangle : public Shape {
public:
    Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
            const glm::vec3& n0, const glm::vec3& n1, const glm::vec3& n2) {
        vertices[0] = v0;
        vertices[1] = v1;
        vertices[2] = v2;
        normals[0] = n0;
        normals[1] = n1;
        normals[2] = n2;
    }

    const glm::vec3& getNormal0() const { return normals[0]; }
    const glm::vec3& getNormal1() const { return normals[1]; }
    const glm::vec3& getNormal2() const { return normals[2]; }

    bool intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const override;
    glm::vec3 getNormal(const glm::vec3& point) const override;

    const glm::vec3& getV0() const { return vertices[0]; }
    const glm::vec3& getV1() const { return vertices[1]; }
    const glm::vec3& getV2() const { return vertices[2]; }

    glm::vec3 vertices[3];
    glm::vec3 normals[3];
};
