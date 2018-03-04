#include "stdafx.h"
#include <vector>
#include <fstream>
#include <iostream>
#include "Shader.h"


std::string Shader::LastError = "None";


GLuint Shader::Load(const char * fileName, ShaderTypes shaderType)
{

	char filepath[256];
	sprintf_s(filepath, "%s%s%s", SHADER_FOLDER_PATH, fileName, SHADER_FILE_EXTENSION);
	
	// create

	GLuint id;
	id = glCreateShader((GLuint)shaderType);
	if (id == 0)
	{
		SetErrorMessage("Failed to create shader");
		return 0;
	}

	// read file

	std::string code;
	if (!ReadShaderFile(filepath, &code))
	{
		glDeleteShader(id);
		SetErrorMessage("Failed to read shader file.");
		return 0;
	}

	// Compile Shader

	char const * cstrCode = code.c_str();
	glShaderSource(id, 1, &cstrCode, NULL);
	glCompileShader(id);

	// Check compilation

	if (!IsCompileSuccess(id))
	{
		glDeleteShader(id);
		return 0;
	}

	return id;

}

bool Shader::IsCompileSuccess(GLuint shaderId)
{
	GLint compilationSuccess = GL_FALSE;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationSuccess);
	if (compilationSuccess == GL_FALSE) {
		int statusMsgLenght;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &statusMsgLenght);
		std::vector<char> errorMessageVec(statusMsgLenght + 1);
		glGetShaderInfoLog(shaderId, statusMsgLenght, NULL, &errorMessageVec[0]);
		LastError = std::string(errorMessageVec.begin(), errorMessageVec.end());
	}

	return compilationSuccess != 0;

}

bool Shader::ReadShaderFile(const char * fileName, std::string * output)
{
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(fileName, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
		{
			*output += "\n" + Line;
		}
		VertexShaderStream.close();
		return true;
	}
	else {
		
		return false;
	}
}

void Shader::SetErrorMessage(const char * message)
{
	std::cout << "Error: " << message << std::endl;
	LastError = std::string(message);
}