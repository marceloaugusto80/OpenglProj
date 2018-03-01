#pragma once

#include <vector>
#include "Scene.h"
#include "Content\TestScene.h"


typedef Scene*(*SceneFactoryFunc)(void);

class SceneManager
{
public:
	SceneManager() :
		m_sceneIndex(-1)
	{
		
	}

	~SceneManager()
	{
	}

	template<class S>
	void RegisterScene()
	{
		SceneFactoryFunc fun = CreateScene<S>;
		m_sceneList.push_back(fun);

	}

	Scene* Next()
	{
		delete m_currentScene;

		if (m_sceneIndex < m_sceneList.size() - 1)
		{
			m_sceneIndex++;
		}
		else
		{
			m_sceneIndex = 0;
		}

		m_currentScene = m_sceneList[m_sceneIndex]();
		m_currentScene->OnCreate();
		return m_currentScene;
	}

	Scene* GetCurrent()
	{
		m_currentScene;
	}

private:
	std::vector<SceneFactoryFunc> m_sceneList;
	Scene* m_currentScene;
	int m_sceneIndex;
};
