#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Player.h"
#include "DeckOfCards.h"

class Game
{
public:
	Game();
	~Game();
	bool init(const char* title,
		int xpos,
		int ypos,
		int width,
		int height,
		int flags);

	void render();
	void update();
	void handleEvents();

	void clean();

	bool isRunning();

	void createPlayers();
	void dealCardsToPlayers();
	void putCardToTable();
	void checkPlayersCards();

	bool isWar = false;
	Card drawCard();

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;

	std::vector<Player> players;
	DeckOfCards deck;
};