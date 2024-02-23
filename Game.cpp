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
				
				//set backround width and height
				backgroundWidth = width;
				backgroundHeight = height;
				startXPos = (width / 2) - (startWidth / 2);
				
				state = Initial;
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

	if (state == Initial)
	{
		TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);
		TextureManager::Instance()->drawTexture("start_button", { startXPos, startYPos, startWidth, startHeight }, renderer);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);

	}
	if (state == NormalPlay)
	{
		TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);

		// draw decks
		drawPlayersDeck();
		drawPlayersCardsUp();
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);

		checkPlayersCards();
	}

}


void Game::update()
{
	if (mouseXDown > startXPos && mouseXDown < (startXPos + startWidth)
		&& mouseYDown > startYPos && mouseYDown < (startYPos + startHeight)
		&& state == Initial)
	{
		std::cout << "Start pressed" << std::endl;
		// populate players deck
		dealCardsToPlayers();
		//change state
		state = NormalPlay;
	}
	for (int i = 0; i < players.size(); i++)
	{
		if (mouseXDown > players.at(i).getPlayerBackCardPosX() 
			&& mouseXDown < (players.at(i).getPlayerBackCardPosX() + emptyCard.getCardWidth())
			&& mouseYDown > players.at(i).getPlayerBackCardPosY()
			&& mouseYDown < (players.at(i).getPlayerBackCardPosY() + emptyCard.getCardHeight()))
		{
			players.at(i).playerState = Player::PlayerCardOpen;
		}
	}
}

void Game::drawPlayersDeck()
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players.at(i).playerState == Player::PlayerReady)
		{
			TextureManager::Instance()->drawTexture(emptyCard.getID(), 
				{ players.at(i).getPlayerBackCardPosX(), players.at(i).getPlayerBackCardPosY(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, players.at(i).getCardAngle());

		}
	}
}

void Game::drawPlayersCardsUp()
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players.at(i).playerState == Player::PlayerCardOpen)
		{
			// draw deck
			TextureManager::Instance()->drawTexture(emptyCard.getID(),
				{ players.at(i).getPlayerBackCardPosX(), players.at(i).getPlayerBackCardPosY(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, players.at(i).getCardAngle());
			// draw face up card
			TextureManager::Instance()->drawTexture(players.at(i).getPlayerDeck().front().getID(),
				{ players.at(i).getPlayerFaceUpCardPosX(), players.at(i).getPlayerFaceUpCardPosY(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer);
		}
	}
}

void Game::checkPlayersCards()
{
	int cardsOpen = 0;
	for (int i = 0; i < players.size(); i++)
	{
		if (players.at(i).playerState == Player::PlayerCardOpen)
		{
			cardsOpen++;
		}
	}
	if (cardsOpen == players.size())
	{
		comparePlayersCardsPower();
	}
}

void Game::comparePlayersCardsPower()
{
	if (players.size() > 1)
	{
		/*int tempCardPower = players.at(0).getPlayerDeck().front().getPower();
		players.at(0).getPlayerDeck().pop();
		if (players.at(0).getPlayerDeck().size() > 0)
		{
			players.at(0).playerState = Player::PlayerReady;
		}
		int playerId = players.at(0).getPlayerID();*/
		for (int i = 0; i < players.size() - 1; i++)
		{
			int tempCardPower = players.at(i).getPlayerDeck().front().getPower();
			int playerId = players.at(i).getPlayerID();
			if (tempCardPower < players.at(i + 1).getPlayerDeck().front().getPower())
			{
				tempCardPower = players.at(i + 1).getPlayerDeck().front().getPower();
				playerId = players.at(i + 1).getPlayerID();
				players.at(i + 1).getPlayerDeck().pop();
			}
			else if (tempCardPower > players.at(i + 1).getPlayerDeck().front().getPower())
			{
				players.at(i + 1).getPlayerDeck().pop();
			}
			else if (tempCardPower == players.at(i + 1).getPlayerDeck().front().getPower())
			{
				players.at(playerId).playerState = Player::PlayerAtWar;
				players.at(i + 1).playerState = Player::PlayerAtWar;
			}

		}
	}
}


void Game::dealCardsToPlayers()
{
	deck.createDeck();

	for (int i = 0; i < 10; i++)
	{
		players.at(0).updatePlayerDeck().push(deck.getDeck().front());
		deck.updateDeck().pop();
		players.at(1).updatePlayerDeck().push(deck.getDeck().front());
		deck.updateDeck().pop();
		players.at(2).updatePlayerDeck().push(deck.getDeck().front());
		deck.updateDeck().pop();
	}

	players.at(0).playerState = Player::PlayerReady;
	players.at(1).playerState = Player::PlayerReady;
	players.at(2).playerState = Player::PlayerReady;

}

void Game::createPlayers()
{
	Player firstPlayer;
	Player secondPlayer;
	Player thirdPlayer;

	firstPlayer.setPlayerID(0);
	firstPlayer.setCardAngle(90);
	firstPlayer.setPlayerBackCardPosX(100);
	firstPlayer.setPlayerBackCardPosY(250);
	firstPlayer.setPlayerFaceUpCardPosX(450);
	firstPlayer.setPlayerFaceUpCardPosY(250);

	secondPlayer.setPlayerID(1);
	secondPlayer.setCardAngle(0);
	secondPlayer.setPlayerBackCardPosX(600);
	secondPlayer.setPlayerBackCardPosY(500);
	secondPlayer.setPlayerFaceUpCardPosX(600);
	secondPlayer.setPlayerFaceUpCardPosY(250);

	thirdPlayer.setPlayerID(2);
	thirdPlayer.setCardAngle(90);
	thirdPlayer.setPlayerBackCardPosX(1000);
	thirdPlayer.setPlayerBackCardPosY(250);
	thirdPlayer.setPlayerFaceUpCardPosX(750);
	thirdPlayer.setPlayerFaceUpCardPosY(250);

	players.push_back(firstPlayer);
	players.push_back(secondPlayer);
	players.push_back(thirdPlayer);
}

void Game::handleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
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
	}
}

Card Game::pickCard()
{
	Card c = deck.getDeck().front();
	deck.getDeck().pop();
	return c;
}

const std::vector<Player>& Game::getPlayers()
{
	return this->players;
}

std::vector<Player>& Game::updatePlayers()
{
	return this->players;
}

const std::vector<Card>& Game::getDiscardedCards()
{
	return this->discardedCards;
}

std::vector<Card>& Game::updateDiscardedCards()
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