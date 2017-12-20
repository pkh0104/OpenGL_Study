// ShaderLoader.h
#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>

namespace Core
{
    class CShaderLoader
    {
        private:
            std::string readShader(std::string filename);
            GLuint createShader(GLenum shaderType, std::string source, std::string shaderName);
        public:
            CShaderLoader(void);
            ~CShaderLoader(void);
            GLuint createProgram(std::string vertexshaderfilename, std::string fragmentshaderfilename);
    };
}
