/*
 * ShaderProgram.cpp
 *
 *  Created on: Feb 14, 2012
 *      Author: brachyonic
 */

#include <ShaderProgram.h>
#include <GL/glew.h>
#include <stdio.h>
#include <string>
#include <map>
#include <Utils.h>

ShaderProgram::ShaderProgram(std::vector<GLuint> Shaders, std::vector<std::string> Uniforms)
{
	this->Handle = LinkProgram(Shaders.data(), Shaders.size());
	for (unsigned int UniformIndex = 0; UniformIndex < Uniforms.size(); UniformIndex++) {
		this->UniformLocations[Uniforms[UniformIndex]] = glGetUniformLocation(this->Handle,Uniforms[UniformIndex].c_str());
	}
}

void ShaderProgram::BindFragDataLocation(GLuint ColorNumber, const char *Name) {
	glBindFragDataLocation(this->Handle, ColorNumber, Name);
}

GLuint ShaderProgram::Get_UniformLocation(std::string Name)
{
	return this->UniformLocations[Name];
}

void ShaderProgram::Activate()
{
	glUseProgram(this->Handle);
}

bool ShaderProgram::Has_Uniform(std::string Name)
{
	return this->UniformLocations.count(Name) > 0;
}

GLuint ShaderProgram::GetHandle() {
	return this->Handle;
}
