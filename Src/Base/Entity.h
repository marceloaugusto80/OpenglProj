#pragma once

#include <typeindex>
#include <unordered_map>
#include "Common.h"
#include "Transform.h"

class Component;
class Entity;

typedef std::unordered_map<std::type_index, Component*> ComponentMap;


class Component : public NonCopyable
{
public:

	Component()
	{}

	virtual ~Component()
	{}

	Entity* GetOwner()
	{
		return m_owner;
	}

	void SetOwner(Entity* entity)
	{
		m_owner = entity;
	}

	virtual void OnAttach()
	{}

	virtual void OnDettach()
	{}

private:
	Entity * m_owner;

};



class Entity : public NonCopyable
{
	Transform* m_transform;
	ComponentMap m_componentMap;

public:

	Entity()
	{}
	
	virtual ~Entity()
	{
		for (auto item : m_componentMap)
		{
			delete item.second;
		}
	}
	
	Transform* GetTransform()
	{
		return m_transform;
	}
	
	virtual void OnUpdate(float delta) {}


	inline void Attach(Entity * child)
	{
		GetTransform()->AddChild(child->GetTransform());
	}

	inline void AttachTo(Entity* parent)
	{
		parent->GetTransform()->AddChild(GetTransform());
	}

	template<class C>
	C* AddComponent()
	{
		C* inst = new C();
		inst->SetOwner(this);
		return inst;
	}

	template<class C>
	void RemoveComponent()
	{
		auto it = m_componentMap.find(typeid(C));
		if (it == m_componentMap.end()) return;
		delete it->second;
		m_componentMap.erase(it->first);
	}

	template<class C>
	C* GetComponent()
	{
		auto it = m_componentMap.find(typeid(C));
		if (it == m_componentMap.end()) return 0;
		return static_cast<C*>(it->second);
	}

};



