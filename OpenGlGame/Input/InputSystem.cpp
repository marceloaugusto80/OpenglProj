#include "stdafx.h"
#include "InputSystem.h"
#include "Game.h"


std::vector<IInputListener*> InputSystem::m_listeners;


void InputSystem::AddListener(IInputListener * listener)
{
	m_listeners.push_back(listener);
}

void InputSystem::RemoveListener(IInputListener * listener)
{
	m_listeners.erase(std::remove(m_listeners.begin(), m_listeners.end(), listener), m_listeners.end());
}

void InputSystem::OnKeyEvent(GameContext * context, int key, int scancode, int action, int modifier)
{
	for (auto listener : m_listeners)
	{
		switch (action)
		{
		case GLFW_PRESS:
			if (key == GLFW_KEY_ENTER && modifier == GLFW_MOD_ALT)
			{
				TheGame->Render().ToggleFullscreen();
			}

			listener->OnKeyDown(key);
			break;
		case GLFW_RELEASE:
			listener->OnKeyUp(key);
			break;
		}
	}
}


InputSystem::InputSystem(GameContext * context) :
	m_context(context)
{
	glfwSetKeyCallback(context, OnKeyEvent);
	m_inputMap = 
	{
		GLFW_KEY_UP,
		GLFW_KEY_RIGHT,
		GLFW_KEY_DOWN,
		GLFW_KEY_LEFT,
		GLFW_KEY_SPACE,
		GLFW_KEY_E
	};
}
