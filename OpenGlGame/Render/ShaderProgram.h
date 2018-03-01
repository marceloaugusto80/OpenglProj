#pragma once

#include <string.h>
#include "GL\glew.h"

class ShaderProgram
{
	static std::string ErrorMessage;
	
	static bool Link(GLuint programId);

public:

	static GLuint Compile(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);

	static const std::string& GetLastError()
	{
		return ErrorMessage;
	}

};
