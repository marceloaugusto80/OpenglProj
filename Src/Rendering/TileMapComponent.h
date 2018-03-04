#pragma once

#include "Base\Entity.h"
#include "TileMap.h"

class TileMapComponent : public Component
{
	TileMap m_tileMap;

public:

	bool Load(const char* tileMapFile);

};