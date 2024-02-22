//Game.cpp
#include <iostream>
#include <SDL.h>

#include "Game.h"
#include "TextureManager.h"

Game::Game()
{
	this->window = NULL;
	this->renderer = NULL;
	this->running = true;
	this->backgroundWidth = 0;
	this->backgroundHeight = 0;
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
				SDL_SetRenderDrawColor(renderer, 255, 100, 100, 255);

				// load textures
				loadTextures();
				// initialize Players
				createPlayers();
				// populate players deck
				dealCardsToPlayers();
				//set backround width and height
				backgroundWidth = width;
				backgroundHeight = height;
				startXPos = (width / 2) - (startWidth / 2);
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
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	//Background Image upload
	TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);

	TextureManager::Instance()->drawTexture("start_button", {startXPos, startYPos, startWidth, startHeight}, renderer);

	drawPlayersDeck(hasGameStarted);
	drawPlayersCardsUp(isPlayerOneDeckPressed, isPlayerTwoDeckPressed, isPlayerThreeDeckPressed);
	
	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_WaitEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_MOUSEBUTTONDOWN: {
			int msx, msy;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&msx, &msy);
				mouseXDown = msx;
				mouseYDown = msy;
			}

		}; break;
		}
	}
	/*if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: running = false; break;
		case SDL_MOUSEBUTTONDOWN: {
			int msx, msy;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&msx, &msy);
				mouseXDown = msx;
				mouseYDown = msy;
			}
			
		}; break;
		case SDL_MOUSEBUTTONUP: {
			int msx, msy;
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&msx, &msy);
				mouseXUp = msx;
				mouseYUp = msy;
			}
			
		}; break;
		default: break;

		}
	}*/
}

void Game::update()
{
	std::cout << "Update" << std::endl;
	if (mouseXDown > startXPos && mouseXDown < (startXPos + startWidth)
		&& mouseYDown > startYPos && mouseYDown < (startYPos + startHeight))
	{
		hasGameStarted = true;
	}
	if (mouseXDown > player1DeckPosX && mouseXDown < (player1DeckPosX + emptyCard.getCardWidth())
		&& mouseYDown > player1DeckPosY && mouseYDown < (player1DeckPosY + emptyCard.getCardHeight()))
	{
		isPlayerOneDeckPressed = true;
	}
	if (mouseXDown > player2DeckPosX && mouseXDown < (player2DeckPosX + emptyCard.getCardWidth())
		&& mouseYDown > player2DeckPosY && mouseYDown < (player2DeckPosY + emptyCard.getCardHeight()))
	{
		isPlayerTwoDeckPressed = true;
	}
	if (mouseXDown > player3DeckPosX && mouseXDown < (player3DeckPosX + emptyCard.getCardWidth())
		&& mouseYDown > player3DeckPosY && mouseYDown < (player3DeckPosY + emptyCard.getCardHeight()))
	{
		isPlayerThreeDeckPressed = true;
	}
}

void Game::createPlayers()
{
	Player firstPlayer;
	Player secondPlayer;
	Player thirdPlayer;

	firstPlayer.setPlayerID(0);
	secondPlayer.setPlayerID(1);
	thirdPlayer.setPlayerID(2);

	players.push_back(firstPlayer);
	players.push_back(secondPlayer);
	players.push_back(thirdPlayer);
}

void Game::dealCardsToPlayers()
{
	for (int i = 0; i < 10; i++)
	{
		players.at(0).updatePlayerDeck().push(deck.getDeck().front());
		deck.updateDeck().pop();
		players.at(1).updatePlayerDeck().push(deck.getDeck().front());
		deck.updateDeck().pop();
		players.at(2).updatePlayerDeck().push(deck.getDeck().front());
		deck.updateDeck().pop();
	}
	isPlayerOnePlaying = true;
	isPlayerTwoPlaying = true;
	isPlayerThreePlaying = true;
}

void Game::drawPlayersDeck(bool hasGameStarted)
{
	if (hasGameStarted)
	{
		TextureManager::Instance()->drawTexture(emptyCard.getID(), { player1DeckPosX, player1DeckPosY, emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, 90);
		TextureManager::Instance()->drawTexture(emptyCard.getID(), { player3DeckPosX, player3DeckPosY, emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, 90);
		TextureManager::Instance()->drawTexture(emptyCard.getID(), { player2DeckPosX, player2DeckPosY, emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, 0);
	}
}

void Game::drawPlayersCardsUp(bool p1Pressed, bool p2Pressed, bool p3Pressed)
{
	if (p1Pressed)
	{
		if (players.at(0).getPlayerDeck().size() > 0)
		{
			TextureManager::Instance()->drawTexture(players.at(0).getPlayerDeck().front().getID(),
				{ player1CardPosX, player1CardPosY, emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer);
		}
		else
		{
			isPlayerOnePlaying = false;
		}
		
	}
	
	if (p2Pressed)
	{
		if (players.at(1).getPlayerDeck().size() > 0)
		{
			TextureManager::Instance()->drawTexture(players.at(1).getPlayerDeck().front().getID(),
				{ player2CardPosX, player2CardPosY, emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer);
		}
		else
		{
			isPlayerTwoPlaying = false;
		}
	}

	if (p3Pressed)
	{
		if (players.at(2).getPlayerDeck().size() > 0)
		{
			TextureManager::Instance()->drawTexture(players.at(2).getPlayerDeck().front().getID(),
				{ player3CardPosX, player3CardPosY, emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer);
		}
		else
		{
			isPlayerThreePlaying = false;
		}
	}
}

Card Game::pickCard()
{
	Card c = deck.getDeck().front();
	deck.getDeck().pop();
	return c;
}

std::vector<Player> Game::getPlayers() const
{
	return this->players;
}

std::vector<Player>& Game::updatePlayers()
{
	return this->players;
}

std::queue<Card> Game::getDiscardedCards() const
{
	return this->discardedCards;
}

std::queue<Card>& Game::updateDiscardedCards()
{
	return this->discardedCards;
}


void Game::loadTextures()
{
	TextureManager::Instance()->loadTexture("./assets/background.jpg",
		"background",
		renderer);
	TextureManager::Instance()->loadTexture("./assets/cardBack_red5.png",
		"backCard",
		renderer);
	TextureManager::Instance()->loadTexture("./assets/start_button.png",
		"start_button",
		renderer);

	for (int i = 0; i < 52; i++)
	{
		std::string id = std::to_string(i);
		std::string path;
		path.append("./assets/").append(id).append(".png");
		TextureManager::Instance()->loadTexture(path.data(), id,
			renderer);
	}
}


bool Game::isRunning()
{
	return Game::running;
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