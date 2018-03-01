#include "stdafx.h"
#include "PhysicsComponent.h"
#include "Game.h"

PhysicsComponent::PhysicsComponent() :
	m_speed({ 0.0f, 0.0f })
{
	TheGame->GetPhysics().Register(this);
}

PhysicsComponent::~PhysicsComponent()
{
	TheGame->GetPhysics().Unregister(this);
}

void PhysicsComponent::Step(float delta)
{

	GetOwner()->GetTransform()->Move(m_speed * delta);
	GetOwner()->GetTransform()->AddRotation(m_angularSpeed * delta);

}
