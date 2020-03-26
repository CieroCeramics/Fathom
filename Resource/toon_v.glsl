/*
	Toon vertex shader
	
	Transforms vertex and sends required variables to 
	fragment shader for toon shading.
*/


#version 120


// 2 varyings
varying vec2 texcoord;
varying vec3 normal;


void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_FrontColor = gl_Color;
	texcoord = gl_MultiTexCoord0.st;
	normal = gl_NormalMatrix*gl_Normal;
	//eyePos = vec3(gl_ModelViewMatrix * gl_Vertex);
}