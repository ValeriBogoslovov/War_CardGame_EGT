#pragma once

#include <string>

class Card
{
public:
	Card(int backCardX = 0, int backCardY = 0, int faceCardX = 0, int faceCardY = 0, double angle = 0.0,
		std::string face = "empty", std::string suit = "empty", std::string id = "backCard", int power = 0);
	std::string getFace()const;
	std::string getSuit()const;
	std::string getID()const;
	int getPower()const;
	void setBackCardXPos(int x);
	void setBackCardYPos(int y);
	void setFaceCardXPos(int x);
	void setFaceCardYPos(int y);
	void setCardAngle(double angle);

	int getCardWidth() const;
	int getCardHeight() const;
	int getBackCardXPos() const;
	int getBackCardYPos() const;
	int getFaceCardXPos() const;
	int getFaceCardYPos() const;
	double getCardAngle() const;
private:
	std::string face;
	std::string suit;
	std::string id;
	double angle;
	int power;
	int backCardXPos, backCardYPos, faceCardXPos, faceCardYPos;
	int cardWidth = 100;
	int cardHeight = 150;
};

