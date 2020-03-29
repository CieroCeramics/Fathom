#pragma once

#include "Texture.h"
#include "Include.h"

#include<vector>
class FBO
{
public:
	FBO();
	~FBO();
	//unsigned int CreateFBO(FBO dude, unsigned int numColourTarget, bool useDepth, bool useLinearFiltering, bool useHDR);

	void setTextureSize(int wifth, int height);
	int getTextureSize(int choice);

	void InitFrameBuffer();
	void InitRenderBuffer();
	void InitTexture();
	void initDepthTexture();

	void bind();
	void unbind(unsigned int type);
	void addColourTexture(unsigned int *textureHandle);
	Texture* get();


private:
	 unsigned int _height;
	 unsigned int _width;

	unsigned int _frameBuffer;
	std::vector <unsigned int>* colourTextureOut;
	unsigned int* depthTextureOut;
	Texture* _texture;

	bool useLinearFiltering;
	bool useHDR;
	bool useDepth;
};

