#pragma once
#include "Shape.h"
#include "Triangle.h"
#include <vector>
#include <memory>
#include "BVHNode.h"  // Add this include

class BVH : public Shape {
public:
    explicit BVH(const std::vector<Triangle*>& triangles);
    ~BVH();
    mutable Shape* lastHitShape;

    bool intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const override;
    glm::vec3 getNormal(const glm::vec3& point) const override;

private:
    static const int MAX_TRIANGLES_PER_LEAF = 3;
    BVHNode* root;
    mutable const Triangle* lastHitTriangle;

    void buildBVH(const std::vector<Triangle*>& triangles);
    void buildNode(BVHNode* node, std::vector<Triangle*>& tris, int depth);
    bool intersectNode(const BVHNode* node, const glm::vec3& origin,
                       const glm::vec3& direction, float& t) const;
};
