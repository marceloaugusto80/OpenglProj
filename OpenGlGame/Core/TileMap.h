#pragma once
#include <vector>
#include <string>
#include "Core\Core.h"


struct TMLayer
{
	TMLayer() :
		DataArray(0)
	{}
	~TMLayer()
	{
		delete[] DataArray;
	}

	std::string 
		Encoding,
		Name,
		Type;
	
	int
		Width,
		Height,
		X,
		Y;

	unsigned int* DataArray;

	bool IsVisible;
	
	float Opacity;
	
};

struct TMTileSet
{
	int 
		Columns,
		FirstGID,
		ImageWidth,
		ImageHeight,
		Margin,
		Spacing,
		TileCount,
		TileWidth,
		TileHeight;
	
	std::string
		Image,
		Name;
};

struct TileMap
{

	int
		Height,
		NextObjectId,
		TileHeight,
		TileWidth,
		Width;

	bool IsInfinite;
	std::string
		Orientation,
		RenderOrder,
		Type;
	
	std::vector<TMTileSet> TileSets;
	std::vector<TMLayer> Layers;

	bool Load(const char* path);

};


