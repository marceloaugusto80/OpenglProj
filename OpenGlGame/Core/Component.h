#pragma once

#include "Utils\Utils.h"
class GameObject;



class Component : public NonCopyable
{
	friend class GameObject;

public:

	Component()
	{}

	virtual ~Component()
	{}

	GameObject* GetOwner()
	{
		return m_owner;
	}

	virtual void OnAttach() 
	{}

	virtual void OnDettach()
	{}

private:
	GameObject * m_owner;

};
