#include "Card.h"
#include <iostream>

Card::Card(std::string face, std::string suit, std::string id)
    :face(face), suit(suit), id(id){}

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

Card::~Card()
{
    std::cout << "Card Destructor called.\n\n";
}
