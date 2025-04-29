#include "Camera.h"

#include <iostream>
#include <ostream>
#include <glm/glm.hpp>


Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera::Camera(int widthRes, int heightRes,
	   const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up,
	   float fovY, float focalDistance)
{
	this->widthRes = widthRes;
	this->heightRes = heightRes;
	this->eye = eye;
	this->focalDistance = focalDistance;
	this->fovY = fovY;

	glm::vec3 a = eye - lookAt;
	glm::vec3 b = up;
	this->w = normalize(a);
	this->u = normalize(glm::cross(b, w));
	this->v = cross(w, u);
	this->aspectRatio = static_cast<float>(widthRes) / static_cast<float>(heightRes);

	renderedImage = new float[widthRes * heightRes * 3];
}

void Camera::TakePicture(Scene *scene) {
	for (int x = 0; x < widthRes; x++) {
		for (int y = 0; y < heightRes; y++) {

            float height = focalDistance * tan(fovY / 2.0f) * 2.0f;
            float width = height * aspectRatio;
            float pixelSize = width / static_cast<float>(widthRes);

			glm::vec3 viewDirection = -w;
			glm::vec3 p0 = eye - viewDirection * focalDistance - (width / 2.0f) * u - (height / 2.0f) * v;

			glm::vec3 pixelPosition = p0 + pixelSize * ((static_cast<float>(x) + 0.5f) * u + (static_cast<float>(y) + 0.5f) * v);
			glm::vec3 color = RayTrace(pixelPosition, viewDirection, scene, 0);

			//std::cout << color.x << " " << color.y << " " << color.z << std::endl;
			int index = (y * widthRes + x) * 3;
			renderedImage[index + 0] = color[0]; // Red
			renderedImage[index + 1] = color[1]; // Green
			renderedImage[index + 2] = color[2]; // Blue
		}
	}
}

bool Camera::FindIntersection(const glm::vec3& origin, const glm::vec3& direction, Scene* scene, float& t, Shape*& hitShape) {
	float minT = INFINITY;
	for (auto shape : scene->GetShapes()) {
		float currentT;
		if (shape->intersect(origin, direction, currentT)) {
			if (currentT < minT) {
				minT = currentT;
				hitShape = shape;
				t = minT;
			}
		}
	}
	return hitShape != nullptr;
}

glm::vec3 Camera::RayTrace(const glm::vec3& origin, const glm::vec3& direction, Scene* scene, int depth) {

	float t;
	Shape * shape = nullptr;
	glm::vec3 totalColor = glm::vec3(0, 0, 0);
	if (FindIntersection(origin, direction, scene, t, shape)) {
		totalColor = shape->ka * ambientLightIntensity; // ambient light
		for (auto light : scene->GetLights()) {
			glm::vec3 c = glm::vec3(0, 0, 0); // intensity of point light source
			glm::vec3 normal = shape->getNormal(origin);
			glm::vec3 diffuse = c * shape->kd * (glm::dot(light->position, normal) / (light->position.length() * normal.length())); // diffuse
			totalColor += diffuse;

			// specular light
			glm::vec3 viewDir = glm::normalize(eye - t);
			glm::vec3 lightDir = glm::normalize(light->position - t);
			glm::vec3 reflected = 2.0f * glm::dot(normal, lightDir) * normal - lightDir;
			totalColor += shape->ka * ambientLightIntensity + c * (shape->kd * glm::dot(light->position, normal) +
				shape->ks * glm::pow(glm::max(dot(reflected, viewDir), 0.0f), shape->n));
		}
	}

	return totalColor;
}









