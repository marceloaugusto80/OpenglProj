#pragma once

#include "Core\Core.h"
#include "Utils\Utils.h"

class PhysicsComponent : public Component
{

	Vec2 m_speed;
	float m_angularSpeed;

public:
	PhysicsComponent();
	~PhysicsComponent();

	const Vec2& GetSpeed()
	{
		return m_speed;
	}
	void SetSpeed(const Vec2& speed)
	{
		m_speed = speed;
	}

	void SetSpeedY(float speedY)
	{
		m_speed.y = speedY;
	}
	void SetSpeedX(float speedX)
	{
		m_speed.x = speedX;

	}
	void AddSpeed(const Vec2& speed)
	{
		m_speed += speed;
	}
	void AddSpeed(const Vec2& speed, const Vec2& threshold)
	{
		m_speed += speed;
		if (m_speed.x > threshold.x) m_speed.x = threshold.x;
		if (m_speed.y > threshold.y) m_speed.y = threshold.y;

	}

	void SetAngularSpeed(float speed)
	{
		m_angularSpeed = speed;
	}
	float GetAngularSpeed()
	{
		return m_angularSpeed;
	}

	virtual void Step(float delta);

};

