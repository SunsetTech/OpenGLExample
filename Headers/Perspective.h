#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Perspective {
	private:
		float Width;
		float Height;
		float FOV;
		float zNear;
		float zFar;
		glm::mat4 ProjectionMatrix;
		void UpdateProjectionMatrix();
	public:
		Perspective();
		Perspective(float Width, float Height, float FOV, float zNear, float zFar);
		void SetDimensions(float Width, float Height);
		void SetFOV(float FOV);
		void SetBounds(float zNear, float zFar);
		glm::mat4 GetProjectionMatrix();
};
