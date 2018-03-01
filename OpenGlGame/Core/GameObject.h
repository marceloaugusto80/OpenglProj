#pragma once

#include "Transform.h"
#include "Component.h"

class Scene;

typedef std::unordered_map<std::type_index, Component*> ComponentMap;



class GameObject : public NonCopyable
{
	Transform* m_transform;
	ComponentMap m_componentMap;

public:

	GameObject();
	
	virtual ~GameObject();
	
	Transform* GetTransform()
	{
		return m_transform;
	}
	
	virtual void OnCreate() {}

	virtual void OnDestroy() {}

	virtual void OnUpdate(float delta) {}


	inline void Attach(GameObject * child)
	{
		GetTransform()->AddChild(child->GetTransform());
	}

	inline void AttachTo(GameObject* parent)
	{
		parent->GetTransform()->AddChild(GetTransform());
	}

	template<class C>
	C* AddComponent()
	{
		C* inst = new C();
		inst->m_owner = this;
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

