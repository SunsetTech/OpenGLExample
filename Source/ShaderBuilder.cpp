/*
 * ShaderBuilder.cpp
 *
 *  Created on: Feb 14, 2012
 *      Author: brachyonic
 */

#include <ShaderBuilder.h>
#include <GL/glew.h>
#include <stdlib.h>
#include <string>
#include <Utils.h>

ShaderBuilder::ShaderBuilder(GLenum Type) : Type(Type) {
}

void ShaderBuilder::Add_Source(const std::string& Source) {
    SourceStrings.push_back(Source);
}

GLuint ShaderBuilder::Compile() {
    std::vector<const char*> cStrings;
    std::vector<GLint> lengths;

    // Populate the temporary vectors
    for (const auto& str : SourceStrings) {
        cStrings.push_back(str.c_str());
        lengths.push_back(static_cast<GLint>(str.length()));
    }

    // Pass the data directly from temporary vectors
    return CompileShader(
        Type,
        cStrings.data(),
        lengths.data(),
        static_cast<GLsizei>(SourceStrings.size())
    );
}

ShaderBuilder::~ShaderBuilder() {
}

