#pragma once

#include "Common.h"


class Transform
{
	Vec2 m_position, m_scale;
	float m_rotation, m_zIndex;
	Mat4f m_transformMatrix;
	bool m_isDirty;
	std::vector<Transform*> m_children;
	Transform* m_parent;

	void SetDirty();

	void UpdateWorldMatrix();

public:
	Transform() :
		m_position({ 0.0f, 0.0f }),
		m_scale({ 1.0f, 1.0f }),
		m_rotation(0.0f),
		m_zIndex(0.0f),
		m_isDirty(false),
		m_parent(0),
		m_transformMatrix(Mat3f(1.0f))
	{
		SetDirty();
	}

	const Vec2& GetPosition()
	{
		return m_position;
	}
	void SetPosition(const Vec2& position)
	{
		m_position = position;
		SetDirty();
	}

	const Vec2& GetScale()
	{
		return m_scale;
	}
	void SetScale(const Vec2& scale)
	{
		m_scale = scale;
		SetDirty();
	}

	float GetRotation()
	{
		return m_rotation;
	}
	void SetRotation(float rotation)
	{
		m_rotation = rotation;
		SetDirty();
	}
	void AddRotation(float rotation)
	{
		m_rotation += rotation;
		SetDirty();
	}

	float GetZIndex()
	{
		return m_zIndex;
	}
	void SetZIndex(float zIndex)
	{
		m_zIndex = zIndex;
	}

	void Move(const Vec2& offset)
	{
		m_position += offset;
		SetDirty();
	}
	void MoveX(float x)
	{
		m_position.x += x;
		SetDirty();
	}
	void MoveY(float y)
	{
		m_position.y += y;
		SetDirty();
	}


	const Mat4f& GetMatrix();

	void AddChild(Transform* child);

	void RemoveChild(Transform* child);


};
