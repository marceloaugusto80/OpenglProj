#pragma once


class IInputListener
{
public:
	virtual void OnKeyDown(int key) = 0;

	virtual void OnKeyUp(int key) = 0;
};
