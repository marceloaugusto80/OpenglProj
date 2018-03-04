#pragma once

#include "GL\glew.h" // glew must be initialized before glfw
#include "GLFW\glfw3.h"


typedef GLFWwindow GameContext;

class GameContextFactory
{
public:
	static GameContext* CreateContext(const char* gameTitle);
	static void DestroyContext(GameContext* context);
};
