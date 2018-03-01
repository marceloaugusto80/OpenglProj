#pragma once

#include <vector>
#include "PhysicsComponent.h"

class PhysicsSystem
{
	std::vector<PhysicsComponent*> m_pxList;

public:
	PhysicsSystem()
	{
	}

	~PhysicsSystem()
	{
	}

	void Register(PhysicsComponent* pxComponent);

	void Unregister(PhysicsComponent* pxcomponent);
	
	void Step(float milisecs);

};

