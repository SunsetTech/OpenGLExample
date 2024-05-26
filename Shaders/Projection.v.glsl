#version 330

layout(location = 0) in vec4 Position;

uniform mat4 TransformationMatrix;

void main() {
	gl_Position = TransformationMatrix*Position;
}

