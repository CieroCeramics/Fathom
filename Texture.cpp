#include "Texture.h"

Texture::Texture()
{

}

Texture::Texture(char* textureName)
{
	load(textureName);
}

Texture::~Texture()
{

}

void Texture::load(char* textureName)
{
	char texturePath[99] = "TexturesSimple/"; //Creates a character array of size 99 and stores path
	strcat_s(texturePath, textureName); //Adds textureName to texturePath to give full path

	std::cout << "Loading Texture: " << textureName << "." << std::endl;	

	_texture = ilutGLLoadImage(texturePath);
	setTextureName(textureName);

	//Red book page 411 to page 428
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

GLubyte Texture::get()
{
	return _texture;
}

void Texture::set(GLuint &texID)
{
	_texture = (GLubyte) texID;
}

void Texture::setTextureName(char* textureName)
{
	_textureName = textureName;
}

std::string Texture::getTextureName()
{
	return _textureName;
}
