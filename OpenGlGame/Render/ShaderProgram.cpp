#include "stdafx.h"
#include <vector>
#include "Shader.h"
#include "ShaderProgram.h"


std::string ShaderProgram::ErrorMessage = "None";



GLuint ShaderProgram::Compile(const char * vertexShaderFilePath, const char * fragmentShaderFilePath)
{
	GLuint progId = glCreateProgram();

	// vert shader - compile and attach

	GLuint vertId = Shader::Load("vertex", Shader::ShaderTypes::VERTEX);
	if (vertId == 0)
	{
		glDeleteProgram(progId);
		ErrorMessage = Shader::GetLastError().c_str();
		return 0;
	}
	glAttachShader(progId, vertId);

	// fragment - compile and attach

	GLuint fragId = Shader::Load("fragment", Shader::ShaderTypes::FRAGMENT);
	if (fragId == 0)
	{
		glDeleteProgram(progId);
		ErrorMessage = Shader::GetLastError().c_str();
		return false;
	}
	glAttachShader(progId, fragId);

	// Link

	if (!Link(progId))
		return 0;

	// release resources

	glDetachShader(progId, vertId);
	glDetachShader(progId, fragId);
	glDeleteShader(vertId);
	glDeleteShader(fragId);
		
	return progId;
}

bool ShaderProgram::Link(GLuint programId)
{
	glLinkProgram(programId);
	GLint isLinkOk = GL_FALSE;
	glGetProgramiv(programId, GL_LINK_STATUS, &isLinkOk);
	
	if (!isLinkOk) {
		GLint messageLenght;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &messageLenght);
		std::vector<char> errorMsg(messageLenght + 1);
		glGetProgramInfoLog(programId, messageLenght, NULL, &errorMsg[0]);
		
		ErrorMessage = std::string(errorMsg.begin(), errorMsg.end());
		
		return false;
	}
	
	return true;
}
