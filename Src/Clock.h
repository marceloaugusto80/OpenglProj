#pragma once

#include <vector>
#include "GameContext.h"


class Clock
{
	GameContext* m_context;

	float
		m_delta,
		m_now,
		m_marker,
		m_minElapsed;

public:

	Clock(GameContext* context, float minimalElapsed = 0.0f) :
		m_context(context),
		m_delta(0),
		m_now(0),
		m_marker(0),
		m_minElapsed(minimalElapsed)
	{
	}

	void Reset()
	{
		m_marker = GetGameTime();
	}

	float GetElapsed()
	{
		return GetGameTime() - m_marker;
	}

	float ResetAndGetElapsed()
	{
		float elapsed = GetElapsed();
		Reset();
		return elapsed;
	}
	
	bool HasMinimalElapsed()
	{
		return (GetElapsed() >= m_minElapsed);
	}

	void SetMinimalElapsed(float minimalElapsed)
	{
		m_minElapsed = minimalElapsed;
	}

	float GetMinimalElapsed()
	{
		return m_minElapsed;
	}

	static float GetGameTime()
	{
		return static_cast<float>(glfwGetTime());
	}

};
