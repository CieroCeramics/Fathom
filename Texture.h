//This is a class that deals with the loading of textures

#pragma once

#include <iostream>

#include "Include.h"

//#include "Include\GL\freeglut.h"
//#include "Include\IL\ilut.h"

class Texture
{
public:
	Texture();
	Texture(char* textureName);
	~Texture();

	void load(char* textureName);
	GLubyte get();
	void set(GLuint &texID);

	void setTextureName(char* textureName);
	std::string getTextureName();

protected:
	GLubyte _texture;
	std::string _textureName;
};