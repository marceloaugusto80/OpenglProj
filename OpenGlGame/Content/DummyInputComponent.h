#pragma once

#include "Core\Core.h"
#include "Input\Input.h"

class DummyInputComponent : public InputComponent
{
	float m_step;

public:

	DummyInputComponent();
	~DummyInputComponent();
	// Inherited via InputComponent
	virtual void OnKeyDown(int key) override;

	virtual void OnKeyUp(int key) override;

	void SetStep(float step)
	{
		m_step = step;
	}

};

