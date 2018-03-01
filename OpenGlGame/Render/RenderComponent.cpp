#include "stdafx.h"
#include "RenderComponent.h"
#include "Game.h"

RenderComponent::RenderComponent() :
	m_size(Vec2(10.0f, 10.0f)),
	m_color(Vec4(1.0f, 1.0f, 1.0f, 1.0f)),
	m_textureUV(Rectf(0.0f, 0.0f, 256.0f, 256.0f)),
	m_offset(Vec2(0.0f, 0.0f))
{
	TheGame->Render().RegisterComponent(this);
}

RenderComponent::~RenderComponent()
{
	TheGame->Render().UnregisterComponent(this);
}