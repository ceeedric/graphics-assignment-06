#include "Scene.h"

#include "Sphere.h"

Scene::Scene(bool loadBunny) {
    Light * light1 = new Light(glm::vec3(0.0f, 3.0f, -2.0f), glm::vec3(0.2f, 0.2f, 0.2f));
    Light * light2 = new Light(glm::vec3(-2.0f, 1.0f, 4.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    lights.push_back(light1);
    lights.push_back(light2);

    Sphere * sphere1 = new Sphere(glm::vec3(-1.0f, -0.7f, 3.0f), 0.3f);
    sphere1->ka = glm::vec3(0.1f, 0.1f, 0.1);
    sphere1->kd = glm::vec3(0.2f, 1.0f, 0.2);
    sphere1->ks = glm::vec3(1.0f, 1.0f, 1.0);
    sphere1->km = glm::vec3(0.0f, 0.0f, 0.0);
    sphere1->n = 100.0f;
    shapes.push_back(sphere1);
}

Scene::~Scene() {
    for (auto & shape : shapes)
        delete shape;

    for (auto & light : lights)
        delete light;

}
