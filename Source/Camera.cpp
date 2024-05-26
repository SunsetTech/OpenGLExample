#include <Camera.h>

Camera::Camera(float Width, float Height, float FOV, float zNear, float zFar) {
	this->Projection = Perspective(
		Width,Height,
		FOV,
		zNear,zFar
	);
}
