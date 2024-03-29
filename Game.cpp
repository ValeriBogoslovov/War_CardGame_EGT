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
				loadTexturesAndSounds();

				//set backround width and height
				backgroundWidth = width;
				backgroundHeight = height;

				this->gameButton.updateWidth(160);
				this->gameButton.updateHeight(80);
				this->gameButton.updateYPos(50);
				this->gameButton.updateIsActive(true);
				this->gameButton.updateXPos((width / 2) - (this->gameButton.getWidth() / 2));
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

	if (state == Initial)
	{

		TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);
		TextureManager::Instance()->drawTexture("start_button", { gameButton.getXPos(),gameButton.getYPos(), gameButton.getWidth(),
			gameButton.getHeight()}, renderer);
		SDL_RenderPresent(renderer);
	}
	else if (state == NormalPlay)
	{

		TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);
		TextureManager::Instance()->drawTexture("start_inactive", { gameButton.getXPos(),gameButton.getYPos(), gameButton.getWidth(),
			gameButton.getHeight() }, renderer);

		// draw decks
		drawPlayersDeck();
		// check placed cards of Active players
		SDL_RenderPresent(renderer);
		if (checkIfActivePlayersPlacedCards())
		{
			// compare power of players cards
			comparePlayersCardsPower();
			// update players deck after comparison
			updatePlayersDecks();
		}
	}
	else if (state == CardsDelay)
	{
		TextureManager::Instance()->drawTexture("background", { 0,0,backgroundWidth, backgroundHeight }, renderer);
		TextureManager::Instance()->drawTexture("start_inactive", { gameButton.getXPos(),gameButton.getYPos(), 
			gameButton.getWidth(),gameButton.getHeight() }, renderer);
		int atWarCounter = 0;
		for (int i = 0; i < players.size(); i++)
		{
			TextureManager::Instance()->drawTexture(emptyCard.getID(),
				{ players.at(i).getPlayerCard().getBackCardXPos(), players.at(i).getPlayerCard().getBackCardYPos(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, players.at(i).getPlayerCard().getCardAngle());

			TextureManager::Instance()->drawTexture(players.at(i).getPlayerButton().getId(),
				{ players.at(i).getPlayerButton().getXPos(), players.at(i).getPlayerButton().getYPos(),
				players.at(i).getPlayerButton().getWidth(), players.at(i).getPlayerButton().getHeight() }, renderer);

			TextureManager::Instance()->drawTexture(players.at(i).getPlayerDiscardedDeck().top().getID(),
				{ players.at(i).getPlayerCard().getFaceCardXPos(), players.at(i).getPlayerCard().getFaceCardYPos(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer);

			if (players.at(i).getAtWar())
			{
				atWarCounter++;
			}
			players.at(i).cardCounter(renderer);
		}
		if (atWarCounter == 0)
		{
			showWinnerOfBattle(renderer);
		}
		

		SDL_RenderPresent(renderer);
		
		state = NormalPlay;
		SDL_Delay(2500);
	}

}

void Game::update()
{
	// check if mouse click is at Start button
	if (mouseXDown > gameButton.getXPos() && mouseXDown < (gameButton.getXPos() + gameButton.getWidth())
		&& mouseYDown > gameButton.getYPos() && mouseYDown < (gameButton.getYPos() + gameButton.getHeight())
		&& state == Initial)
	{
		SoundManager::Instance()->playBackgroundMusic("start", 0);
		SDL_Delay(1200);
		SoundManager::Instance()->playBackgroundMusic("music", -1);

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
			// check if mouse is pressed on player button and the state of the player is Ready
			if (mouseXDown > players.at(i).getPlayerButton().getXPos()
				&& mouseXDown < (players.at(i).getPlayerButton().getXPos() + players.at(i).getPlayerButton().getWidth())
				&& mouseYDown > players.at(i).getPlayerButton().getYPos()
				&& mouseYDown < (players.at(i).getPlayerButton().getYPos() + players.at(i).getPlayerButton().getHeight())
				&& players.at(i).playerState == Player::PlayerReady)
			{
				// change state of player so it will show card
				players.at(i).playerState = Player::PlayerCardOpen;
				// push the top card to the player discarded deck
				players.at(i).updatePlayerDiscardedDeck().push(players.at(i).getPlayerDeck().front());
				// remove top card from player deck
				players.at(i).updatePlayerDeck().pop();
				// add top card to the shared discarded deck
				discardedCards.push_back(players.at(i).getPlayerDiscardedDeck().top());
				// change player button to Inactive
				std::string buttonId = "player_";
				buttonId.append(std::to_string(players.at(i).getPlayerID() + 1)).append("_inactive");
				players.at(i).updatePlayerButton().updateId(buttonId);
				// set mouse x and y position to 0
				mouseXDown = 0;
				mouseYDown = 0;
				// play sound effect
				SoundManager::Instance()->playSFX("sfx2", 0);
			}
		}
	}
}

void Game::drawPlayersDeck()
{
	for (int i = 0; i < players.size(); i++)
	{
		players.at(i).cardCounter(renderer);
		if (players.at(i).playerState == Player::PlayerReady || players.at(i).playerState == Player::Inactive)
		{
			if (players.at(i).playerState == Player::Inactive)
			{
				std::string buttonId = "player_";
				buttonId.append(std::to_string(players.at(i).getPlayerID() + 1)).append("_inactive");
				players.at(i).updatePlayerButton().updateId(buttonId);
			}
			else
			{
				std::string buttonId = "player_";
				buttonId.append(std::to_string(players.at(i).getPlayerID() + 1));
				players.at(i).updatePlayerButton().updateId(buttonId);
			}

			TextureManager::Instance()->drawTexture(emptyCard.getID(),
				{ players.at(i).getPlayerCard().getBackCardXPos(), players.at(i).getPlayerCard().getBackCardYPos(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, players.at(i).getPlayerCard().getCardAngle());

			TextureManager::Instance()->drawTexture(players.at(i).getPlayerButton().getId(),
				{ players.at(i).getPlayerButton().getXPos(), players.at(i).getPlayerButton().getYPos(),
				players.at(i).getPlayerButton().getWidth(), players.at(i).getPlayerButton().getHeight()}, renderer);
			//showWinnerOfBattle(renderer);
		}
		if ((players.at(i).getAtWar() && players.at(i).playerState != Player::Inactive)
			|| players.at(i).playerState == Player::PlayerCardOpen)
		{
			TextureManager::Instance()->drawTexture(emptyCard.getID(),
				{ players.at(i).getPlayerCard().getBackCardXPos(), players.at(i).getPlayerCard().getBackCardYPos(),
				emptyCard.getCardWidth(), emptyCard.getCardHeight() }, renderer, players.at(i).getPlayerCard().getCardAngle());

			TextureManager::Instance()->drawTexture(players.at(i).getPlayerButton().getId(),
				{ players.at(i).getPlayerButton().getXPos(), players.at(i).getPlayerButton().getYPos(),
				players.at(i).getPlayerButton().getWidth(), players.at(i).getPlayerButton().getHeight() }, renderer);

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
	//int currentCardPlayerId = 0;

	for (int i = 0; i < players.size(); i++)
	{
		
		if (players.at(i).playerState == Player::Inactive)
		{
			continue;
		}
		currentCard = players.at(i).getPlayerDiscardedDeck().top().getPower();

		if (previousCard < currentCard)
		{
			players.at(previousPlayerId).playerState = Player::Inactive;
			players.at(i).playerState = Player::WonBattle;
			previousPlayerId = i;
			previousCard = currentCard;
		}
		else if (previousCard > currentCard)
		{
			players.at(i).playerState = Player::Inactive;
			players.at(i).updateAtWar(false);

		}
		else if (previousCard == currentCard)
		{
			players.at(i).updateAtWar(true);
			players.at(i).playerState = Player::PlayerReady;
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
			players.at(i).hasWon = true;
			for (int j = 0; j < discardedCards.size(); j++)
			{
				players.at(i).updatePlayerDeck().push(discardedCards.at(j));
			}
			discardedCards.clear();
			for (int k = 0; k < players.size(); k++)
			{
				players.at(k).playerState = Player::PlayerReady;
				players.at(k).updateAtWar(false);
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
	else
	{
		state = CardsDelay;
	}
}

bool Game::showWinnerOfBattle(SDL_Renderer* ren)
{
	if (TTF_Init() == -1) // return error
	{
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	font = TTF_OpenFont("./assets/segoepr.ttf", 30);

	SDL_Surface* tempSurfaceText = NULL;
	for (int i = 0; i < players.size(); i++)
	{
		if (players.at(i).hasWon)
		{
			tempSurfaceText = TTF_RenderText_Blended(font, "The Winner is Player ", { 255,255,255,255 }); 
			playerNameText = SDL_CreateTextureFromSurface(ren, tempSurfaceText);
			tempSurfaceText = TTF_RenderText_Blended(font, std::to_string(i + 1).data(), {255,255,255,255});
			playerPointsText = SDL_CreateTextureFromSurface(ren, tempSurfaceText);
			int tw, th;
			SDL_QueryTexture(playerNameText, 0, 0, &tw, &th);
			SDL_QueryTexture(playerPointsText, 0, 0, &tw, &th);
			players.at(i).hasWon = false;
		}
	}

	playerNameTextDestRect = { 520,150,200,65 };
	playerPointsTextDestRect = { 720,150,30,65 };

	SDL_RenderCopy(ren, playerNameText, NULL, &this->playerNameTextDestRect);
	SDL_RenderCopy(ren, playerPointsText, NULL, &this->playerPointsTextDestRect);

	SDL_FreeSurface(tempSurfaceText);
	return true;
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
	//players.at(0).updatePlayerDeck().push(Card(0,0,0,0,0,"","", "3",5));
	//players.at(1).updatePlayerDeck().push(Card(0, 0, 0, 0, 0, "", "", "2", 4));
	//players.at(2).updatePlayerDeck().push(Card(0, 0, 0, 0, 0, "", "", "16", 5));
	//players.at(2).updatePlayerDeck().push(Card(0, 0, 0, 0, 0, "", "", "24", 13));

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
	// create players with their deck position and buttons
	Player firstPlayer(0, 100,250,450,250, 90.0, 90, 380, 120, 35, "player_1");
	Player secondPlayer(1, 600, 500, 600, 250, 0, 590, 655, 120, 35, "player_2");
	Player thirdPlayer(2, 1000, 250, 750, 250, 90.0, 990, 380, 120, 35, "player_3");

	firstPlayer.updateCardText(90, 220, 100, 45);
	firstPlayer.updateCardCounter(180, 220, 30, 45);

	secondPlayer.updateCardText(600, 450, 100, 45);
	secondPlayer.updateCardCounter(690, 450, 30, 45);

	thirdPlayer.updateCardText(990, 220, 100, 45);
	thirdPlayer.updateCardCounter(1080, 220, 30, 45);


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


void Game::loadTexturesAndSounds()
{
	// load assets
	TextureManager::Instance()->loadTexture("./assets/background.jpg",
		"background",
		renderer);
	TextureManager::Instance()->loadTexture("./assets/cardBack_red5.png",
		"backCard",
		renderer);
	TextureManager::Instance()->loadTexture("./assets/start.png",
		"start_button",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/start-inactive.png",
		"start_inactive",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p1.png",
		"player_1",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p1-inactive.png",
		"player_1_inactive",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p2.png",
		"player_2",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p2-inactive.png",
		"player_2_inactive",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p3.png",
		"player_3",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/p3-inactive.png",
		"player_3_inactive",
		renderer);

	TextureManager::Instance()->loadTexture("./assets/c.png",
		"card_counter",
		renderer);

	SoundManager::Instance()->loadMusicAndSFX("./assets/start.wav", "start", 1);

	SoundManager::Instance()->loadMusicAndSFX("./assets/cool-jazz.mp3", "music", 1);

	SoundManager::Instance()->loadMusicAndSFX("./assets/card-deal1.ogg", "sfx1", 0);

	SoundManager::Instance()->loadMusicAndSFX("./assets/card-deal2.ogg", "sfx2", 0);

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