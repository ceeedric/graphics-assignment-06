#include "BVH.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Camera.h"

BVH::BVH(const std::vector<Triangle*>& triangles) : root(nullptr), lastHitTriangle(nullptr), lastHitShape(nullptr) {
    root = new BVHNode();
    buildBVH(triangles);
}

BVH::~BVH() {
    delete root;
    root = nullptr;
    lastHitTriangle = nullptr;
    lastHitShape = nullptr;
}


void BVH::buildBVH(const std::vector<Triangle*>& triangles) {
    root = new BVHNode();
    buildNode(root, const_cast<std::vector<Triangle*>&>(triangles), 0);
}

void BVH::buildNode(BVHNode* node, std::vector<Triangle*>& tris, int depth) {
    // calculate bounding box
    BoundingBox boundingBox;
    for (Triangle * triangle : tris) {
        boundingBox.expand(triangle->getV0());
        boundingBox.expand(triangle->getV1());
        boundingBox.expand(triangle->getV2());
    }

    node->bounds = boundingBox;

    // if we are under the max amount of trees, stop here
    if (tris.size() <= MAX_TRIANGLES_PER_LEAF) {
        node->triangles = tris;
        return;
    }

    int axis = depth % 3;
    std::sort(tris.begin(), tris.end(), [axis](const Triangle * t1, const Triangle * t2){

        glm::vec3 center1 = (t1->getV0() + t1->getV1() + t1->getV2()) / 3.0f;
        glm::vec3 center2 = (t2->getV0() + t2->getV1() + t2->getV2()) / 3.0f;

        return center1[axis] < center2[axis];
    });

    int middle = tris.size() / 2;
    std::vector<Triangle*> left(tris.begin(), tris.begin() + middle);
    std::vector<Triangle*> right(tris.begin() + middle, tris.end());

    node->left = new BVHNode();
    buildNode(node->left, left, depth + 1);

    node->right = new BVHNode();
    buildNode(node->right, right, depth + 1);

    // if (depth == 10){
    //     std::cout << "depth: " << depth << std::endl;
    //     std::cout << tris.size() << std::endl;
    //     std::cout << "-------" << std::endl;
    // }
}

bool BVH::intersectNode(const BVHNode* node, const glm::vec3& origin,
                   const glm::vec3& direction, float& t) const {

    float boxT;
    if (!node->bounds.intersect(origin, direction, boxT))
        return false;

    float closestT = std::numeric_limits<float>::max();

    // if this is a leaf node, check all triangles
    if (node->left == nullptr && node->right == nullptr) {
        // std::cout << node->left << " " << node->right << std::endl;
        for (auto & triangle : node->triangles) {
            float f;
            if (triangle->intersect(origin, direction, f) && f < closestT) {
                closestT = f;
                lastHitTriangle = triangle;
                lastHitShape = triangle;
            }
        }

        t = closestT;
        return true;
    }

    bool hit = false;
    float tLeft = std::numeric_limits<float>::max();
    float tRight = std::numeric_limits<float>::max();

    bool hitLeft = intersectNode(node->left, origin, direction, tLeft);
    bool hitRight = intersectNode(node->right, origin, direction, tRight);

    if (hitLeft && tLeft < closestT) {
        closestT = tLeft;
        hit = true;
    }

    if (hitRight && tRight < closestT) {
        closestT = tRight;
        hit = true;
    }

    if (hit)
        t = closestT;

    return hit;
}

bool BVH::intersect(const glm::vec3& origin, const glm::vec3& direction, float& t) const {
    return intersectNode(root, origin, direction, t) && t > EPSILON;
}

glm::vec3 BVH::getNormal(const glm::vec3& point) const {
    if (lastHitTriangle == nullptr)
        return glm::vec3(0, 0, 0);

    return lastHitTriangle->getNormal(point);
}
