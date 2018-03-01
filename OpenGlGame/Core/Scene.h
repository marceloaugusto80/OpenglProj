#pragma once

#include <vector>
#include "Core\Core.h"
#include "Utils\Utils.h"



class Scene : public GameObject
{
public:
	Scene()
	{}

	virtual ~Scene();

	template<class G>
	G* Spawn(const Vec3& location = Vec3(0.0f, 0.0f, 0.0f))
	{
		// TODO verify object list capacity before spawn
		G* go = new G();
		m_objList.push_back(go);

		GetTransform()->AddChild(go->GetTransform());
		go->GetTransform()->SetPosition(location);
		go->OnCreate();
		
		return go;
	}

	void Destroy(GameObject* gameObject)
	{
		gameObject->OnDestroy();
		VECTOR_REMOVE(m_objList, gameObject);
		delete gameObject;
	}

	virtual void OnCreate() override;

	void OnUpdate(float delta) override;

private:
	std::vector<GameObject*> m_objList;

};

template<class S>
Scene* CreateScene()
{
	return new S();
}