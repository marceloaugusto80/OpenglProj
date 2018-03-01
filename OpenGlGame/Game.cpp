#include "stdafx.h"
#include "Game.h"
#include "Utils\Utils.h"
#include "Content\TestScene.h" // TODO erase test scene here. only for dirty testing


Game* TheGame = 0;

void Game::Loop()
{
	Clock renderClock = Clock(m_context, 1.0f / 60.0f);
	Clock pxClock = Clock(m_context, 1.0f / 30.0f);
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
		m_gameClock.UpdateListeners(delta);
		
		if (pt >= ptLim)
		{
			m_physics.Step(delta);
			//PRINTF("delta: %2.4f", pt);
			pt = 0.0f;
		}
		else
		{
			pt += delta;
		}
		
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
	m_sceneManager.RegisterScene<TestScene>();
	m_sceneManager.Next();
	Loop();
	
}

