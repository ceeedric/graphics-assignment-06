#pragma once
#include "BoundingBox.h"
#include "Triangle.h"
#include <vector>

class BVHNode {
public:
    BVHNode() : left(nullptr), right(nullptr) {}
    ~BVHNode() {
        delete left;
        delete right;
    }

    BoundingBox bounds;
    BVHNode* left;
    BVHNode* right;
    std::vector<Triangle*> triangles;
};