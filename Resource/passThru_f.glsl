/*
	Pass-through Fragment Shader

	Sets the fragment colour to the current front-facing colour.
*/

#version 120

void main()
{
	gl_FragColor = gl_Color;
}