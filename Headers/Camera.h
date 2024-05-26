#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include <Perspective.h>

class Camera {
	public:
		Perspective Projection;
		glm::mat4 Transform;
		Camera(float Width, float Height, float FOV, float zNear, float zFar);
};
