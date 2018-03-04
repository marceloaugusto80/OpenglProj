#include "stdafx.h"
#include "GameContext.h"
#include "Common.h"

GameContext * GameContextFactory::CreateContext(const char* gameTitle)
{
	if (!glfwInit())
	{
		PRINT("glfw init error.");
		return 0;
	}

	// select opengl version

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// glfw tweaks
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwSwapInterval(0);

	// create window and opengl context

	
	GameContext* context;
	context = glfwCreateWindow(800, 600, gameTitle, 0, 0);

	if (!context)
	{
		PRINT("glfw window creation error.");
		return 0;
	}
	glfwMakeContextCurrent(context);

	// NOTE ogl context must have been created before init glew
	if (glewInit() != GLEW_OK)
	{
		PRINT("glew init error");
		return 0;
	}

	return context;
}

void GameContextFactory::DestroyContext(GameContext * context)
{
	glfwDestroyWindow(context);
	glfwTerminate();
}
