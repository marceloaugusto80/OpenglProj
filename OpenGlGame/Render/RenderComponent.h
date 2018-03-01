#pragma once

#include <algorithm>
#include <vector>
#include "Core\Core.h"
#include "Texture.h"
#include "Utils\Utils.h"

class RenderComponent : public Component
{
	Vec2 m_size;
	Vec2 m_offset;
	Vec4 m_color;
	Rectf m_textureUV;
	Texture m_texture;

public:
	
	RenderComponent();
	
	virtual ~RenderComponent();

	//

	virtual const Vec2& GetSize()
	{
		return m_size;
	}
	void SetSize(const Vec2& size)
	{
		m_size = size;
	}
	


	const Vec4& GetColor()
	{
		return m_color;
	}
	void SetColor(const Vec4& color)
	{
		m_color = color;
	}



	const Texture& GetTexture()
	{
		return m_texture;
	}
	void SetTexture(const Texture& texture)
	{
		// TODO change uv coords on texture change. if new tex has different size, old uvs can be wrong.
		m_texture = texture;

	}

	const Rectf& GetTextureUv() 
	{
		return m_textureUV;
	}
	void SetTextureUV(const Rectf& uv)
	{
		m_textureUV = uv;
	}

	

	float GetOpacity()
	{
		return m_color.a;
	}
	void SetOpacity(float opacity)
	{
		m_color.a = opacity;
	}



	const Vec2& GetOffset()
	{
		return m_offset;
	}
	void SetOffset(const Vec2& offset)
	{
		m_offset = offset;
	}
};


