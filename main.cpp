#include <iostream>
#include "DeckOfCards.h"
#include "Game.h"
#include "GameService.h"

Game* game = NULL;
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

int main(int argc, char* argv[])
{
	//game = new Game();
	//game->init("War card game window",
	//SDL_WINDOWPOS_CENTERED,
	//SDL_WINDOWPOS_CENTERED,
	//WINDOW_WIDTH, WINDOW_HEIGHT,
	//SDL_WINDOW_RESIZABLE);
	GameService gs;
	gs.createPlayers();
	gs.dealCardsToPlayers();

	while (!gs.playerWon)
	{
		int input = 0;
		std::cout << "Press 1 for next round.\n";
		std::cin >> input;
		if (input == 1)
		{
			gs.putCardToTable();
			gs.checkPlayersCards();
		}
	}
	/*while (game->isRunning())
	{
		game->handleEvents();
		game->update();
		game->render();
		
	}
	game->clean();*/

	//TO DO
	// Deal cards - done
	// Implement rules (check for wars, power of cards)
	// Point system
	// Restart game
	// Statistics
	// Graphics

	// delete game;
	// game = nullptr;
	return 0;
}

