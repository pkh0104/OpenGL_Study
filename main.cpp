// main.cpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include "Core/ShaderLoader.h"

using namespace Core;

GLuint g_Program;

void renderScene(void)
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(g_Program);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint VertexBufferID;
    glGenBuffers(1, &VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);

    static const GLfloat VertexBufferData[] = {
         0.25, -0.25, 0.5, 1.0,
        -0.25, -0.25, 0.5, 1.0,
         0.25,  0.25, 0.5, 1.0 
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferData), VertexBufferData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glutSwapBuffers();
}

void init()
{
    glEnable(GL_DEPTH_TEST);

    Core::CShaderLoader ShaderLoader;
    g_Program = ShaderLoader.createProgram( std::string("Shaders/VertexShader.glsl"), std::string("Shaders/FragmentShader.glsl") );

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Drawing my first triangle with GLSL");
    glewInit();

    std::cout << "GL   version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    init();

    glutDisplayFunc(renderScene);
    glutMainLoop();
    glDeleteProgram(g_Program);

    return 0;
}
