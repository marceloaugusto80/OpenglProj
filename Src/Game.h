#pragma once

#include "Rendering\RenderSystem.h"
#include "GameContext.h"
#include "Clock.h"


	
struct Configuration
{
	const char* GameTitle;
};


class Game
{
	GameContext* m_context;
	RenderSystem m_renderer;
	
	Clock m_gameClock;


	Game(GameContext* context, const Configuration& config, const RenderConfig& renderConfig) :
		m_context(context),
		m_renderer(context, renderConfig),
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

	GameContext* GetContext()
	{
		return m_context;
	}

	Clock& GetGameClock()
	{
		return m_gameClock;
	}

	
};

extern Game* TheGame;