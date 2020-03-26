/*
	Uniform Colour Fragment Shader

	Sets the fragment colour to an externally-set value.
*/

#version 120

uniform vec4 colour;

void main()
{
	gl_FragColor = colour;
}