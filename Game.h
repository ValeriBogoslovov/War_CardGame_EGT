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

	// initializes 3 players and sets Id, called in Init()
	void createPlayers();
	// populate players's queue of Card from DeckOfCards, called in Init()
	void dealCardsToPlayers();

	// draw players deck
	void drawPlayersDeck(bool hasGameStarted);
	// draw players cards face up
	void drawPlayersCardsUp(bool p1Pressed, bool p2Pressed, bool p3Pressed);

	bool isWar = false;
	// draw card from rest of deck
	Card pickCard();
	// getter and setter for vector of Player
	std::vector<Player> getPlayers()const;
	std::vector<Player>& updatePlayers();

	// getter and setter for queue of discarded Card
	std::queue<Card> getDiscardedCards()const;
	std::queue<Card>& updateDiscardedCards();


private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool running;
	// vector containing the 3 players
	std::vector<Player> players;
	// deck object containing shuffled queue of cards
	DeckOfCards deck;
	// queue of Card will be used when players put cards on table
	std::queue<Card> discardedCards;
	// empty Card used for xPos and yPos and width and height
	Card emptyCard;
	// load all images func, called in Init()
	void loadTextures();
	// background width and height, initialized in Init()
	int backgroundWidth;
	int backgroundHeight;

	// start button position, width and height
	int startXPos = 0;
	const int startYPos = 50;
	const int startWidth = 100;
	const int startHeight = 50;
	// players default deck position
	const int player1DeckPosX = 100;
	const int player1DeckPosY = 250;

	const int player2DeckPosX = 600;
	const int player2DeckPosY = 500;

	const int player3DeckPosX = 1000;
	const int player3DeckPosY = 250;

	// players default card face up position
	const int player1CardPosX = 450;
	const int player1CardPosY = 250;

	const int player2CardPosX = 600;
	const int player2CardPosY = 250;

	const int player3CardPosX = 750;
	const int player3CardPosY = 250;

	// mouse position
	int mouseXUp, mouseXDown, mouseYUp, mouseYDown;

	// bool if player deck is pressed
	bool isPlayerOneDeckPressed = false;
	bool isPlayerTwoDeckPressed = false;
	bool isPlayerThreeDeckPressed = false;

	// bool if playerIsPlaying
	bool isPlayerOnePlaying = false;
	bool isPlayerTwoPlaying = false;
	bool isPlayerThreePlaying = false;

	// bool if game has started
	bool hasGameStarted = false;

	// counter for how many players have put their cards on desk
	int counter = 0;
};