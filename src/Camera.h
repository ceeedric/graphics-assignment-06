#include <glm/vec3.hpp>

#include "Scene.h"

class Camera {
public:
	Camera();
	Camera(int widthRes, int heightRes,
		   const glm::vec3& eye, const glm::vec3& lookAt, const glm::vec3& up,
		   float fovY, float focalDistance);
	~Camera();

	void TakePicture(Scene* scene);
	float* GetRenderedImage() { return renderedImage; }

private:
	glm::vec3 RayTrace(const glm::vec3& origin, const glm::vec3& direction, Scene* scene, int depth);

	bool FindIntersection(const glm::vec3& origin, const glm::vec3& direction, Scene* scene, float& t, Shape*& hitShape);

	glm::vec3 eye;
	glm::vec3 w, u, v;
	float fovY;
	float focalDistance;

	int widthRes;
	int heightRes;
	float aspectRatio;
	float* renderedImage;
	glm::vec3 ambientLightIntensity = glm::vec3(1.0f, 1.0f, 1.0f);

	static const int MAX_DEPTH = 5; // change this if performance is low
};
