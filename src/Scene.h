#pragma once
#include <vector>
#include "Shape.h"
#include "Light.h"

class Scene {
public:
	Scene(bool loadBunny = false);
	~Scene();

	const std::vector<Shape*>& GetShapes() const { return shapes; }
	const std::vector<Light*>& GetLights() const { return lights; }

protected:
	std::vector<Shape*> shapes;
	std::vector<Light*> lights;
};
