/*
 * ShaderProgramBuilder.h
 *
 *  Created on: Feb 14, 2012
 *      Author: brachyonic
 */

#ifndef SHADERPROGRAMBUILDER_H_
#define SHADERPROGRAMBUILDER_H_
#include <vector>
#include "ShaderProgram.h"
#include <string>


class ShaderProgramBuilder {
	private:
		std::vector<GLuint> Shaders;
		std::vector<std::string> Uniforms;
	public:
		ShaderProgramBuilder();
		void Attach_Shader(GLuint Shader);
		void Declare_Uniform(std::string Name);
		ShaderProgram* Build();
		virtual ~ShaderProgramBuilder( );
};

#endif /* SHADERPROGRAMBUILDER_H_ */
