#pragma once

#include "FrameListenerComponent.h"

class RotateComponent : public FrameListenerComponent
{
	float m_frequency;
	float m_amplitude;
	float m_t;
	float m_pos;

public:

	RotateComponent() :
		m_t(0),
		m_frequency(1),
		m_amplitude(10),
		m_pos(5.0f)
	{}

	void SetFrequency(float f)
	{
		m_frequency = f;
	}

	void SetAmplitude(float a)
	{
		m_amplitude = a;
	}

	void SetPos(float pos)
	{
		m_pos = pos;
	}

	// Inherited via FrameListenerComponent
	virtual void OnUpdate(float delta) override
	{
		auto t = GetOwner()->GetTransform();

		// wobble
		/*m_t += delta;
		float offset = m_amplitude * sin(2 * PI * m_frequency * m_t);
		t->SetPosition({ offset + m_pos, t->GetPosition().y });*/

		t->AddRotation(delta * m_frequency * 360.0f);
	}
};