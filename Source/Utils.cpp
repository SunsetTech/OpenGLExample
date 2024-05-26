/*
 * Engine.c
 *
 *  Created on: Jan 25, 2012
 *      Author: brachyonic
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <GL/glew.h>
#include <Utils.h>

static void ShowInfoLog(GLuint object, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog) {
	GLint log_length;
	glGet__iv(object, GL_INFO_LOG_LENGTH, &log_length);
	char *log = (char*)malloc(log_length);
	glGet__InfoLog(object, log_length, NULL, log);
	fprintf(stderr, "%s", log);
	free(log);
}
void DumpGLData(GLuint ProgramHandle) {
	GLint AttributeCount,AttributeMaxNameLength;
	glGetProgramiv(ProgramHandle,GL_ACTIVE_ATTRIBUTES,&AttributeCount);glGetProgramiv(ProgramHandle,GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,&AttributeMaxNameLength);
	GLint UniformCount,UniformMaxNameLength;
	glGetProgramiv(ProgramHandle,GL_ACTIVE_UNIFORMS,&UniformCount);glGetProgramiv(ProgramHandle,GL_ACTIVE_UNIFORM_MAX_LENGTH,&UniformMaxNameLength);
	fprintf(stderr,"Shader %i\n",ProgramHandle);fprintf(stderr,"\t%i Attributes\n",AttributeCount);
	for (int AttributeIndex = 0; AttributeIndex < AttributeCount; AttributeIndex++) {
		GLsizei NameLength;GLint Size;GLenum Type;GLchar *Name = (GLchar*)calloc(AttributeMaxNameLength,sizeof(GLchar));
		glGetActiveAttrib(ProgramHandle,AttributeIndex,AttributeMaxNameLength,&NameLength,&Size,&Type,Name);
		fprintf(stderr,"\t\tAttribute %s (Location: %i, Size: %i, Type: %i)\n",Name,AttributeIndex,Size,Type);
		free(Name);
		GLuint Buffer, Enabled, DataSize, DataType;
		glGetVertexAttribIuiv(AttributeIndex,GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING,&Buffer);glGetVertexAttribIuiv(AttributeIndex,GL_VERTEX_ATTRIB_ARRAY_ENABLED,&Enabled);glGetVertexAttribIuiv(AttributeIndex,GL_VERTEX_ATTRIB_ARRAY_SIZE,&DataSize);glGetVertexAttribIuiv(AttributeIndex,GL_VERTEX_ATTRIB_ARRAY_TYPE,&DataType);
		fprintf(stderr,"\t\t\tBuffer: %i, Enabled: %i, DataSize: %i, DataType: %i\n",Buffer,Enabled,DataSize,DataType);
	}
	fprintf(stderr,"\t%i Uniforms\n",UniformCount);
	for (int UniformIndex = 0; UniformIndex < UniformCount; UniformIndex++) {
		GLsizei NameLength;GLint Size;GLenum Type;GLchar *Name = (GLchar*)calloc(UniformMaxNameLength,sizeof(GLchar));
		glGetActiveUniform(ProgramHandle,UniformIndex,UniformMaxNameLength,&NameLength,&Size,&Type,Name);
		fprintf(stderr,"\t\tUniform %s (Location: %i, Size: %i, Type: %i)\n",Name,UniformIndex,Size,Type);
		free(Name);
	}

}
GLuint CompileShader(GLenum Type, const char** Strings, int* Lengths, unsigned int Count) {
	GLint ShaderOK;
	GLuint ShaderHandle = glCreateShader(Type);
	glShaderSource(ShaderHandle,Count,Strings,Lengths);
	glCompileShader(ShaderHandle);
	glGetShaderiv(ShaderHandle,GL_COMPILE_STATUS,&ShaderOK);
	if (!ShaderOK) {
		ShowInfoLog(ShaderHandle,glGetShaderiv,glGetShaderInfoLog);
		glDeleteShader(ShaderHandle);
		return 0;
	}
	return ShaderHandle;
}
GLuint LinkProgram(GLuint* Shaders, unsigned int Count) {
	GLuint ProgramHandle = glCreateProgram();
	for (unsigned int ShaderIndex = 0; ShaderIndex < Count; ShaderIndex++) {
		glAttachShader(ProgramHandle,Shaders[ShaderIndex]);
	}
	GLint ProgramOK;
	glLinkProgram(ProgramHandle);
	glGetProgramiv(ProgramHandle,GL_LINK_STATUS,&ProgramOK);
	if (!ProgramOK) {
		ShowInfoLog(ProgramHandle, glGetProgramiv, glGetProgramInfoLog);
		glDeleteProgram(ProgramHandle);
		return 0;
	}
	return ProgramHandle;
}

