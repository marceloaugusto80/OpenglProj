#include "stdafx.h"
#include "InputComponent.h"
#include "Game.h"

InputComponent::InputComponent()
{
	TheGame->Input().AddListener(this);
}

InputComponent::~InputComponent()
{
	TheGame->Input().RemoveListener(this);
}


