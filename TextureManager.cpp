#include "TextureManager.h"
#include <iostream>

bool TextureManager::loadTexture(const char* fileName,
	std::string id,
	SDL_Renderer* ren)
{
	SDL_Surface* tempSurface = IMG_Load(fileName);

	if (!tempSurface)
	{
		std::cout << "Temp surface could not load.\n";
		return false;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);

	SDL_FreeSurface(tempSurface);
	tempSurface = nullptr; // free address

	if (tex != 0) {
		textureMap[id] = tex;
		return true;
	}

	return false;
}

void TextureManager::drawTexture(std::string id,
	SDL_Rect destRect,
	SDL_Renderer* ren,
	double angle,
	SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(ren, textureMap[id], NULL, &destRect, angle, 0, flip);
}

TextureManager::~TextureManager()
{
	delete instance;
	instance = nullptr;
}

TextureManager* TextureManager::instance = 0;