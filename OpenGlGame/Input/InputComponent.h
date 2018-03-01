#pragma once

#include "Core\Core.h"
#include "IInputListener.h"

class InputComponent : public Component, public IInputListener
{

public:
	InputComponent();

	virtual ~InputComponent();

	virtual void OnKeyDown(int key) = 0;

	virtual void OnKeyUp(int key) = 0;

};