#version 130

#pragma debug(on)
#pragma optimize(off) 

#ifdef PI
#undef PI
#endif
#define PI 3.141592

uniform mat4 MVP;
in vec4 Position;
in vec4 Color;
out vec4 vColor;

void main(void)
{
    gl_Position = MVP * Position;
	vColor = Color;
}
