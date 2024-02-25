#pragma once
#include "Game.h"
#include <string>
#include <map>


class TextureManager
{
public:
	bool loadTexture(const char* fileName,
		std::string id,
		SDL_Renderer* ren);

	void drawTexture(std::string id,
		SDL_Rect destRect,
		SDL_Renderer* ren,
		double angle = 0,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	static TextureManager* Instance()
	{
		if (!instance)
		{
			instance = new TextureManager();
			return instance;
		}
		return instance;
	}

	~TextureManager();

private:
	TextureManager() {}
	std::map<std::string, SDL_Texture*> textureMap;
	static TextureManager* instance;
};

