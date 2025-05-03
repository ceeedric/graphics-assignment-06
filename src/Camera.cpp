#include "Camera.h"

#include <iostream>
#include <ostream>
#include <glm/glm.hpp>

#include "BVH.h"


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
			renderedImage[index + 0] = glm::clamp(color.r, 0.0f, 1.0f); // Red
			renderedImage[index + 1] = glm::clamp(color.g, 0.0f, 1.0f); // Green
			renderedImage[index + 2] = glm::clamp(color.b, 0.0f, 1.0f); // Blue
		}
	}
}

bool Camera::FindIntersection(const glm::vec3& origin, const glm::vec3& direction, Scene* scene, float& t, Shape*& hitShape) {
	float minT = INFINITY;
	hitShape = nullptr;

	for (Shape * shape : scene->GetShapes()) {
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
		// ambient light
		totalColor = shape->ka * ambientLightIntensity;
		glm::vec3 ray = origin + t * direction;
		glm::vec3 normal = shape->getNormal(ray);


		for (auto light : scene->GetLights()) {
			glm::vec3 l = glm::normalize(light->position - ray);
			glm::vec3 shadowOrigin = ray + 0.0001f * normal;
			float shadowT;
			Shape* shadowHit = nullptr;
			float lightDistance = glm::length(light->position - ray);
			if (FindIntersection(shadowOrigin, l, scene, shadowT, shadowHit) && shadowT < lightDistance)
				continue;

			// diffuse light
			glm::vec3 diffuse = shape->kd * glm::max(glm::dot(l, normal), 0.0f);
			totalColor += diffuse * light->color;

			// specular light
			glm::vec3 reflected = 2 * dot(l, normal) * normal - l;
			glm::vec3 e = glm::normalize(eye - ray);
			float specular = glm::pow(dot(reflected, e), shape->n);
			totalColor += (light->color * shape->ks * specular);
		}

		if (glm::length(shape->km) > 0.0f) {
			// since V in the slides goes out of the surface and our direction goes into it, we
			// must flip it to still use the same formula as the slides
			glm::vec3 v = -direction;
			glm::vec3 reflectionDir = normalize(2.0f * glm::dot(v, normal) * normal - v);
			glm::vec3 reflectionRay = ray + 0.0001f * reflectionDir; // shoot the ray
			glm::vec3 reflectedColor = RayTrace(reflectionRay, reflectionDir, scene, depth + 1);
			totalColor += shape->km * reflectedColor;
		}
	}

	return totalColor;
}









