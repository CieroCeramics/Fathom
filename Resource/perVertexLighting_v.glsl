/*
	Per-vertex Lighting
	Vertex Shader

	Computes lighting on the incoming vertex. Colour is 
	interpolated between vertices for modest-looking shading.
*/

#version 120

void main()
{
	// simulating eye-space POINT light
	vec3 lightPos = vec3(1.0, 8.0, 5.0);

	vec3 eyePos = vec3(gl_ModelViewMatrix * gl_Vertex);

	vec3 lightDisplacement = lightPos - eyePos;

	vec3 normal = gl_NormalMatrix * gl_Normal;

	float diffuseCoefficient = dot( normalize(normal), normalize(lightDisplacement) );

	gl_FrontColor.xyz = diffuseCoefficient * gl_Color.rgb;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}