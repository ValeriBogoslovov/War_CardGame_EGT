#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Card.h"
#include "Button.h"
#include <queue>
#include <stack>

class Player
{
public:
	Player(int id = -1, int backCardX = 0, int backCardY = 0, int faceCardX = 0, 
		int faceCardY = 0, double cardAngle = 0.0, int buttonX = 0, int buttonY = 0,
		int buttonWidth = 0, int buttonHeight = 0, std::string buttonId = "");
	//setters, updaters
	void setPlayerID(int id);
	void updateAtWar(bool isAtWar);
	bool cardCounter(SDL_Renderer* ren);
	void updateCardText(int x, int y, int w, int h);
	void updateCardCounter(int x, int y, int w, int h);
	std::queue<Card>& updatePlayerDeck();
	std::stack<Card>& updatePlayerDiscardedDeck();
	Card& setPlayerCard();
	Button& updatePlayerButton();
	// getters
	std::queue<Card> getPlayerDeck() const;
	std::stack<Card> getPlayerDiscardedDeck() const;
	int getPlayerID() const;
	bool getAtWar()const;
	Card getPlayerCard();
	Button getPlayerButton();
	SDL_Rect getCardText() const;
	SDL_Rect getCardCounter() const;
	bool hasWon = false;
	enum PlayerState {
		PlayerReady,
		PlayerCardOpen,
		WonBattle,
		Inactive,
		Finished
	};
	PlayerState playerState;

private:
	std::queue<Card> playerDeck;
	std::stack<Card> playerDiscardedCards;
	int playerID;
	bool isAtWar = false;
	Card playerCard;
	Button playerButton;

	// font
	TTF_Font* font;
	SDL_Texture* cardsText;
	SDL_Texture* cardsCount;
	SDL_Rect cardsTextDestRect;
	SDL_Rect cardsCountDestRect;
};

