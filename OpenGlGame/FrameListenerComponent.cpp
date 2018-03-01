#include "stdafx.h"
#include "FrameListenerComponent.h"
#include "Game.h"

FrameListenerComponent::FrameListenerComponent()
{
	TheGame->GetGameClock().RegisterListener(this);
}

FrameListenerComponent::~FrameListenerComponent()
{
	TheGame->GetGameClock().UnregisterListener(this);
}
