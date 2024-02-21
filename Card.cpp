#include "Card.h"
#include <iostream>

int Card::destructorCount = 0;

Card::Card(std::string face, std::string suit, std::string id, int power)
    :face(face), suit(suit), id(id), power(power){}

std::string Card::getFace() const
{
    return this->face;
}

std::string Card::getSuit() const
{
    return this->suit;
}

std::string Card::getID() const
{
    return this->id;
}

int Card::getPower() const
{
    return this->power;
}

Card::~Card()
{
    //++destructorCount;
    //std::cout << "Card Destructor called: " << destructorCount << " times.\n";
}
