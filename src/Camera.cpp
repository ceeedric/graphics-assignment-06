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
	float height = focalDistance * tan(fovY / 2.0f) * 2.0f;
	float width = height * aspectRatio;
	float pixelSize = width / static_cast<float>(widthRes);

	glm::vec3 viewDirection = -w;
	glm::vec3 p0 = eye + viewDirection * focalDistance - (width / 2.0f) * u - (height / 2.0f) * v;

	for (int x = 0; x < widthRes; x++) {
		for (int y = 0; y < heightRes; y++) {

			glm::vec3 pixelPosition = p0 + pixelSize * ((static_cast<float>(x) + 0.5f) * u + (static_cast<float>(y) + 0.5f) * v);
			glm::vec3 rayDirection = normalize(pixelPosition - eye);
			glm::vec3 color = RayTrace(eye, rayDirection, scene, 0);

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
	hitShape = nullptr;

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
	if (depth >= MAX_DEPTH)
		return glm::vec3(0, 0, 0);


	float t;
	Shape * shape = nullptr;
	glm::vec3 totalColor = glm::vec3(0, 0, 0);
	if (FindIntersection(origin, direction, scene, t, shape)) {
		glm::vec3 intersectionPoint = origin + t * direction;
		glm::vec3 normal = shape->getNormal(intersectionPoint);

		// ambient light
		totalColor += shape->ka * ambientLightIntensity;

		for (auto light : scene->GetLights()) {
			// Shadow ray direction and length
			glm::vec3 lightDir = normalize(light->position - intersectionPoint);
			float lightDistance = glm::length(light->position - intersectionPoint);

			Shape* shadowHit = nullptr;
			float tShadow;
			glm::vec3 shadowOrigin = intersectionPoint + 0.001f * normal;

			if (FindIntersection(shadowOrigin, lightDir, scene, tShadow, shadowHit) && tShadow < lightDistance)
				continue;

			// diffuse light
			float diffuseIntensity = glm::max(glm::dot(normal, lightDir), 0.0f);
			glm::vec3 diffuse = shape->kd * diffuseIntensity * light->color;
			totalColor += diffuse;

			// specular light
			glm::vec3 reflected = 2 * dot(light->position, normal) * normal - light->position;
			glm::vec3 specular = shape->ks * glm::pow(glm::dot(reflected, eye - intersectionPoint), shape->n);
			totalColor += (specular * light->color);
		}
	}

	return totalColor;
}









