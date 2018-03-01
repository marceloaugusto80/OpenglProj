#include "stdafx.h"
#include <algorithm>
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"



void PhysicsSystem::Register(PhysicsComponent * pxComponent)
{
	m_pxList.push_back(pxComponent);
}

void PhysicsSystem::Unregister(PhysicsComponent * pxcomponent)
{
	m_pxList.erase(std::remove(m_pxList.begin(), m_pxList.end(), pxcomponent), m_pxList.end());
}

void PhysicsSystem::Step(float milisecs)
{
	for (auto& ph : m_pxList)
	{
		ph->Step(milisecs);
	}
}
