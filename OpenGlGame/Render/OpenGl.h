#pragma once

#include "GL\glew.h"
#include "GLFW\glfw3.h"

typedef GLFWwindow SystemContext;

class OpenGl
{
	static const char* m_lastError;

public:
	static bool HasError();
	static const char* GetLastError();
	
};
