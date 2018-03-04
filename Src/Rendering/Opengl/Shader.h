#pragma once

#include <GL\glew.h>
#include <string>

#define SHADER_FOLDER_PATH "Resources\\Shaders\\"
#define SHADER_FILE_EXTENSION ".glsl"


class Shader
{
	static std::string LastError;
	
	static bool IsCompileSuccess(GLuint shaderId);
	static bool ReadShaderFile(const char* fileName, std::string* output);
	static void SetErrorMessage(const char* message);

public:

	enum ShaderTypes
	{
		UNDEFINED = -1,
		VERTEX = GL_VERTEX_SHADER,
		FRAGMENT = GL_FRAGMENT_SHADER
	};


	static GLuint Load(const char* fileName, ShaderTypes shaderType);
	
	static const std::string GetLastError()
	{
		return LastError;
	}
	
	
};


