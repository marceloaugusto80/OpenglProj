#pragma once

#include <vector>
#include "GameContext.h"
#include "IInputListener.h"
#include "Utils\Utils.h"


struct InputMap
{
	int Up, Right, Down, Left, Action1, Action2;
};




class InputSystem : NonCopyable
{
	GameContext * m_context;
	static std::vector<IInputListener*> m_listeners;
	InputMap m_inputMap;


	static void OnKeyEvent(GameContext* context, int key, int scancode, int action, int modifier);

public:
	InputSystem(GameContext* context);

	void AddListener(IInputListener* listener);

	void RemoveListener(IInputListener* listener);

	void SetInputMap(const InputMap& inputMap)
	{
		m_inputMap = inputMap;
	}

	const InputMap& GetInputMap()
	{
		return m_inputMap;
	}


};

