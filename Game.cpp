//Game.cpp
#include <iostream>
#include <SDL.h>

#include "Game.h"
#include "TextureManager.h"
// id for the vector of flipped cards
int Game::flippedCardId = 0;

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
		//SDL_RenderClear(renderer);
		TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);
		TextureManager::Instance()->drawTexture("start_button", { startXPos, startYPos, startWidth, startHeight }, renderer);
		SDL_RenderPresent(renderer);


	}
	else if (state == NormalPlay)
	{
		//SDL_RenderClear(renderer);
		TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);
		TextureManager::Instance()->drawTexture("start_button", { startXPos, startYPos, startWidth, startHeight }, renderer);
		// draw decks
		drawPlayersDeck();
		drawPlayersCardsUp();

		SDL_RenderPresent(renderer);

		checkIfActivePlayersPlacedCards();
	}
	else if (state == WarPlay)
	{
		TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);
		TextureManager::Instance()->drawTexture("start_button", { startXPos, startYPos, startWidth, startHeight }, renderer);

		drawPlayersDeck();
		drawPlayersCardsUp();

		SDL_RenderPresent(renderer);

		checkIfActivePlayersPlacedCards();

	}

}

void Game::update()
{
	if (mouseXDown > startXPos && mouseXDown < (startXPos + startWidth)
		&& mouseYDown > startYPos && mouseYDown < (startYPos + startHeight)
		&& state == Initial)
	{
		std::cout << "Start pressed" << std::endl;
		createPlayers();
		// populate players deck
		dealCardsToPlayers();
		//change state
		state = NormalPlay;
	}
	if (state == NormalPlay)
	{
		for (int i = 0; i < players.size(); i++)
		{
			if (mouseXDown > players.at(i).getPlayerBackCardPosX()
				&& mouseXDown < (players.at(i).getPlayerBackCardPosX() + emptyCard.getCardWidth())
				&& mouseYDown > players.at(i).getPlayerBackCardPosY()
				&& mouseYDown < (players.at(i).getPlayerBackCardPosY() + emptyCard.getCardHeight()))
			{
				//players.at(i).playerState = Player::PlayerCardOpen;
				players.at(i).playerShowCard = true;
				mouseXDown = 0;
				mouseYDown = 0;
			}
		}
	}
	else if (state == WarPlay)
	{
		for (int i = 0; i < players.size(); i++)
		{
			if (mouseXDown > players.at(i).getPlayerBackCardPosX()
				&& mouseXDown < (players.at(i).getPlayerBackCardPosX() + emptyCard.getCardWidth())
				&& mouseYDown > players.at(i).getPlayerBackCardPosY()
				&& mouseYDown < (players.at(i).getPlayerBackCardPosY() + emptyCard.getCardHeight())
				&& players.at(i).playerAtWar)
			{
				//players.at(i).playerState = Player::PlayerCardOpen;
				players.at(i).playerShowWarCard = true;
				mouseXDown = 0;
				mouseYDown = 0;
			}
		}
	}
	
}

void Game::drawPlayersDeck()
{
	for (int i = 0; i < players.size(); i++)
	{
		if (players.at(i).playerReady)
		{
			TextureManager::Instance()->drawTexture(emptyCard.getID(), 
				{ players.at(i).getPlayerBackCardPosX(), players.at(i).getPlayerBackCardPosY(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, players.at(i).getCardAngle());
		}
	}
}

void Game::drawPlayersCardsUp()
{
	if (state == NormalPlay)
	{
		for (int i = 0; i < players.size(); i++)
		{
			if (players.at(i).playerShowCard)
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
	else if (state == WarPlay)
	{
		int lastElementId = discardedCards.size();
		
		for (int i = 0; i < players.size(); i++)
		{
			if (players.at(i).playerShowWarCard)
			{
				// draw deck
				TextureManager::Instance()->drawTexture(emptyCard.getID(),
					{ players.at(i).getPlayerBackCardPosX(), players.at(i).getPlayerBackCardPosY(),
					emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, players.at(i).getCardAngle());
				// draw face up card
				TextureManager::Instance()->drawTexture(players.at(i).getPlayerDeck().front().getID(),
					{ players.at(i).getPlayerFaceUpCardPosX(), players.at(i).getPlayerFaceUpCardPosY(),
					emptyCard.getCardWidth(), emptyCard.getCardHeight() },renderer);
				++lastElementId;
			}
			else
			{
				// draw deck
				TextureManager::Instance()->drawTexture(emptyCard.getID(),
					{ players.at(i).getPlayerBackCardPosX(), players.at(i).getPlayerBackCardPosY(),
					emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, players.at(i).getCardAngle());
				// draw face up card
				TextureManager::Instance()->drawTexture(discardedCards.at(lastElementId - flippedCardId).getID(),
					{ players.at(i).getPlayerFaceUpCardPosX(), players.at(i).getPlayerFaceUpCardPosY(),
					emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer);
				++lastElementId;
			}
		}
	}
	
}

void Game::checkIfActivePlayersPlacedCards()
{
	int cardsOpen = 0;
	for (int i = 0; i < players.size(); i++)
	{
		if (players.at(i).playerShowCard)
		{
			cardsOpen++;
		}
		else if (players.at(i).playerShowWarCard || players.at(i).playerInactive)
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
	int highestCard = players.at(0).getPlayerDeck().front().getPower();
	int playerId = players.at(0).getPlayerID();
	for (int i = 1; i < players.size(); i++)
	{
		int currentCard = players.at(i).getPlayerDeck().front().getPower();
		if (highestCard < currentCard)
		{
			highestCard = currentCard;
			playerId = players.at(i).getPlayerID();
			players.at(i - 1).playerLostBattle = true;
			players.at(i - 1).playerAtWar = false;

			players.at(playerId).playerWonBattle = true;
		}
		else if (highestCard > currentCard)
		{
			players.at(i).playerLostBattle = true;
			players.at(playerId).playerWonBattle = true;
		}
		else if (highestCard == currentCard)
		{
			players.at(playerId).playerAtWar = true;
			players.at(playerId).playerWonBattle = false;
			players.at(i).playerAtWar = true;
		}
		
	}
	updatePlayersDecks();
}

void Game::updatePlayersDecks()
{
	// counter for winner
	int playerWonCounter = 0;
	// winner player Id
	int playerId = -1;
	// for loop for checking if someone won
	for (int i = 0; i < players.size(); i++)
	{
		// if playerWonBattle returns true, increment winner count and get Id
		if (players.at(i).playerWonBattle)
		{
			playerWonCounter++;
			playerId = players.at(i).getPlayerID();
		}
	}
	// 
	if (playerWonCounter > 0)
	{
		//TO DO
		// statistics set winner battle points
		for (int i = 0; i < players.size(); i++)
		{
			if (players.at(i).playerAtWar)
			{
				players.at(i).playerShowWarCard = false;
				continue;
			}
			discardedCards.push_back(players.at(i).getPlayerDeck().front());
			players.at(i).updatePlayerDeck().pop();

			players.at(i).playerWonBattle = false;
			players.at(i).playerAtWar = false;
			players.at(i).playerLostBattle = false;
			players.at(i).playerShowCard = false;
			players.at(i).playerInactive = false;

		}
		for (int i = 0; i < discardedCards.size(); i++)
		{
			players.at(playerId).updatePlayerDeck().push(discardedCards.at(i));
		}
		discardedCards.clear();
		
		//erase players if they have zero cards in deck
		// using lambda expression
		players.erase(std::remove_if(players.begin(), players.end(), [](Player& player) { return player.getPlayerDeck().size() == 0; }), players.end());
		if (players.size() == 1)
		{
			state = Initial;
		}
		else
		{
			state = NormalPlay;
		}
	}
	else
	{
		flippedCardId = 0;
		for (int i = 0; i < players.size(); i++)
		{
			if (players.at(i).playerAtWar)
			{
				flippedCardId++;

				players.at(i).playerWonBattle = false;
				players.at(i).playerLostBattle = false;
				players.at(i).playerShowCard = false;
				players.at(i).playerShowWarCard = false;
				players.at(i).playerInactive = false;
				discardedCards.push_back(players.at(i).getPlayerDeck().front());
				players.at(i).updatePlayerDeck().pop();
				if (players.at(i).getPlayerDeck().size() == 0)
				{
					Card c = pickCard();
					if (c.getPower() != 0)
					{
						players.at(i).updatePlayerDeck().push(c);
					}
				}
			}
			else
			{
				players.at(i).playerInactive = true;
				players.at(i).playerShowCard = false;
				players.at(i).playerShowWarCard = false;
				players.at(i).playerWonBattle = false;
				players.at(i).playerLostBattle = false;
			}
		}
		//erase players if they have zero cards in deck
		// using lambda expression
		players.erase(std::remove_if(players.begin(), players.end(), [](Player& player) { return player.getPlayerDeck().size() == 0; }), players.end());
		if (players.size() == 1)
		{
			state = Initial;
		}
		else
		{
			state = WarPlay;
		}
	}

}


void Game::dealCardsToPlayers()
{
	deck.createDeck();

	for (int i = 0; i < 1; i++)
	{
		players.at(0).updatePlayerDeck().push(Card(std::to_string(i+2), "Spades", std::to_string(i), i+2));
		deck.updateDeck().pop();
		players.at(1).updatePlayerDeck().push(Card(std::to_string(i+2), "Diamonds", std::to_string(i + 13), i+2));
		deck.updateDeck().pop();
		players.at(2).updatePlayerDeck().push(Card(std::to_string(i+2), "Hearts", std::to_string(i + 26), i+2));
		deck.updateDeck().pop();
	}
	//players.at(0).updatePlayerDeck().push(Card("2", "Clubs", "0", 2));
	//players.at(1).updatePlayerDeck().push(Card("3", "Diamonds", "14", 3));
	//players.at(2).updatePlayerDeck().push(Card("3", "Hearts", "27", 3));
	players.at(0).playerReady = true;
	players.at(1).playerReady = true;
	players.at(2).playerReady = true;

}

void Game::createPlayers()
{
	if (players.size() > 0)
	{
		players.clear();
	}
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
	for (int i = 0; i < players.size(); i++)
	{
		players.at(i).playerAtWar = false;
		players.at(i).playerInactive = false;
		players.at(i).playerReady = false;
		players.at(i).playerLostBattle = false;
		players.at(i).playerWonBattle = false;
		players.at(i).playerShowCard = false;
	}
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
	Card c;
	if (deck.getDeck().size() > 0)
	{
		Card c = deck.getDeck().front();
		deck.updateDeck().pop();
		return c;
	}
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