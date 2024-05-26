/*
 * Engine.h
 *
 *  Created on: Jan 25, 2012
 *      Author: brachyonic
 */
#ifndef GLUTILS_H_
#define GLUTILS_H_

#include <GL/glew.h>
void DumpGLData();
GLuint CompileShader(GLenum Type, const char** Strings, int* Lengths, unsigned int Count);
GLuint LinkProgram(GLuint* Shaders, unsigned int Count);

#endif /* GLUTILS_H_ */
