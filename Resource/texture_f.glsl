/*
	Texture-sampled Fragment Shader

	Sets the fragment colour to a pixel sampled from a texture.
*/

#version 120

uniform sampler2D tex;

void main()
{
	gl_FragColor = texture2D(tex, gl_TexCoord[0].st);
}