#version 330

layout(location = 0) in vec4 Position;

uniform mat4 CameraMatrix;
uniform mat4 ModelMatrix;

void main() {
	gl_Position = CameraMatrix*ModelMatrix*Position;
}

