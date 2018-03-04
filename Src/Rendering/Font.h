#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include "Logger.h"
#include "Texture.h"
#include "Types.h"
#include "pugixml\pugixml.hpp"


struct FontChar
{
	Vec2 Offset;
	Vec2 Size;
	Rectf UvRect;
	float Advance;
};

typedef unsigned char byte;
 
typedef std::unordered_map<unsigned char, FontChar> CharCoordMap;

class Font
{
	CharCoordMap m_charCoordMap; 
	Texture m_texture;
	const char* m_fontName;
	
	float m_base,
		  m_lineHeight,
		  m_imageWidth,
		  m_imageHeight;

	void FillMap(const char* fontPath)
	{
		
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(fontPath);

		if (!result)
		{
			PRINTF("xml parsed with errors: %s", result.description());
		}

		auto root = doc.child("font");

		std::string imagePath = "Resources\\Fonts\\";
		imagePath +=  root.child("pages").child("page").attribute("file").as_string();
		m_texture = Texture(); //TheGame->Render().LoadTexture(imagePath.c_str());

		auto common = root.child("common");
		m_base = common.attribute("base").as_float();
		m_lineHeight = common.attribute("lineHeight").as_float();
		m_imageWidth = common.attribute("scaleW").as_float();
		m_imageHeight = common.attribute("scaleH").as_float();


		auto chars = root.child("chars").children("char");
		for (auto it = chars.begin(); it != chars.end(); it++)
		{
			pugi::xml_node& node = *it;
			FontChar fc;
			

			fc.Advance = node.attribute("xadvance").as_float();
			
			fc.Offset = Vec2(
				node.attribute("xoffset").as_float(), 
				node.attribute("yoffset").as_float());
			
			fc.Size = Vec2(
				node.attribute("width").as_float(), 
				node.attribute("height").as_float());
			
			Vec2 startPos = Vec2(
				node.attribute("x").as_float(), 
				node.attribute("y").as_float());
			fc.UvRect = { 
				{ startPos.x, startPos.y  }, 
				{ startPos.x + fc.Size.x, startPos.y + fc.Size.y } };
			
			
			unsigned char c = static_cast<unsigned char>(node.attribute("id").as_int());
			m_charCoordMap[c] = fc;

		}
		

	}

public:
	Font(){}

	~Font()
	{
	}

	bool Load(const char* fontPath)
	{
		FillMap(fontPath);
		return true;
	}

	FontChar* GetChar(char character)
	{
		auto it = m_charCoordMap.find(character);
		if (it != m_charCoordMap.end())
		{
			return &(it->second);
		}
		return 0;
	}

	Texture GetTexture()
	{
		return m_texture;
	}

	float GetBase()
	{
		return m_base;
	}

	float GetLineHeight()
	{
		return m_lineHeight;
	}

};


