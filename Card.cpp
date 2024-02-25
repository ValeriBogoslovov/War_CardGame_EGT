#include "Card.h"
#include <iostream>


Card::Card(std::string face, std::string suit, std::string id, int power)
    :face(face), suit(suit), id(id), power(power) {}

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

void Card::setBackCardXPos(int x)
{
    this->backCardXPos = x;
}

void Card::setBackCardYPos(int y)
{
    this->backCardYPos = y;
}

void Card::setFaceCardXPos(int x)
{
    this->faceCardXPos = x;
}

void Card::setFaceCardYPos(int y)
{
    this->faceCardYPos = y;
}

void Card::setCardAngle(double angle)
{
    this->angle = angle;
}

int Card::getCardWidth() const
{
    return this->cardWidth;
}

int Card::getCardHeight() const
{
    return this->cardHeight;
}

int Card::getBackCardXPos() const
{
    return this->backCardXPos;
}

int Card::getBackCardYPos() const
{
    return this->backCardYPos;
}

int Card::getFaceCardXPos() const
{
    return this->faceCardXPos;
}

int Card::getFaceCardYPos() const
{
    return this->faceCardYPos;
}

double Card::getCardAngle() const
{
    return this->angle;
}
