/*
 * ShaderProgramBuilder.cpp
 *
 *  Created on: Feb 14, 2012
 *      Author: brachyonic
 */

#include <ShaderProgramBuilder.h>

#include <ShaderProgram.h>
#include <string>

ShaderProgramBuilder::ShaderProgramBuilder( )
{
}

void ShaderProgramBuilder::Declare_Uniform(std::string Name)
{
	this->Uniforms.push_back(Name);
}

ShaderProgram* ShaderProgramBuilder::Build()
{
	return new ShaderProgram(this->Shaders,this->Uniforms);
}

void ShaderProgramBuilder::Attach_Shader(GLuint Shader)
{
	this->Shaders.push_back(Shader);
}

ShaderProgramBuilder::~ShaderProgramBuilder( )
{
}
