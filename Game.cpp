//Game.cpp
#include <iostream>
#include <SDL.h>

#include "Game.h"
#include "TextureManager.h"

Game::Game()
{
	Game::window = NULL;
	Game::renderer = NULL;
	Game::running = true;
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window != 0) //window init success
		{
			std::cout << "window creation success\n";
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer != 0) //renderer init success
			{
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

				// load background
				TextureManager::Instance()->loadTexture("./assets/background.jpg",
					"background",
					renderer);

				// load all playing cards
				//for (int i = 0; i < 4; i++)
				//{
				//	for (int j = 0; j < 14; j++)
				//	{
				//		// load texture cards
				//	}
				//}
			}
			else
			{
				std::cout << "renderer init failed\n";
				return false;
			}
		}
		else
		{
			std::cout << "window init failed\n";
			return false;
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false;
	}
	std::cout << "init success\n";
	running = true;
	return true;
}



void Game::render()
{
	SDL_RenderClear(renderer);

	//Background Image upload
	// Licence Image by <a href="https://www.freepik.com/free-vector/gradient-poker-table-background_94959238.htm#query=blackjack%20background&position=29&from_view=search&track=ais&uuid=af0baaae-6b29-4a09-9a62-962c07164214">Freepik</a>

	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: running = false; break;
		case SDL_KEYDOWN: {
			if (event.key.keysym.sym == SDLK_SPACE)
			{
				createPlayers();
				dealCardsToPlayers();
			}
		}; break;
		default: break;

		}
	}
}

void Game::update()
{

}



bool Game::isRunning()
{
	return Game::running;
}

void Game::createPlayers()
{
	Player firstPlayer;
	Player secondPlayer;
	Player thirdPlayer;

	players.push_back(firstPlayer);
	players.push_back(secondPlayer);
	players.push_back(thirdPlayer);
}

void Game::dealCardsToPlayers()
{
	for (int i = 0; i < 10; i++)
	{
		players.at(0).addCard(deck.getDeck().front());
		deck.getDeck().pop();
		players.at(1).addCard(deck.getDeck().front());
		deck.getDeck().pop();
		players.at(2).addCard(deck.getDeck().front());
		deck.getDeck().pop();
	}
}

void Game::putCardToTable()
{

}

void Game::checkPlayersCards()
{
}

Card Game::drawCard()
{
	Card c = deck.getDeck().front();
	deck.getDeck().pop();
	return c;
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

Game::~Game()
{
	renderer = nullptr;
	window = nullptr;
}