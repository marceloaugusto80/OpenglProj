#pragma once

#include <vector>
#include "OglRenderer.h"
#include "TextureManager.h"
#include "GameContext.h"
#include "NonCopyable.h"
class RenderComponent;


struct RenderConfig
{
	int SpriteMaxCount;
	int TextureMaxWidth;
	int TextureMaxHeight;
	int MaxTextureCount;
	int ScreenWidth;
	int ScreenHeigth;
};


class RenderSystem : NonCopyable
{
	OglRenderer* m_oglRender;
	TextureManager m_texManager;
	std::vector<RenderComponent*> m_components;

public:
	
	RenderSystem(GameContext* context, const RenderConfig& config);
	
	~RenderSystem() 
	{
		delete m_oglRender;
	}
	
	Texture LoadTexture(const char* filePath)
	{
		Texture tex;
		m_texManager.Load(&tex, filePath);
		return tex;
	}

	Texture LoadTexture(unsigned char* buffer, int width, int height, const char* key)
	{
		Texture tex;
		m_texManager.Load(&tex, buffer, width, height, key);
		return tex;
	}

	void Render();

	inline void ToggleFullscreen()
	{
		m_oglRender->ToggleFullscreen();
	}

	// 

	void RegisterComponent(RenderComponent* rc);
	
	void UnregisterComponent(RenderComponent* rc);
};





