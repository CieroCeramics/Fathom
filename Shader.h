#pragma once
#include "Include.h"
class Shader
{

public:
	Shader();
	Shader(const char* vertexShader, const char* fragmentShader);
	~Shader();

	unsigned int GLSLVertexShaderFromFile(const char* filePath);
	unsigned int GLSLVertexShaderFromFiles(unsigned int numFiles, const char** filePaths);

	unsigned int GLSLFragmentShaderFromFile(const char* filePath);
	unsigned int GLSLFragmentShaderFromFiles(unsigned int numFiles, const char** filePaths);


	// Create shaders by providing raw source strings.

	unsigned int GLSLVertexShaderFromSource(const char* source);
	unsigned int GLSLVertexShaderFromSources(unsigned int numSources, const char** sources);

	unsigned int GLSLFragmentShaderFromSource(const char* source);
	unsigned int GLSLFragmentShaderFromSources(unsigned int numSources, const char** sources);


	// Create a basic GLSL program using previously initialized shader handles. 
	//	A basic program can have a vertex shader, a fragment shader, or both.  
	//	The function also deletes the provided shaders if specified.

	unsigned int GLSLProgram(unsigned int vertexShaderHandle,
		unsigned int fragmentShaderHandle);


	// Create a program handle and perform the complete set up for the shader 
	//	given sources or file paths. Provide a non-null pointer for 'shaderOut' 
	//	to obtain the shader handle; if this value is null, the shader will be 
	//	discarded after the program is created.

	unsigned int GLSLProgramFromFiles(unsigned int numVertexFiles, const char** vertexFilePaths, unsigned int* vertexShaderOut,
		unsigned int numFragmentFiles, const char** fragmentFilePaths, unsigned int* fragmentShaderOut);


	// Create program from source strings.

	unsigned int GLSLProgramFromSources(unsigned int numVertexSources, const char** vertexSources, unsigned int* vertexShaderOut,
		unsigned int numFragmentSources, const char** fragmentSources, unsigned int* fragmentShaderOut);



};

