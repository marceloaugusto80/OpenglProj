#include "stdafx.h"
#include "TileMapComponent.h"
#include "Base\Entity.h"
#include "RenderComponent.h"
#include "Game.h"

void RenderTiles(Entity& go, const TileMap& tileMap)
{
	const TMTileSet& set1 = tileMap.TileSets[0];
	
	std::vector<Rectf> tileUvs(set1.TileCount);
	size_t imgCols = set1.Columns;
	size_t imgRows = set1.TileCount / set1.Columns;

	for (size_t row = 0; row < imgRows; row++)
	{
		for (size_t col = 0; col < imgCols; col++)
		{
			int idx = row * imgCols + col;
			Rectf rect;
			
			/*rect.TopLeft = { 
				static_cast<float>(col * set1.TileWidth), 
				static_cast<float>(row * set1.TileHeight) };
			rect.BottomRight = {
				rect.TopLeft.x + set1.TileWidth,
				rect.TopLeft.y + set1.TileHeight
			};*/
			
			tileUvs.push_back(rect);

		}
	}


	std::string img1Path = std::string("Resources\\Tiles\\") + set1.Image;

	auto tex1 = TheGame->Render().LoadTexture(img1Path.c_str());
	

	const TMLayer& layer1 = tileMap.Layers[0];

	for (size_t row = 0; row < layer1.Height; row++)
	{
		for (size_t col = 0; col < layer1.Width; col++)
		{
			int idx = row * imgCols + col;

			RenderComponent* rc = go.AddComponent<RenderComponent>();
			rc->SetTexture(tex1);
			unsigned int tileId = layer1.DataArray[idx];
			rc->SetTextureUV(tileUvs[tileId + 1]);
			rc->SetSize(Vec2(set1.TileWidth * 0.3, set1.TileHeight * 0.3));
			rc->SetOffset(Vec2(
				static_cast<float>(idx * tileMap.TileWidth) * 0.3,
				static_cast<float>(idx * tileMap.TileHeight) * 0.3
			));
		}
	}



	

}

bool TileMapComponent::Load(const char * tileMapFile)
{
	if (!m_tileMap.Load(tileMapFile)) return false;
	
	RenderTiles(*GetOwner(), m_tileMap);

	return true;
}
