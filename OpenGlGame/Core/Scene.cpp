#include "stdafx.h"
#include "Scene.h"

Scene::~Scene()
{
	for (auto obj : m_objList)
	{
		delete obj;
	}
}

void Scene::OnCreate()
{
	GameObject::OnCreate();
}

void Scene::OnUpdate(float delta)
{
	for (auto& go : m_objList)
	{
		go->OnUpdate(delta);
	}
}
