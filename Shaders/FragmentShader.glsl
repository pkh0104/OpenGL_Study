#version 130

uniform vec3 LightPosition;
uniform vec3 EyePosition;
uniform vec3 LightColor;
uniform vec3 ObjectColor;

in vec3 FragmentPosition;
in vec3 Normal;

out vec4 FrameBuffer;

void main(void)
{
	// Ambient
	float fAmbientStrength = 0.1f;
	vec3 vAmbient = fAmbientStrength * LightColor;

	// Diffuse
	vec3 vNorm = normalize(Normal);
	vec3 vLightDir =  normalize(LightPosition - FragmentPosition);
	float fDiff = max(dot(vNorm, vLightDir), 0.0);
	vec3 vDiffuse = fDiff * LightColor;

	vec3 vResult = (vAmbient + vDiffuse) * ObjectColor;

	FrameBuffer = vec4(vResult, 1.0f);
}
