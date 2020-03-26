#pragma once

#include "Include.h"
class FBO
{
public:
	FBO();
	~FBO();
	unsigned int CreateFBO(FBO dude, unsigned int numColourTarget, bool useDepth, bool useLinearFiltering, bool useHDR);



	unsigned int height;
	unsigned int width;

	GLuint* colourTextureOut;
	GLuint* depthTextureOut;
};

