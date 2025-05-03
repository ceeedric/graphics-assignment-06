#include <iostream>
#include <filesystem>
#include "Scene.h"
#define TINYOBJLOADER_IMPLEMENTATION

#include "BVH.h"
#include "Plane.h"
#include "Sphere.h"
#include "OBJLoader.h"
#include "tiny_obj_loader.h"

Scene::Scene(bool loadBunny) {
    Light * light1 = new Light(glm::vec3(0.0f, 3.0f, -2.0f), glm::vec3(0.2f, 0.2f, 0.2f));
    Light * light2 = new Light(glm::vec3(-2.0f, 1.0f, 4.0f), glm::vec3(0.5f, 0.5f, 0.5f));

    lights.push_back(light1);
    lights.push_back(light2);

    if (loadBunny) {
        OBJLoader objLoader;
        std::vector<Triangle*> triangles;

        objLoader.LoadOBJ("../../obj/bunny.obj", triangles,
                          glm::vec3(0.1f, 0.1f, 0.1f),
                          glm::vec3(0.0f, 0.0f, 1.0f),
                          glm::vec3(1.0f, 1.0f, 0.5f),
                          glm::vec3(0.0f, 0.0f, 0.0f),
                          100.0f);

        std::cout << triangles.size() << " triangles" << std::endl;
        BVH* bvh = new BVH(triangles);
        bvh->ka = glm::vec3(0.1f, 0.1f, 0.1f);
        bvh->kd = glm::vec3(0.0f, 0.0f, 1.0f);
        bvh->ks = glm::vec3(1.0f, 1.0f, 0.5f);
        bvh->km = glm::vec3(0.0f, 0.0f, 0.0f);
        bvh->n = 100.0f;
        shapes.push_back(bvh);
        return;
    }

    Sphere * sphere1 = new Sphere(glm::vec3(-1.0f, -0.7f, 3.0f), 0.3f);
    sphere1->ka = glm::vec3(0.1f, 0.1f, 0.1f);
    sphere1->kd = glm::vec3(0.2f, 1.0f, 0.2f);
    sphere1->ks = glm::vec3(1.0f, 1.0f, 1.0f);
    sphere1->km = glm::vec3(0.0f, 0.0f, 0.0f);
    sphere1->n = 100.0f;
    shapes.push_back(sphere1);

    Sphere * sphere2 = new Sphere(glm::vec3(1.0f, -0.5f, 3.0f), 0.5f);
    sphere2->ka = glm::vec3(0.1f, 0.1f, 0.1f);
    sphere2->kd = glm::vec3(0.0f, 0.0f, 1.0f);
    sphere2->ks = glm::vec3(1.0f, 1.0f, 1.0f);
    sphere2->km = glm::vec3(0.0f, 0.0f, 0.0f);
    sphere2->n = 10.0f;
    shapes.push_back(sphere2);

    Sphere * sphere3 = new Sphere(glm::vec3(-1.0f, -0.0f, -0.0f), 1.0f);
    sphere3->ka = glm::vec3(0.0f, 0.0f, 0.0f);
    sphere3->kd = glm::vec3(0.0f, 0.0f, 0.0f);
    sphere3->ks = glm::vec3(0.0f, 0.0f, 0.0f);
    sphere3->km = glm::vec3(1.0f, 1.0f, 1.0f);
    sphere3->n = 0.0f;
    shapes.push_back(sphere3);

    Sphere * sphere4 = new Sphere(glm::vec3(1.0f, 0.0f, -1.0f), 1.0f);
    sphere4->ka = glm::vec3(0.0f, 0.0f, 0.0f);
    sphere4->kd = glm::vec3(0.0f, 0.0f, 0.0f);
    sphere4->ks = glm::vec3(0.0f, 0.0f, 0.0f);
    sphere4->km = glm::vec3(0.8f, 0.8f, 0.8f);
    sphere4->n = 0.0f;
    shapes.push_back(sphere4);

    Plane * plane1 = new Plane(glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    plane1->ka = glm::vec3(0.1f, 0.1f, 0.1f);
    plane1->kd = glm::vec3(1.0f, 1.0f, 1.0f);
    plane1->ks = glm::vec3(0.0f, 0.0f, 0.0f);
    plane1->km = glm::vec3(0.0f, 0.0f, 0.0f);
    plane1->n = 0.0f;
    shapes.push_back(plane1);

    Plane * plane2 = new Plane(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    plane2->ka = glm::vec3(0.1f, 0.1f, 0.1f);
    plane2->kd = glm::vec3(1.0f, 1.0f, 1.0f);
    plane2->ks = glm::vec3(0.0f, 0.0f, 0.0f);
    plane2->km = glm::vec3(0.0f, 0.0f, 0.0f);
    plane2->n = 0.0f;
    shapes.push_back(plane2);
}

Scene::~Scene() {
    for (auto & shape : shapes)
        delete shape;

    for (auto & light : lights)
        delete light;

}
