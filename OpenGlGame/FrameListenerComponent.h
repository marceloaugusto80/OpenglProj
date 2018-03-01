#pragma once

#include "Core\Core.h"
#include "IFrameListener.h"

class FrameListenerComponent : public Component, public IFrameListener
{

public:
	FrameListenerComponent();
	~FrameListenerComponent();
	virtual void OnUpdate(float delta) = 0;
};