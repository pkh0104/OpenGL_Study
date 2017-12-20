// ShaderLoader.cpp
#include "ShaderLoader.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace Core;

CShaderLoader::CShaderLoader(void)
{
}
CShaderLoader::~CShaderLoader(void)
{
}

std::string CShaderLoader::readShader(std::string filename)
{
    std::string ShaderCodeStr;
    std::ifstream FileStrm(filename.c_str(), std::ios::in);

    if(!FileStrm.good()){
        std::cout << "Can't read file" << filename << std::endl;
        std::terminate();
    }

    FileStrm.seekg(0, std::ios::end);
    ShaderCodeStr.resize( static_cast<unsigned int>(FileStrm.tellg()) );
    FileStrm.seekg(0, std::ios::beg);
    FileStrm.read(&ShaderCodeStr[0], ShaderCodeStr.size());
    FileStrm.close();

    return ShaderCodeStr;
}

GLuint CShaderLoader::createShader(GLenum shaderType, std::string source, std::string shadername)
{
    int iCompileRst = 0;

    GLuint Shader = glCreateShader(shaderType);
    const char *pShaderCodePtr = source.c_str();
    const int iShaderCodeSize = source.size();

    glShaderSource(Shader, 1, &pShaderCodePtr, &iShaderCodeSize);
    glCompileShader(Shader);
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &iCompileRst);

    if(iCompileRst == GL_FALSE){
        int iInfoLogLengh = 0;
        glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &iInfoLogLengh);
        std::vector<char> ShaderLogVec(iInfoLogLengh);
        glGetShaderInfoLog(Shader, iInfoLogLengh, NULL, &ShaderLogVec[0]);
        std::cout << "ERROR compiling shader:" << shadername << std::endl << &ShaderLogVec[0] << std::endl;
        return 0;
    }

    return Shader;
}

GLuint CShaderLoader::createProgram(std::string vertexshaderfilename, std::string fragmentshaderfilename)
{
    std::string VertexShaderCodeStr = readShader(vertexshaderfilename);
    std::string FragmentShaderCodeStr = readShader(fragmentshaderfilename);

    GLuint VertexShader = createShader(GL_VERTEX_SHADER, VertexShaderCodeStr, std::string("vertex shader"));
    GLuint FragmentShader = createShader(GL_FRAGMENT_SHADER, FragmentShaderCodeStr, std::string("fragment shader"));

    int iLinkRst = 0;

    GLuint Program = glCreateProgram();
    glAttachShader(Program, VertexShader);
    glAttachShader(Program, FragmentShader);

    glLinkProgram(Program);
    glGetProgramiv(Program, GL_LINK_STATUS, &iLinkRst);

    if(iLinkRst == GL_FALSE){
        int iInfoLogLengh = 0;
        glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &iInfoLogLengh);
        std::vector<char> ProgramLogVec(iInfoLogLengh);
        glGetProgramInfoLog(Program, iInfoLogLengh, NULL, &ProgramLogVec[0]);
        std::cout << "Shader loader : LINK ERROR" << std::endl << &ProgramLogVec[0] << std::endl;
        return 0;
    }

    return Program;
}

