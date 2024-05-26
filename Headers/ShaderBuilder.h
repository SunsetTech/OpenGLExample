/*
 * ShaderBuilder.h
 *
 *  Created on: Feb 14, 2012
 *      Author: brachyonic
 */

#ifndef SHADERBUILDER_H_
#define SHADERBUILDER_H_
#include <GL/glew.h>
#include <vector>
#include <string>


class ShaderBuilder {
    private:
        std::vector<std::string> SourceStrings;
        GLenum Type;
    public:
        ShaderBuilder(GLenum Type);
        void Add_Source(const std::string& Source);
        GLuint Compile();
        virtual ~ShaderBuilder();
};

		
#endif /* SHADERBUILDER_H_ */
