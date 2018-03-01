#pragma once

class IFrameListener
{
public:
	virtual void OnUpdate(float delta) = 0;
};