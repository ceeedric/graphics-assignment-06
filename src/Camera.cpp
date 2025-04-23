#include "Camera.h"



Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera::Camera(int widthRes, int heightRes)
{
	this->widthRes = widthRes;
	this->heightRes = heightRes;
	renderedImage = new float[widthRes * heightRes * 3];
}

void Camera::TakePicture(Scene *scene) {
    // loop through each pixel
    // on each pixel, first create a ray pointing from the camera to the pixel
    // then call a function to determine the color of the ray -
    //          most computations will be done inside this function
    //          It should be recursive to account for reflections and other things
    // the returned color becomes the color of that pixel and the color should be modified
    // in the renderedImage array

    // Recommended order (see figure 2):
    // 1. Render a sphere without any shadows or anything
    // 2. Add a plane to the scene
    // 3. Shoot shadow rays to be able to render shadows
    // 4. Implement the recursive function call and add a reflective sphere to the scene to test it

	memset(renderedImage, 0, sizeof(float) * widthRes * heightRes * 3);
}
