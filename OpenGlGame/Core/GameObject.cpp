#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"


GameObject::GameObject()
{
	m_transform = AddComponent<Transform>();
}


GameObject::~GameObject()
{
	for (auto item : m_componentMap)
	{
		delete item.second;
	}
}
