#version 130

#pragma debug(on)
#pragma optimize(off) 

#ifdef PI
#undef PI
#endif
#define PI 3.141592

uniform mat4 Model;
uniform mat4 InversedModel;
uniform mat4 View;
uniform mat4 Projection;

in vec3 Position;
in vec3 VertexNormal;

out vec3 FragmentPosition;
out vec3 Normal;

void main(void)
{
    gl_Position = Projection * View * Model * vec4(Position, 1.0);

	FragmentPosition = vec3(Model * vec4(Position, 1.0));
	mat3 mNormalMatrix = mat3(transpose(InversedModel));
	Normal = mNormalMatrix * VertexNormal;
}
