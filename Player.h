#pragma once
#include "Card.h"
#include <queue>

class Player
{
public:
	//setters, updaters
	void addCard(Card c);
	void setPlayerID(int id);
	void updateAtWar(bool isAtWar);
	void setCardAngle(double angle);
	void setPlayerBackCardPosX(int posX);
	void setPlayerBackCardPosY(int posY);
	void setPlayerFaceUpCardPosX(int posX);
	void setPlayerFaceUpCardPosY(int posY);
	std::queue<Card>& updatePlayerDeck();

	// getters
	std::queue<Card> getPlayerDeck() const;
	int getPlayerID() const;
	bool getAtWar()const;
	double getCardAngle()const;
	int getPlayerBackCardPosX()const;
	int getPlayerBackCardPosY()const;
	int getPlayerFaceUpCardPosX()const;
	int getPlayerFaceUpCardPosY()const;

	bool playerReady = false;
	bool playerShowCard = false;
	bool playerShowWarCard = false;
	bool playerAtWar = false;
	bool playerInactive = false;
	bool playerWonBattle = false;
	bool playerLostBattle = false;

	//enum PlayerState {
	//	PlayerReady,
	//	PlayerCardOpen,
	//	PlayerAtWar,
	//	Inactive,
	//	Finished
	//};
	//PlayerState playerState;
	
private:
	std::queue<Card> playerDeck;
	int playerID;
	double playerCardAngle;
	bool isAtWar = false;

	// player back and face up card position x and y
	int playerBackCardPosX;
	int playerBackCardPosY;
	int playerFaceCardPosX;
	int playerFaceCardPosY;

};

