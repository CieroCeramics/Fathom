#include "FBO.h"

using namespace std;
FBO::FBO()
{
	_height = 720;
	_width = 1280;
	colourTextureOut = new vector <unsigned int> {};
	depthTextureOut = new unsigned int();
	_texture = new Texture();


}

FBO::~FBO()
{
	glDeleteFramebuffersEXT(1, &_frameBuffer); //Deletes frame buffer
	//glDeleteRenderbuffersEXT(1, &_depthBuffer); //Deletes render buffer
}


void FBO::setTextureSize(int width, int height)
{
	_width = width;
	_height = height;
}

void FBO::InitFrameBuffer(void)
{
	// if (!numColourTarget && !useDepth)
	// 	return 0;
	// //	unsigned int fboHandle;


		glGenFramebuffers(1, &_frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);


		GLint texParam = useLinearFiltering ? GL_LINEAR : GL_NEAREST;
	GLint internalFormat = useHDR ? GL_RGBA16 : GL_RGBA8;
	GLint internalType = useHDR ? GL_UNSIGNED_SHORT : GL_UNSIGNED_BYTE;
	
}

void FBO::InitTexture()
{
	if (colourTextureOut->size() && &colourTextureOut[0])
	{
				//****QUERY THE MAXIMUM NUMBER OF RENDER TARGETS!
		// implement this!
	GLint texParam = useLinearFiltering ? GL_LINEAR : GL_NEAREST;
	GLint internalFormat = useHDR ? GL_RGBA16 : GL_RGBA8;
	GLint internalType = useHDR ? GL_UNSIGNED_SHORT : GL_UNSIGNED_BYTE;
		// proceed with texture creation
		glGenTextures(colourTextureOut->size(),  colourTextureOut->data());
		for (unsigned int i=0;
			i< colourTextureOut->size() ;
			++ i)
		{
						glBindTexture(GL_TEXTURE_2D, colourTextureOut->at(i));
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, 
				GL_RGBA, internalType, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, (GL_COLOR_ATTACHMENT0 + i), 
				GL_TEXTURE_2D, colourTextureOut->at(i), 0);

		}

	}
}

void FBO::initDepthTexture()
{
	GLint texParam = useLinearFiltering ? GL_LINEAR : GL_NEAREST;
	if(useDepth && depthTextureOut)
	{
		glGenTextures(1, depthTextureOut);
		glBindTexture(GL_TEXTURE_2D, *depthTextureOut);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, 
			GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texParam);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
			GL_TEXTURE_2D, *depthTextureOut, 0);
	}
	else
	{
		printf("failed to bind depth Texture");
	}
	

}

void FBO::bind()
{
	
		
		
	

	
	
	int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status != GL_FRAMEBUFFER_COMPLETE)
	{
				printf("\n failed to bind FBO\n.");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteFramebuffers(1, &_frameBuffer);
		glDeleteTextures(colourTextureOut->size(), colourTextureOut->data());
		glDeleteTextures(1, depthTextureOut);
		memset(colourTextureOut->data(), 0, colourTextureOut->size()*sizeof(int));
		*depthTextureOut = 0;
	//	return 0;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//return _frameBuffer;
}

void FBO::addColourTexture(unsigned int* handle)
{
	colourTextureOut->push_back(*handle);
}
//unsigned int FBO::CreateFBO(FBO  unsigned int numColourTarget, bool useDepth, bool useLinearFiltering, bool useHDR)
