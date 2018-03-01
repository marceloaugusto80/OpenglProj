#include "stdafx.h"
#include "DummyInputComponent.h"
#include "Game.h"
#include "Physics\Physics.h"
#include "Utils\Utils.h"

DummyInputComponent::DummyInputComponent() :
	m_step(10.0f)
{
}



DummyInputComponent::~DummyInputComponent()
{
	//InputSystem::Inst()->RemoveListener(this);
}



void DummyInputComponent::OnKeyDown(int key)
{
	const InputMap& map = TheGame->Input().GetInputMap();
	PhysicsComponent* px = GetOwner()->GetComponent<PhysicsComponent>();
	
	if (!px) return;
	
	const Vec2& curSpeed = px->GetSpeed();
	PRINTF("Current Speed: %2.2f", curSpeed);

	if (key == map.Up)
	{
		if (curSpeed.y <= 0.0f)
		{
			px->SetSpeedY(m_step);
		}

	}
	else if (key == map.Down)
	{
		if (curSpeed.y >= 0.0f)
		{
			px->SetSpeedY(-m_step);

		}

	}
	else if (key == map.Left)
	{
		if (curSpeed.x >= 0.0f)
		{
			px->SetSpeedX(-m_step);
		}

	}
	else if (key == map.Right)
	{
		if (curSpeed.x <= 0.0f)
		{
			px->SetSpeedX(m_step);
			
		}

	}
	else if (key == map.Action1)
	{
		//px->SetAngularSpeed(-m_step / 20.0f);

	}
	else if (key == map.Action2)
	{
		//px->SetAngularSpeed(m_step / 20.0f);
	}
}



void DummyInputComponent::OnKeyUp(int key)
{
	const InputMap& map = TheGame->Input().GetInputMap();
	PhysicsComponent* px = GetOwner()->GetComponent<PhysicsComponent>();
	if (!px) return;
	
	const Vec2& curSpeed = px->GetSpeed();
	PRINTF("Current Speed: %2.2f", curSpeed);
	

	if (key == map.Up)
	{
		if (curSpeed.y > 0.0f)
			px->SetSpeedY(0);

	}
	else if (key == map.Down)
	{
		if (curSpeed.y < 0.0f)
			px->SetSpeedY(0);

	}
	else if (key == map.Left)
	{
		if (curSpeed.x < 0.0f)
			px->SetSpeedX(0);

	}
	else if (key == map.Right)
	{
		if(curSpeed.x > 0.0f)
			px->SetSpeedX(0);

	}
	else if (key == map.Action1)
	{
		m_step += 0.25f;
		PRINTF("speed: %2.2f", m_step);
		//px->SetAngularSpeed(0);

	}
	else if (key == map.Action2)
	{
		m_step -= 0.25f;
		PRINTF("speed: %2.2f", m_step);
		//px->SetAngularSpeed(0);
	}

}

