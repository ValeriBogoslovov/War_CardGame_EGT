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
	SDL_Delay(100);
	SDL_RenderClear(renderer);
	
	int width, height;
	SDL_GetWindowSize(window, &width, &height);

	if (state == Initial)
	{
		TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);
		TextureManager::Instance()->drawTexture("start_button", { startXPos, startYPos, startWidth, startHeight }, renderer);
		SDL_RenderPresent(renderer);
	}
	else if (state == NormalPlay)
	{
		TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);
		TextureManager::Instance()->drawTexture("start_inactive", { startXPos, startYPos, startWidth, startHeight }, renderer);

		// draw decks
		drawPlayersDeck();
		// check placed cards of Active players
		if (checkIfActivePlayersPlacedCards())
		{
			// compare power of players cards
			comparePlayersCardsPower();
			// update players deck after comparison
			updatePlayersDecks();
		}
		SDL_RenderPresent(renderer);
		
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
	else if (state == NormalPlay)
	{
		for (int i = 0; i < players.size(); i++)
		{
			if (mouseXDown > players.at(i).getPlayerCard().getBackCardXPos()
				&& mouseXDown < (players.at(i).getPlayerCard().getBackCardXPos() + players.at(i).getPlayerCard().getCardWidth())
				&& mouseYDown > players.at(i).getPlayerCard().getBackCardYPos()
				&& mouseYDown < (players.at(i).getPlayerCard().getBackCardYPos() + players.at(i).getPlayerCard().getCardHeight())
				&& players.at(i).playerState == Player::PlayerReady)
			{
				players.at(i).playerState = Player::PlayerCardOpen;
				players.at(i).updatePlayerDiscardedDeck().push(players.at(i).getPlayerDeck().front());
				players.at(i).updatePlayerDeck().pop();
				discardedCards.push_back(players.at(i).getPlayerDiscardedDeck().top());
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
		if (players.at(i).playerState == Player::PlayerReady || players.at(i).playerState == Player::Inactive)
		{
			TextureManager::Instance()->drawTexture(emptyCard.getID(),
				{ players.at(i).getPlayerCard().getBackCardXPos(), players.at(i).getPlayerCard().getBackCardYPos(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, players.at(i).getPlayerCard().getCardAngle());
		}
		if ((players.at(i).getAtWar() && players.at(i).playerState != Player::Inactive)
			|| players.at(i).playerState == Player::PlayerCardOpen)
		{
			TextureManager::Instance()->drawTexture(emptyCard.getID(),
				{ players.at(i).getPlayerCard().getBackCardXPos(), players.at(i).getPlayerCard().getBackCardYPos(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, players.at(i).getPlayerCard().getCardAngle());

			TextureManager::Instance()->drawTexture(players.at(i).getPlayerDiscardedDeck().top().getID(),
				{ players.at(i).getPlayerCard().getFaceCardXPos(), players.at(i).getPlayerCard().getFaceCardYPos(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer);
			
		}
	}
}

bool Game::checkIfActivePlayersPlacedCards()
{
	int cardsOpen = 0;
	for (int i = 0; i < players.size(); i++)
	{
		if (players.at(i).playerState == Player::PlayerCardOpen || players.at(i).playerState == Player::Inactive)
		{
			cardsOpen++;
		}
	}
	if (cardsOpen == players.size())
	{
		return true;
	}
	return false;
}

void Game::comparePlayersCardsPower()
{
	// get previous and current card and player Id
	int previousCard = 0;
	int previousPlayerId = 0;
	int currentCard = 0;
	int currentCardPlayerId = -1;

	for (int i = 0; i < players.size(); i++)
	{
		
		if (players.at(i).playerState == Player::Inactive)
		{
			continue;
		}
		currentCard = players.at(i).getPlayerDiscardedDeck().top().getPower();
		currentCardPlayerId = players.at(i).getPlayerID();

		if (previousCard < currentCard)
		{
			previousCard = currentCard;
			players.at(previousPlayerId).playerState = Player::Inactive;
			previousPlayerId = players.at(currentCardPlayerId).getPlayerID();

			players.at(previousPlayerId).playerState = Player::WonBattle;
		}
		else if (previousCard > currentCard)
		{
			players.at(currentCardPlayerId).playerState = Player::Inactive;
			players.at(currentCardPlayerId).updateAtWar(false);

		}
		else if (previousCard == currentCard)
		{
			players.at(currentCardPlayerId).updateAtWar(true);
			players.at(currentCardPlayerId).playerState = Player::PlayerReady;
			players.at(previousPlayerId).updateAtWar(true);
			players.at(previousPlayerId).playerState = Player::PlayerReady;
		}

	}
}

void Game::updatePlayersDecks()
{
	int playersAtWarCounter = 0;
	// winner player Id
	int playerId = -1;
	// for loop for checking if someone won
	for (int i = 0; i < players.size(); i++)
	{
		// if playerWonBattle returns true, increment winner count and get Id
		if (players.at(i).playerState == Player::WonBattle)
		{
			// get winner, update points of battle
			playerId = players.at(i).getPlayerID();
			std::cout << "Player: " << playerId + 1 << " wins" << std::endl;
			for (int i = 0; i < discardedCards.size(); i++)
			{
				players.at(playerId).updatePlayerDeck().push(discardedCards.at(i));
			}
			discardedCards.clear();
			for (int i = 0; i < players.size(); i++)
			{
				players.at(i).playerState = Player::PlayerReady;
				players.at(i).updateAtWar(false);
			}
			break;
		}
		else if (players.at(i).getAtWar())
		{
			playersAtWarCounter++;
		}
	}
	if (playersAtWarCounter > 1)
	{
		for (int i = 0; i < players.size(); i++)
		{
			if (players.at(i).getAtWar()
				&& players.at(i).getPlayerDeck().size() == 0 
				&& players.at(i).playerState != Player::Inactive)
			{
				Card c = pickCard();
				if (c.getPower() > 0)
				{
					players.at(i).updatePlayerDeck().push(c);
				}
			}
		}
	}

	//erase players if they have zero cards in deck
	// using lambda expression
	players.erase(std::remove_if(players.begin(), players.end(), [](Player& player) { return player.getPlayerDeck().size() == 0; }), players.end());

	if (players.size() == 1)
	{
		// We have a winner, get winner, set points
		std::cout << "Player " << players.at(0).getPlayerID() + 1 << " WINS THE GAME!" << std::endl;
		state = Initial;
	}

}

void Game::dealCardsToPlayers()
{
	deck.createDeck();

	for (int i = 0; i < 10; i++)
	{
		players.at(0).updatePlayerDeck().push(Card(deck.getDeck().front()));
		deck.updateDeck().pop();
		players.at(1).updatePlayerDeck().push(Card(deck.getDeck().front()));
		deck.updateDeck().pop();
		players.at(2).updatePlayerDeck().push(Card(deck.getDeck().front()));
		deck.updateDeck().pop();
	}

	players.at(0).playerState = Player::PlayerReady;
	players.at(1).playerState = Player::PlayerReady;
	players.at(2).playerState = Player::PlayerReady;

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
	firstPlayer.setPlayerCard().setCardAngle(90);
	firstPlayer.setPlayerCard().setBackCardXPos(100);
	firstPlayer.setPlayerCard().setBackCardYPos(250);
	firstPlayer.setPlayerCard().setFaceCardXPos(450);
	firstPlayer.setPlayerCard().setFaceCardYPos(250);

	secondPlayer.setPlayerID(1);
	secondPlayer.setPlayerCard().setCardAngle(0);
	secondPlayer.setPlayerCard().setBackCardXPos(600);
	secondPlayer.setPlayerCard().setBackCardYPos(500);
	secondPlayer.setPlayerCard().setFaceCardXPos(600);
	secondPlayer.setPlayerCard().setFaceCardYPos(250);

	thirdPlayer.setPlayerID(2);
	thirdPlayer.setPlayerCard().setCardAngle(90);
	thirdPlayer.setPlayerCard().setBackCardXPos(1000);
	thirdPlayer.setPlayerCard().setBackCardYPos(250);
	thirdPlayer.setPlayerCard().setFaceCardXPos(750);
	thirdPlayer.setPlayerCard().setFaceCardYPos(250);

	players.push_back(firstPlayer);
	players.push_back(secondPlayer);
	players.push_back(thirdPlayer);
	for (int i = 0; i < players.size(); i++)
	{
		players.at(i).playerState = Player::PlayerReady;
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
	TextureManager::Instance()->loadTexture("./assets/start.png",
		"start_button",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p1.png",
		"player 1",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p1-inactive.png",
		"p1-inactive",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p2.png",
		"player 2",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p2-inactive.png",
		"p2-inactive",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p3.png",
		"player 3",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p3-inactive.png",
		"p3-inactive",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/c.png",
		"card_counter",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/start-inactive.png",
		"start_inactive",
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