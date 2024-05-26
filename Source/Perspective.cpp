#include <Perspective.h>

Perspective::Perspective() {
}

Perspective::Perspective(float Width, float Height, float FOV, float zNear, float zFar) {
	this->Width = Width;
	this->Height = Height;
	this->FOV = glm::radians(FOV);
	this->zNear = zNear;
	this->zFar = zFar;
	this->UpdateProjectionMatrix();
}

void Perspective::SetDimensions(float Width, float Height) {
	this->Width = Width;
	this->Height = Height;
	this->UpdateProjectionMatrix();
}

void Perspective::SetFOV(float FOV) {
	this->FOV = glm::radians(FOV);
	this->UpdateProjectionMatrix();
}

void Perspective::SetBounds(float zNear, float zFar) {
	this->zNear = zNear;
	this->zFar = zFar;
	this->UpdateProjectionMatrix();
}

void Perspective::UpdateProjectionMatrix() {
	this->ProjectionMatrix = glm::perspective(
		this->FOV,
		this->Width/this->Height,
		this->zNear,
		this->zFar
	);
}

glm::mat4 Perspective::GetProjectionMatrix() {
	return this->ProjectionMatrix;
}
