#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Player.h"
#include "DeckOfCards.h"
#include "SoundManager.h"
//#include "Statistics.h"

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

	// initializes 3 players and sets Id, called in Init()
	void createPlayers();
	// populate players's queue of Card from DeckOfCards, called in Init()
	void dealCardsToPlayers();
	// draw players deck
	void drawPlayersDeck();
	// check if all active players have placed cards
	bool checkIfActivePlayersPlacedCards();
	// compare players cards powers
	void comparePlayersCardsPower();
	// update players decks based on winner of war
	void updatePlayersDecks();
	// display player that wins
	bool showWinnerOfBattle(SDL_Renderer* ren);
	// draw card from rest of deck
	Card pickCard();
	// getter and setter for vector of Player
	const std::vector<Player>& getPlayers();
	std::vector<Player>& updatePlayers();

	// getter and setter for vector of discarded Card
	const std::vector<Card>& getDiscardedCards();
	std::vector<Card>& updateDiscardedCards();


private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;
	// vector containing the 3 players
	std::vector<Player> players;
	// deck object containing shuffled queue of cards
	DeckOfCards deck;
	// vector of Card will be used when players put cards on table
	std::vector<Card> discardedCards;
	// empty Card used for xPos and yPos and width and height
	Card emptyCard;
	// load all images func, called in Init()
	void loadTexturesAndSounds();
	// background width and height, initialized in Init()
	int backgroundWidth;
	int backgroundHeight;

	Button gameButton;
	TTF_Font* font;
	SDL_Texture* playerNameText;
	SDL_Texture* playerPointsText;
	SDL_Rect playerNameTextDestRect;
	SDL_Rect playerPointsTextDestRect;
	// mouse position
	int mouseXUp, mouseXDown, mouseYUp, mouseYDown;

	enum GameState {
		Initial,
		NormalPlay,
		CardsDelay,
		Statistics
	};
	GameState state;
};

