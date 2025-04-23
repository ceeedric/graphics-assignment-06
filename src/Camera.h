#pragma once
#include <vector>
#include "Scene.h"



class Camera
{
public:
	Camera();
	~Camera();

	Camera(int widthRes, int heightRes);

	void TakePicture(Scene *scene);
	float* GetRenderedImage() { return renderedImage; };

private:

	int widthRes;
	int heightRes;

	float *renderedImage;


};
