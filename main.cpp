// main.cpp

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>

#include <EGL/egl.h>
#include "Core/ShaderLoader.h"
#include "Core/glExtension.h"

using namespace Core;

GLuint g_Program;

static const float vCube[] =
{
	// Front
	-0.5f,  0.5f, 0.5f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f,
	 0.5f,  0.5f, 0.5f, 1.0f,
	 0.5f,  0.5f, 0.5f, 1.0f,
	-0.5f, -0.5f, 0.5f, 1.0f,
	 0.5f, -0.5f, 0.5f, 1.0f,
	// Right
	 0.5f,  0.5f,  0.5f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f,
	// Back
	 0.5f,  0.5f, -0.5f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f,
	// Left
	-0.5f,  0.5f, -0.5f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f,
	// Top
	-0.5f,  0.5f, -0.5f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f,
	// Bottom
	-0.5f, -0.5f,  0.5f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f
};

static const float vCubeColors[] =
{
	// Front (RED)
	1.0f, 0.0f, 0.0f, 0.5f,
	1.0f, 0.0f, 0.0f, 0.5f,
	1.0f, 0.0f, 0.0f, 0.5f,
	1.0f, 0.0f, 0.0f, 0.5f,
	1.0f, 0.0f, 0.0f, 0.5f,
	1.0f, 0.0f, 0.0f, 0.5f,

	// Right (GREEN)
	0.0f, 1.0f, 0.0f, 0.5f,
	0.0f, 1.0f, 0.0f, 0.5f,
	0.0f, 1.0f, 0.0f, 0.5f,
	0.0f, 1.0f, 0.0f, 0.5f,
	0.0f, 1.0f, 0.0f, 0.5f,
	0.0f, 1.0f, 0.0f, 0.5f,

	// Back (
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f, 1.0f,

	// Left (BLUE)
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,

	// Top
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, 1.0f, 0.0f, 1.0f,

	// Bottom
	0.5f, 0.5f, 0.5f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f
};

static const float vCubeNormal[] =
{
	// Front face
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,

	// Right face
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,

	// Back face
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,

	// Left face
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,

	// Top face
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,

	// Bottom face
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f
};

void renderScene(void)
{
	GLfloat fWidth = 800.0;
	GLfloat fHeight = 600.0;
	float fAspect = fHeight / fWidth;
	//float fAspect = 0.9;
	glViewport( 0, 0, static_cast<GLsizei>(fWidth), static_cast<GLsizei>(fHeight) );

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint uiPositionLoc = glGetAttribLocation(g_Program, "Position");
	GLuint uiColorLoc = glGetAttribLocation(g_Program, "Color");
	GLuint uiMVPLoc = glGetUniformLocation(g_Program, "MVP");

	GLuint VertexBufferID;
	glGenBuffers(1, &VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vCube), vCube, GL_STATIC_DRAW);

	GLuint ColorBufferID;
	glGenBuffers(1, &ColorBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vCubeColors), vCubeColors, GL_STATIC_DRAW);

	glUseProgram(g_Program);

	/*
	static const GLfloat VertexBufferData[] = {
		0.25, -0.25, 0.5, 1.0,
		-0.25, -0.25, 0.5, 1.0,
		0.25,  0.25, 0.5, 1.0 
	};
	*/

	//glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferData), VertexBufferData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
	glEnableVertexAttribArray(uiPositionLoc);
	glVertexAttribPointer(uiPositionLoc, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferID);
	glEnableVertexAttribArray(uiColorLoc);
	glVertexAttribPointer(uiColorLoc, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)0);

	GLfloat model[16], mvp[16], view[16];
	GLfloat fScale = 0.5f;
	GLfloat fRotateX = -30.0f;
	GLfloat fRotateY = 45.0f;
	GLfloat mRotX[16], mRotY[16], mRotZ[16], mResult[16];

	glExtRotateX(fRotateX, mRotX);
	glExtRotateY(fRotateY, mRotY);
	glExtMultiply(model, mRotX, mRotY);
	glExtFrustum(view, -2.0, 2.0, -2.0 * fAspect, 2.0 * fAspect, -2.0, 2.0);
	glExtMultiply(mvp, view, model);
	glUniformMatrix4fv(uiMVPLoc, 1, GL_FALSE, mvp);

    glDrawArrays(GL_TRIANGLES, 0, 36);

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
