#pragma once
#include "Triangle.h"
#include "BVHNode.h"
#include "tiny_obj_loader.h"
#include <string>
#include <vector>
#include <iostream>

// I regret making this

class OBJLoader {
public:
    static bool LoadOBJ(const std::string& filename,
                        std::vector<Triangle*>& triangles,
                        const glm::vec3& ka = glm::vec3(0.1f),
                        const glm::vec3& kd = glm::vec3(0.0f, 0.0f, 1.0f),
                        const glm::vec3& ks = glm::vec3(1.0f),
                        const glm::vec3& km = glm::vec3(0.0f),
                        float n = 100.0f) {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn;
        std::string err;

        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err,
                                    filename.c_str(), nullptr);

        if (!err.empty()) {
            std::cerr << "Error: " << err << std::endl;
        }

        if (!ret) {
            return false;
        }

        for (const auto& shape : shapes) {
            size_t index_offset = 0;
            for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
                if (shape.mesh.num_face_vertices[f] != 3) {
                    std::cerr << "Warning: Non-triangle face detected. Skipping." << std::endl;
                    continue;
                }

                glm::vec3 vertices[3];
                glm::vec3 normals[3];

                for (size_t v = 0; v < 3; v++) {
                    tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

                    // Vertex positions
                    vertices[v] = glm::vec3(
                            attrib.vertices[3 * idx.vertex_index + 0],
                            attrib.vertices[3 * idx.vertex_index + 1],
                            attrib.vertices[3 * idx.vertex_index + 2]
                    );

                    // Normals (if available)
                    if (idx.normal_index >= 0) {
                        normals[v] = glm::vec3(
                                attrib.normals[3 * idx.normal_index + 0],
                                attrib.normals[3 * idx.normal_index + 1],
                                attrib.normals[3 * idx.normal_index + 2]
                        );
                    } else {
                        glm::vec3 v0v1 = vertices[1] - vertices[0];
                        glm::vec3 v0v2 = vertices[2] - vertices[0];
                        glm::vec3 faceNormal = glm::normalize(glm::cross(v0v1, v0v2));
                        normals[0] = normals[1] = normals[2] = faceNormal;
                    }
                }

                Triangle * tri = new Triangle(vertices[0], vertices[1], vertices[2],
                             normals[0], normals[1], normals[2]);
                tri->ka = ka;
                tri->kd = kd;
                tri->ks = ks;
                tri->km = km;
                tri->n = n;

                triangles.push_back(tri);
                index_offset += 3;
            }
        }

        return true;
    }
};