#pragma once

#include "Render\RenderSystem.h"
#include "Input\InputSystem.h"
#include "Physics\PhysicsSystem.h"
#include "GameContext.h"
#include "Core\SceneManager.h"
#include "Clock.h"


	
struct Configuration
{
	const char* GameTitle;
};


class Game
{
	GameContext* m_context;
	RenderSystem m_renderer;
	InputSystem m_input;
	SceneManager m_sceneManager;
	PhysicsSystem m_physics;
	
	Clock m_gameClock;


	Game(GameContext* context, const Configuration& config, const RenderConfig& renderConfig) :
		m_context(context),
		m_renderer(context, renderConfig),
		m_input(context),
		m_gameClock(context)
	{}
		
	void Loop();

public:
	static Game* Create(const Configuration& config, const RenderConfig& renderConfig);
	~Game();
	void Start();

	RenderSystem& Render()
	{
		return m_renderer;
	}

	InputSystem& Input()
	{
		return m_input;
	}

	GameContext* GetContext()
	{
		return m_context;
	}

	Clock& GetGameClock()
	{
		return m_gameClock;
	}

	PhysicsSystem& GetPhysics()
	{
		return m_physics;
	}
};

extern Game* TheGame;