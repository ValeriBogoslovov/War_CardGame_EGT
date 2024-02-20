#pragma once
#include <string>

class Card
{
public:
	Card(std::string face, std::string suit, std::string id);
	std::string getFace()const;
	std::string getSuit()const;
	std::string getID()const;
	~Card();
private:
	std::string face;
	std::string suit;
	std::string id;
};

