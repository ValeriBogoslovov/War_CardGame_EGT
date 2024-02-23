#include "Player.h"


void Player::addCard(Card c)
{
    playerDeck.push(c);
}

void Player::setPlayerID(int id)
{
    this->playerID = id;
}

void Player::updateAtWar(bool isAtWar)
{
    this->isAtWar = isAtWar;
}

void Player::setCardAngle(double angle)
{
    this->playerCardAngle = angle;
}

void Player::setPlayerBackCardPosX(int posX)
{
    this->playerBackCardPosX = posX;
}

void Player::setPlayerBackCardPosY(int posY)
{
    this->playerBackCardPosY = posY;
}

void Player::setPlayerFaceUpCardPosX(int posX)
{
    this->playerFaceCardPosX = posX;
}

void Player::setPlayerFaceUpCardPosY(int posY)
{
    this->playerFaceCardPosY = posY;
}

std::queue<Card> Player::getPlayerDeck() const
{
    return this->playerDeck;
}

std::queue<Card>& Player::updatePlayerDeck()
{
    return this->playerDeck;
}

int Player::getPlayerID() const
{
    return this->playerID;
}

bool Player::getAtWar() const
{
    return this->isAtWar;
}

double Player::getCardAngle() const
{
    return this->playerCardAngle;
}

int Player::getPlayerBackCardPosX() const
{
    return this->playerBackCardPosX;
}

int Player::getPlayerBackCardPosY() const
{
    return this->playerBackCardPosY;
}

int Player::getPlayerFaceUpCardPosX() const
{
    return this->playerFaceCardPosX;
}

int Player::getPlayerFaceUpCardPosY() const
{
    return this->playerFaceCardPosY;
}
