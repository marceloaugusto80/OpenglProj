#pragma once

class Scene
{
public:
	Scene()
	{}

	virtual ~Scene()
	{}

	//template<class G>
	//G* Spawn(const Vec3& location = Vec3(0.0f, 0.0f, 0.0f))
	//{
	//	// TODO verify object list capacity before spawn
	//	G* go = new G();
	//	m_objList.push_back(go);

	//	GetTransform()->AddChild(go->GetTransform());
	//	go->GetTransform()->SetPosition(location);
	//	go->OnCreate();
	//	
	//	return go;
	//}

};
