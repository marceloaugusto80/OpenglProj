#pragma once

#include "Core\Component.h"
#include "Core\TileMap.h"

class TileMapComponent : public Component
{
	TileMap m_tileMap;

public:

	bool Load(const char* tileMapFile);

};