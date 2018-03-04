#include "stdafx.h"
#include "Game.h"
#include "Common.h"


Game* TheGame = 0;

void Game::Loop()
{
	Clock renderClock = Clock(m_context, 1.0f / 60.0f);
	m_gameClock.SetMinimalElapsed(1.0f / 60.0f);
	
	float delta = 0.0f;
	float time = 0;
	float rt = 0;
	float rtLim = 1.0f / 60.0f;
	float pt = 0.0f;
	float ptLim = 1.0f / 30.0f;
	while (!glfwWindowShouldClose(m_context))
	{
		float t = Clock::GetGameTime();
		delta = t - time;
		time = t;

		glfwPollEvents();
		
		if (rt >= rtLim)
		{
			m_renderer.Render();
			//PRINTF("delta: %2.4f", rt);
			rt = 0.0f;

		}
		
		else
		{
			rt += delta;
		}
	}
}

Game* Game::Create(const Configuration& config, const RenderConfig& renderConfig)
{
	GameContext* context = GameContextFactory::CreateContext(config.GameTitle);

	if (!context)
	{
		PRINT("Error creating GameContext");
		return 0;
	}
	
	Game* g = new Game(context, config, renderConfig);

	
	
	TheGame = g;
	return g;
}

Game::~Game()
{
	GameContextFactory::DestroyContext(m_context);
}

void Game::Start()
{
	Loop();
	
}

