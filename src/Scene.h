#pragma once
#include <vector>
#include "Shape.h"
#include "Light.h"


class Scene
{
public:
	Scene();
	~Scene();

private:
	std::vector<Shape*> shapes;
	std::vector<Light*> lights;

};
