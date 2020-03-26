/*
	GLSL Fathom
	By Mackenzie Sturrup

	Version 1.0


	GLSL FATHOM SDK is a small utility kit containing functions to help 
	create shaders and programs with GLSL (OpenGL Shading Language). The 
	abstract interface is designed carefully to promote reusability with GLSL 
	shaders. Users can choose to load shader sources from files, or provide 
	hard-coded shader source. Programs may be created using a set of source 
	files, hard-coded source, or pre-created shaders, with the option to save 
	or delete the shader handles being provided.
	
	All functions return a valid handle (non-zero unsigned int) if success, or 
	zero if the function fails.

	Library is built using static linkage.
*/


#ifndef _GLSLFATHOM_H
#define _GLSLFATHOM_H


// GLSL FATHOM may be used in C++ programs
#ifdef __cplusplus
extern "C" {
#endif	// __cplusplus


// Create a GLSL vertex or fragment shader which can be reused for multiple 
//	programs. These functions create shaders by loading sources from directly 
//	from files (easier to use).

unsigned int GLSLVertexShaderFromFile(const char *filePath);
unsigned int GLSLVertexShaderFromFiles(unsigned int numFiles, const char **filePaths);

unsigned int GLSLFragmentShaderFromFile(const char *filePath);
unsigned int GLSLFragmentShaderFromFiles(unsigned int numFiles, const char **filePaths);


// Create shaders by providing raw source strings.

unsigned int GLSLVertexShaderFromSource(const char *source);
unsigned int GLSLVertexShaderFromSources(unsigned int numSources, const char **sources);

unsigned int GLSLFragmentShaderFromSource(const char *source);
unsigned int GLSLFragmentShaderFromSources(unsigned int numSources, const char **sources);


// Create a basic GLSL program using previously initialized shader handles. 
//	A basic program can have a vertex shader, a fragment shader, or both.  
//	The function also deletes the provided shaders if specified.

unsigned int GLSLProgram(unsigned int vertexShaderHandle, 
						 unsigned int fragmentShaderHandle);


// Create a program handle and perform the complete set up for the shader 
//	given sources or file paths. Provide a non-null pointer for 'shaderOut' 
//	to obtain the shader handle; if this value is null, the shader will be 
//	discarded after the program is created.

unsigned int GLSLProgramFromFiles(unsigned int numVertexFiles, const char **vertexFilePaths, unsigned int *vertexShaderOut, 
								  unsigned int numFragmentFiles, const char **fragmentFilePaths, unsigned int *fragmentShaderOut);


// Create program from source strings.

unsigned int GLSLProgramFromSources(unsigned int numVertexSources, const char **vertexSources, unsigned int *vertexShaderOut, 
									unsigned int numFragmentSources, const char **fragmentSources, unsigned int *fragmentShaderOut);


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// _GLSLFATHOM_H