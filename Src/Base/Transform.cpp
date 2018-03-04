#include "stdafx.h"
#include "Transform.h"



const Mat4f & Transform::GetMatrix()
{
	if (m_isDirty)
	{
		UpdateWorldMatrix();
		m_isDirty = false;
	}
	return m_transformMatrix;
}

void Transform::AddChild(Transform * child)
{
	child->m_parent = this;
	m_children.push_back(child);
	child->SetDirty();

}

void Transform::RemoveChild(Transform * child)
{
	m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
	child->m_parent = 0;
	child->SetDirty();
}

void Transform::SetDirty()
{
	if (!m_isDirty)
	{
		m_isDirty = true;
		for (auto it = m_children.begin(); it != m_children.end(); it++)
		{
			(*it)->m_isDirty = true;
		}
	}
}

void Transform::UpdateWorldMatrix()
{
	auto s = glm::scale(Mat4f(1.0f), Vec3(m_scale.x, m_scale.y, 1.0f));
	
	auto t = glm::translate(Mat4f(1.0f), Vec3(m_position.x, m_position.y, m_zIndex));
	
	auto r = glm::rotate(Mat4f(1.0f), glm::radians(m_rotation), Vec3(0.0f, 0.0f, 1.0f));
	

	Mat4f parentMat = (m_parent == 0) ? Mat4f(1.0f) : m_parent->GetMatrix();
	m_transformMatrix = parentMat * t * r * s;

}
