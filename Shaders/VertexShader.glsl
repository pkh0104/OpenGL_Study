#version 130

#pragma debug(on)
#pragma optimize(off) 

#ifdef PI
#undef PI
#endif
#define PI 3.141592

layout (location = 0) in vec4 position;

void main(void)
{
////const vec4 vertices[3] = vec4[3]( vec4( 0.25, -0.25, 0.5, 1.0),
////								  vec4(-0.25, -0.25, 0.5, 1.0),	
////								  vec4( 0.25,  0.25, 0.5, 1.0) );
////gl_Position = vertices[gl_VertexID];
    gl_Position = position;
}
