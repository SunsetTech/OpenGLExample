/*
 * ShaderProgram.h
 *
 *  Created on: Feb 14, 2012
 *      Author: brachyonic
 */

#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_
#include <vector>
#include <map>
#include <string>
#include <GL/glew.h>

class ShaderProgram {
	private:
		GLuint Handle;
		std::map<std::string,GLuint> UniformLocations;
	public:
		ShaderProgram(std::vector<GLuint> Shaders, std::vector<std::string> Uniforms);
		void BindFragDataLocation(GLuint ColorNumber, const char *Name);
		GLuint Get_UniformLocation(std::string Name);
		bool Has_Uniform(std::string Name);
		void Activate();
		GLuint GetHandle();
};
#endif /* SHADERPROGRAM_H_ */
