#pragma once

#include "Utils\Utils.h"

class TextureManager;

struct Texture
{
	friend class TextureManager;
	
	Texture() :
		ImageSize({ 0.0f, 0.0f}),
		Index(-1)
	{}

	Vec2 ImageSize;
	int Index;
};
