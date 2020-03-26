#include "FBO.h"


FBO::FBO()
{
	height = 720;
	width = 1280;
	colourTextureOut = new GLuint();
	depthTextureOut = new GLuint();


}


FBO::~FBO()
{
}

unsigned int FBO::CreateFBO(FBO dude, unsigned int numColourTarget, bool useDepth, bool useLinearFiltering, bool useHDR)
{
	
		if (!numColourTarget && !useDepth)
		return 0;
		
		unsigned int fboHandle;

		glGenFramebuffers(1, &fboHandle);
		glBindFramebuffer(GL_FRAMEBUFFER, fboHandle);

		GLint texParam = useLinearFiltering ? GL_LINEAR : GL_NEAREST;
	GLint internalFormat = useHDR ? GL_RGBA16 : GL_RGBA8;
	GLint internalType = useHDR ? GL_UNSIGNED_SHORT : GL_UNSIGNED_BYTE;
	
	if (numColourTarget && dude.colourTextureOut)
	{
				//****QUERY THE MAXIMUM NUMBER OF RENDER TARGETS!
		// implement this!

		// proceed with texture creation
		glGenTextures(numColourTarget, dude.colourTextureOut);
		for (unsigned int i=0;
			i< numColourTarget ;
			++ i)
		{
						glBindTexture(GL_TEXTURE_2D, dude.colourTextureOut[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, dude.width, dude.height, 0, 
				GL_RGBA, internalType, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, (GL_COLOR_ATTACHMENT0 + i), 
				GL_TEXTURE_2D, dude.colourTextureOut[i], 0);

		}

	}
	if(useDepth && dude.depthTextureOut)
	{
		glGenTextures(1, dude.depthTextureOut);
		glBindTexture(GL_TEXTURE_2D, *dude.depthTextureOut);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, dude.width, dude.height, 0, 
			GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
			GL_TEXTURE_2D, *dude.depthTextureOut, 0);
	}

	int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
	{
				printf("\n You fail. No cheezburger for you.");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteFramebuffers(1, &fboHandle);
		glDeleteTextures(numColourTarget, dude.colourTextureOut);
		glDeleteTextures(1, dude.depthTextureOut);
		memset(dude.colourTextureOut, 0, numColourTarget*sizeof(int));
		*dude.depthTextureOut = 0;
		return 0;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return fboHandle;
}
