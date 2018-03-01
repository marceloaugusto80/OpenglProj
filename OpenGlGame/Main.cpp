#include "stdafx.h"
#include "Game.h"

int main(int argc, char** argv)
{
	
	Configuration config;
	config.GameTitle = "Game";

	RenderConfig renderConfig;
	renderConfig.ScreenWidth = 1280;
	renderConfig.ScreenHeigth = 800;
	renderConfig.SpriteMaxCount= 2000;
	renderConfig.MaxTextureCount = 20;
	renderConfig.TextureMaxWidth = 256;
	renderConfig.TextureMaxHeight = 256;

	Game* game = Game::Create(config, renderConfig);
	if (game)
	{
		game->Start();
	}
	return 0;

}