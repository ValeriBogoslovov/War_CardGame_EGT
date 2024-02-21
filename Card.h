#pragma once
#include <string>

class Card
{
public:
	Card(std::string face, std::string suit, std::string id, int power);
	std::string getFace()const;
	std::string getSuit()const;
	std::string getID()const;
	int getPower()const;
	~Card();
private:
	std::string face;
	std::string suit;
	std::string id;
	int power;
	static int destructorCount;
};

