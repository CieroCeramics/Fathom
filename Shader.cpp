
#include <iostream>
//#include <iomanip>
#include <fstream>
#include<vector>

#include "Shader.h"

using namespace std;


Shader::Shader()//const char* vertexShader, const char *fragmentShader)
{
	//_programName = "NGenesis"; //Hard coded even though I hate
	//_fileName = shaderFileName;
	//_funcName = shaderName;

	//initCg();
}

Shader::~Shader()
{

}
int unloadshader(const char** ShaderSource)
{
	if (*ShaderSource != 0)
		delete[] * ShaderSource;
	*ShaderSource = 0;

	return 0;
}


unsigned long getFileLength(ifstream& file)
{
	if (!file.good()) return 0;

	unsigned long pos = file.tellg();
	file.seekg(0, ios::end);
	unsigned long len = file.tellg();
	file.seekg(ios::beg);

	return len;
}
unsigned int Shader::GLSLVertexShaderFromFile(const char* filePath)
{
	ifstream file;
	file.open(filePath, ios::in);// open in ascii
	if (!file) return -1;

	unsigned long len = getFileLength(file);
	char* src;
	src = (char*) new char[len + 1];
	if (*src == 0) return -3;   // can't reserve memory

	unsigned int i = 0;
	while (file.good())
	{
		src[i] = file.get();       // get character from file.
		if (!file.eof())
			i++;
	}

	src[i] = 0;  // 0-terminate it at the correct position

	file.close();
	int vlen = len;
	const char* ShaderSource;
	ShaderSource = src;

	unsigned int vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObject, 1, &ShaderSource, &vlen);
	glCompileShader(vertexShaderObject);

	int compiled;
	//glgetobjectpar
	glGetObjectParameterivARB(vertexShaderObject, GL_COMPILE_STATUS, &compiled);
	if (compiled)
	{
		// yes it compiled!
	}

	int blen = 0;
	int slen = 0;

	glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &blen);
	if (blen > 1)
	{
		char* compiler_log = (char*)malloc(blen);
		glGetInfoLogARB(vertexShaderObject, blen, &slen, compiler_log);
		std::cout << ("compiler_log:\n", compiler_log);
		free(compiler_log);
	}
	return vertexShaderObject; // No Error
}

unsigned int Shader::GLSLVertexShaderFromFiles(unsigned int numFiles, const char** filePaths)
{
	//*(a+5) = 0;

	char** psrc = new char* [numFiles];

	for (int j = 0; j < numFiles; ++j)
	{









		ifstream file;
		file.open(*(filePaths + j), ios::in);// open in ascii
		if (!file) return -1;

		unsigned long len = getFileLength(file);
		char* ShaderSource;
		ShaderSource = (char*) new char[len + 1];
		if (*ShaderSource == 0) return -3;   // can't reserve memory

		unsigned int i = 0;
		while (file.good())
		{
			ShaderSource[i] = file.get();       // get character from file.
			if (!file.eof())
				i++;
		}

		ShaderSource[i] = 0;  // 0-terminate it at the correct position

		file.close();
		file.clear();
		psrc[j] = ShaderSource;
	}
	const char** shaderSources = (const char**)new  const char(**psrc);
	unsigned int vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObject, numFiles, shaderSources, nullptr);
	glCompileShader(vertexShaderObject);

	int compiled;
	//glgetobjectpar
	glGetObjectParameterivARB(vertexShaderObject, GL_COMPILE_STATUS, &compiled);
	if (compiled)
	{
		// yes it compiled!
	}

	int blen = 0;
	int slen = 0;

	glGetShaderiv(vertexShaderObject, GL_INFO_LOG_LENGTH, &blen);
	if (blen > 1)
	{
		char* compiler_log = (char*)malloc(blen);
		glGetInfoLogARB(vertexShaderObject, blen, &slen, compiler_log);
		std::cout << ("compiler_log:\n", compiler_log);
		free(compiler_log);
	}
	return vertexShaderObject; // No Error
}

unsigned int Shader::GLSLFragmentShaderFromFile(const char* filePath)
{
	ifstream file;
	file.open(filePath, ios::in);// open in ascii
	if (!file) return -1;

	unsigned long len = getFileLength(file);
	char* src;
	src = (char*) new char[len + 1];
	if (*src == 0) return -3;   // can't reserve memory

	unsigned int i = 0;
	while (file.good())
	{
		src[i] = file.get();       // get character from file.
		if (!file.eof())
			i++;
	}

	src[i] = 0;  // 0-terminate it at the correct position

	file.close();

	int flen = len;
	const char* ShaderSource;
	ShaderSource = src;
	unsigned int fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObject, 1, &ShaderSource, &flen);
	glCompileShader(fragmentShaderObject);

	int compiled;
	//glgetobjectpar
	glGetObjectParameterivARB(fragmentShaderObject, GL_COMPILE_STATUS, &compiled);
	if (compiled)
	{
		// yes it compiled!
	}

	int blen = 0;
	int slen = 0;

	glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &blen);
	if (blen > 1)
	{
		char* compiler_log = (char*)malloc(blen);
		glGetInfoLogARB(fragmentShaderObject, blen, &slen, compiler_log);
		std::cout << ("compiler_log:\n", compiler_log);
		free(compiler_log);
	}
	//	unloadshader(&src);
	return fragmentShaderObject; // No Error
}
unsigned int Shader::GLSLFragmentShaderFromFiles(unsigned int numFiles, const char** filePaths)
{
	//	ifstream file;
	//	ifstream file;
	//	file.open(filePaths, ios::in);// open in ascii
	//	if (!file) return -1;
	//
	//	unsigned long len = getFileLength(file);
	//	const char* ShaderSource;
	//	ShaderSource = (char*) new char[len + 1];
	//	if (*ShaderSource == 0) return -3;   // can't reserve memory
	//
	//	unsigned int i = 0;
	//	while (file.good())
	//	{
	//		ShaderSource[i] = file.get();       // get character from file.
	//		if (!file.eof())
	//			i++;
	//	}
	//
	//	ShaderSource[i] = 0;  // 0-terminate it at the correct position
	//
	//	file.close();
	//	GLint flen = len;
	//	unsigned int  fragmentShaderObject = glCreateShader(GL_VERTEX_SHADER);
	//	glShaderSource(fragmentShaderObject, 1, &ShaderSource, &flen);
	//	glCompileShader(fragmentShaderObject);
	//
	//
	//	//error checking
	//	GLint compiled;
	//	//glgetobjectpar
	//	glGetObjectParameterivARB(fragmentShaderObject, GL_COMPILE_STATUS, &compiled);
	//	if (compiled)
	//	{
	//		// yes it compiled!
	//	}
	//
	//	GLint blen = 0;
	//	GLsizei slen = 0;
	//
	//	glGetShaderiv(fragmentShaderObject, GL_INFO_LOG_LENGTH, &blen);
	//	if (blen > 1)
	//	{
	//		char* compiler_log = (char*)malloc(blen);
	//		glGetInfoLogARB(fragmentShaderObject, blen, &slen, compiler_log);
	//		std::cout << "fragment shader failed to compile. \n \n compiler_log: \n", compiler_log;
	//		free(compiler_log);
	//	}
	return 0;// *ShaderSource; // No Error
}
//

// Create shaders by providing raw source strings.

unsigned int GLSLVertexShaderFromSource(const char* source)
{
	//const char *vertSrc =
	//unsigned int len = sizeof source;

	// char* src =(char*) new char[len + 1] ;
	//const char* p = std::strtok(src, "/");
	//while (p != 0)
	//{
	//	std::cout << p << '\n';
	//	p = std::strtok(NULL, " ");
	//}

	//delete[] cstr;
	unsigned int vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObject, 1, &source, nullptr);
	glCompileShader(vertexShaderObject);
	return vertexShaderObject;
	//source = (char*) new char[len + 1];
}
unsigned int GLSLVertexShaderFromSources(unsigned int numSources, const char** sources)
{
	return 0;
}

unsigned int GLSLFragmentShaderFromSource(const char* source)
{
	return 0;
}
unsigned int GLSLFragmentShaderFromSources(unsigned int numSources, const char** sources)
{
	return 0;
}


// Create a basic GLSL program using previously initialized shader handles. 
//	A basic program can have a vertex shader, a fragment shader, or both.  
//	The function also deletes the provided shaders if specified.

unsigned int Shader::GLSLProgram(unsigned int vertexShaderHandle,
	unsigned int fragmentShaderHandle)
{
	unsigned int ProgramObject = glCreateProgram();

	glAttachShader(ProgramObject, vertexShaderHandle);
	glAttachShader(ProgramObject, fragmentShaderHandle);

	glLinkProgram(ProgramObject);


	GLint linked;
	glGetProgramiv(ProgramObject, GL_LINK_STATUS, &linked);
	if (linked)
	{
		printf("program linking sucess!!");
		glUseProgram(ProgramObject);
		return ProgramObject;
	}
	else
	{
		printf("link failed!!");
		glUseProgram(ProgramObject);
		return -1;
	}

}


// Create a program handle and perform the complete set up for the shader 
//	given sources or file paths. Provide a non-null pointer for 'shaderOut' 
//	to obtain the shader handle; if this value is null, the shader will be 
//	discarded after the program is created.

unsigned int GLSLProgramFromFiles(unsigned int numVertexFiles, const char** vertexFilePaths, unsigned int* vertexShaderOut,
	unsigned int numFragmentFiles, const char** fragmentFilePaths, unsigned int* fragmentShaderOut)
{
	return 0;
}


// Create program from source strings.

unsigned int GLSLProgramFromSources(unsigned int numVertexSources, const char** vertexSources, unsigned int* vertexShaderOut,
	unsigned int numFragmentSources, const char** fragmentSources, unsigned int* fragmentShaderOut)
{
	return 0;
}



