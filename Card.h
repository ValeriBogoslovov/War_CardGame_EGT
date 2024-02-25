#pragma once

#include <string>

class Card
{
public:
	Card(std::string face = "empty", std::string suit = "empty", std::string id = "backCard", int power = 0);
	std::string getFace()const;
	std::string getSuit()const;
	std::string getID()const;
	int getPower()const;

	int getCardWidth();
	int getCardHeight();
private:
	std::string face;
	std::string suit;
	std::string id;
	int power;

	int cardWidth = 100;
	int cardHeight = 150;
};

