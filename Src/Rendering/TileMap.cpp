#include "stdafx.h"
#include <fstream>
#include "TileMap.h"
#include "json\json.hpp"
#include "Utility\Base64.h"

using json = nlohmann::json;



void FillTileSet(const json& j, TMTileSet& tileSet)
{
	
	tileSet.Columns =     j["columns"].get<int>();
	tileSet.FirstGID =    j["firstgid"].get<int>();
	tileSet.Image =       j["image"].get<std::string>();
	tileSet.ImageHeight = j["imageheight"].get<int>();
	tileSet.ImageWidth =  j["imagewidth"].get<int>();
	tileSet.Margin =      j["margin"].get<int>();
	tileSet.Name =        j["name"].get<std::string>();
	tileSet.Spacing =     j["spacing"].get<int>();
	tileSet.TileCount =   j["tilecount"].get<int>();
	tileSet.TileHeight =  j["tileheight"].get<int>();
	tileSet.TileWidth =   j["tilewidth"].get<int>();
}


void FillTileMap(const json& j, TileMap& tileMap)
{
	tileMap.Height =		j["height"].get<int>();
	tileMap.IsInfinite =	j["infinite"].get<bool>();
	tileMap.NextObjectId =	j["nextobjectid"].get<int>();
	tileMap.Orientation =	j["orientation"].get<std::string>();
	tileMap.RenderOrder =	j["renderorder"].get<std::string>();
	tileMap.TileHeight =	j["tileheight"].get<int>();
	tileMap.TileWidth =		j["tilewidth"].get<int>();
	tileMap.Type =			j["type"].get<std::string>();
	tileMap.Width =			j["width"].get<int>();
}


void FillLayerData(const std::string& bytes, unsigned int* decodedDataArray)
{


	for (size_t i = 0; i < bytes.size(); i += 4)
	{
		int x = 0;
		x |= (bytes[i + 0] << 0);
		x |= (bytes[i + 1] << 8);
		x |= (bytes[i + 2] << 16);
		x |= (bytes[i + 3] << 24);

		decodedDataArray[i / 4] = x;
	}
}

void FillTileLayer(const json& jVal, TMLayer& layer)
{
	layer.Encoding =  jVal["encoding"].get<std::string>();
	layer.Height =	  jVal["height"].get<int>();
	layer.Name =	  jVal["name"].get<std::string>();
	layer.Opacity =	  jVal["opacity"].get<float>();
	layer.Type =	  jVal["type"].get<std::string>();
	layer.IsVisible = jVal["visible"].get<bool>();
	layer.Width =	  jVal["width"].get<int>();
	layer.X =		  jVal["x"].get<int>();
	layer.Y =		  jVal["y"].get<int>();



	size_t dataArraySize = layer.Width * layer.Height;

	std::string b64Data = jVal["data"].get<std::string>();
	std::string decodedBytes = Base64::Decode(b64Data);

	if (dataArraySize != decodedBytes.size() / 4) throw std::exception("TMLayer data bad format.");

	layer.DataArray = new unsigned int[dataArraySize]();
	FillLayerData(decodedBytes, layer.DataArray);

	
}

bool TileMap::Load(const char * path)
{
	json j;
	std::ifstream i = std::ifstream(path);
	i >> j;

	// load tile info

	if (!j.is_object()) return false;
	
	FillTileMap(j, *this);
	
	// load tile sets

	json jSets = j["tilesets"];
	if (!jSets.is_array()) return false;
	
	TileSets.resize(jSets.size());

	for (size_t i = 0; i < jSets.size(); ++i)
	{
		FillTileSet(jSets[i], TileSets[i]);
	}
	
	// load tile layers

	json jLayers = j["layers"];

	if (!jLayers.is_array()) return false;
	
	Layers.resize(jLayers.size());

	try
	{
		for (size_t i = 0; i < jLayers.size(); i++)
		{
			FillTileLayer(jLayers[i], Layers[i]);
		}
	}
	catch (std::exception& ex)
	{
		return false;
	}

	return true;
}
