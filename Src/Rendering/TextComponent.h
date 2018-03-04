#pragma once

#include <string>
#include "Core.h"
#include "Font.h"
#include "Utils\Utils.h"

class TextComponent : public Component
{
public:
	TextComponent()
	{
	}

	~TextComponent()
	{
	}

	void SetText(Font* font, std::string text, float scaleSize = 1.0f)
	{
		float cursorX = 0;
		float cursorY = 0;

		auto& pos = GetOwner()->GetTransform()->GetPosition();

		for (auto const &c : text)
		{
			if (c == '\n')
			{
				cursorY += font->GetLineHeight();
				cursorX = 0;
				continue;
			}

			FontChar* fc = font->GetChar(c);
			if (fc != 0)
			{
				auto r = GetOwner()->AddComponent<RenderComponent>();
				
				r->SetSize(fc->Size * scaleSize);
				r->SetOffset(Vec2(cursorX, cursorY));
				cursorX += fc->Advance;
				
				r->SetTexture(font->GetTexture());
				r->SetTextureUV(fc->UvRect);
				m_renderChars.push_back(r);
			}
		}
	}


private:
	std::string m_text;
	Font* m_font;
	std::vector<RenderComponent*> m_renderChars;
};

