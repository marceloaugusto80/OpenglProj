#include "stdafx.h"
#include "OpenGl.h"


const char* OpenGl::m_lastError = "--";

bool OpenGl::HasError()
{
	return glGetError() != GL_NO_ERROR;
}

const char * OpenGl::GetLastError()
{
	GLenum error = glGetError();
	switch (error)
	{
	case GL_INVALID_ENUM:
		m_lastError = "Invalid enum";
		break;
	case GL_INVALID_VALUE:
		m_lastError = "Invalid value";
		break;
	case GL_INVALID_OPERATION:
		m_lastError = "Invalid operation";
		break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		m_lastError = "Invalid frame buffer operation";
		break;
	case GL_OUT_OF_MEMORY:
		m_lastError = "Out of memory";
		break;
	case GL_STACK_UNDERFLOW:
		m_lastError = "Stack underflow";
		break;
	case GL_STACK_OVERFLOW:
		m_lastError = "Stack overflow";
		break;
	case GL_NO_ERROR:
		m_lastError = "No error";
		break;
	default:
		m_lastError = "Unknown";
		break;
	}

	std::cout << m_lastError << std::endl;
	return m_lastError;
}


