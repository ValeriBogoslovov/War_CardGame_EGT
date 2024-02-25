#include <iostream>
#include "DeckOfCards.h"
#include "Game.h"

Game* game = NULL;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

// 30 frames per second
const int FPS = 30;
// set speed of the game, reduces CPU usage
void setFPS(unsigned int startingTick) {

	if ((1000 / FPS) > SDL_GetTicks() - startingTick) {
		SDL_Delay((1000 / FPS) - (SDL_GetTicks() - startingTick));
	}
}

int main(int argc, char* argv[])
{
	game = new Game();
	game->init("War card game window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	while (game->isRunning())
	{
		unsigned int startingTick = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		setFPS(startingTick);
	}
	game->clean();

	//TO DO
	// Deal cards - done
	// Implement rules (check for wars, power of cards)
	// Point system -> Statistic static members for each player?
	// Restart game
	// Statistics
	// Graphics

	delete game;
	game = nullptr;
    return 0;
}

