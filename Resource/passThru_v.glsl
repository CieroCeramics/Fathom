/*
	Pass-through Vertex Shader

	Uses GL's MVP stack to transform the incoming vertex.
*/

#version 120

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_FrontColor = gl_Color;
}