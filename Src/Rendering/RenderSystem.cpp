#include "stdafx.h"
#include "RenderSystem.h"
#include "RenderComponent.h"
#include "Common.h"
#include "Base\Entity.h"


inline Rectf NormalizeTexUv(const Texture& tex, const Rectf& rect)
{
	return Rectf(
		Normalize(rect.Left, tex.ImageSize.x),
		Normalize(rect.Top, tex.ImageSize.y),
		Normalize(rect.Right, tex.ImageSize.x),
		Normalize(rect.Bottom, tex.ImageSize.y));
}





RenderSystem::RenderSystem(GameContext * context, const RenderConfig & config) :
	m_oglRender(0)
{
	if (!m_texManager.Init(config.TextureMaxWidth, config.TextureMaxHeight, config.SpriteMaxCount))
	{
		throw std::exception("Could not initialize texture manager");
	}

	m_oglRender = OglRenderer::Create(
		context,
		config.SpriteMaxCount,
		m_texManager.GetTextureArrayId(),
		config.ScreenWidth,
		config.ScreenHeigth
	);

	if (!m_oglRender)
	{
		throw std::exception("Could not initialize Ogl Renderer");
	}
}

void RenderSystem::Render()
{
	auto qBuffer = m_oglRender->GetQuadBuffer();

	for (size_t i = 0; i < m_components.size(); i++)
	{
		RenderComponent* comp = m_components[i];
		Quad* q = &qBuffer[i];



		const Mat4f& transform = comp->GetOwner()->GetTransform()->GetMatrix();
		const Vec2& pos = comp->GetOwner()->GetTransform()->GetPosition();
		const Vec2& size = comp->GetSize() + pos;
		const Vec2& off = comp->GetOffset();
		
		Vec4 vecA = transform * Vec4(0.0f,   0.0f,  0.0f, 1.0f);
		Vec4 vecB = transform * Vec4(size.x, 0.0f,  0.0f, 1.0f);
		Vec4 vecC = transform * Vec4(size.x, size.y, 0.0f, 1.0f);
		Vec4 vecD = transform * Vec4(0.0f,   size.y, 0.0f, 1.0f);

		

		const Rectf& uvRect = NormalizeTexUv(comp->GetTexture(), comp->GetTextureUv());

		Vec2 uvA = { uvRect.Left, uvRect.Top };
		Vec2 uvB = { uvRect.Right, uvRect.Top };
		Vec2 uvC = { uvRect.Right, uvRect.Bottom };
		Vec2 uvD = { uvRect.Left, uvRect.Bottom };



		const Vec4& color = comp->GetColor();
		float texIndex = static_cast<float>(comp->GetTexture().Index);
		


		q->V1.Coord = vecA; q->V1.UV = uvA; q->V1.Color = color; q->V1.TexIndex = texIndex;
		q->V2.Coord = vecB; q->V2.UV = uvB; q->V2.Color = color; q->V2.TexIndex = texIndex;
		q->V3.Coord = vecC; q->V3.UV = uvC; q->V3.Color = color; q->V3.TexIndex = texIndex;
		q->V5.Coord = vecD; q->V5.UV = uvD; q->V5.Color = color; q->V5.TexIndex = texIndex;
		
		q->V4 = q->V3;
		q->V6 = q->V1;
	}

	m_oglRender->DrawBuffers(m_components.size());

}

void RenderSystem::RegisterComponent(RenderComponent * rc)
{
	m_components.push_back(rc);
}

void RenderSystem::UnregisterComponent(RenderComponent * rc)
{
	m_components.erase(std::remove(m_components.begin(), m_components.end(), rc), m_components.end());
}


