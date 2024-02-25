#include "Player.h"

Player::Player(int id, int backCardX, int backCardY, int faceCardX,
    int faceCardY, double cardAngle, int buttonX, int buttonY, int buttonWidth, int buttonHeight, std::string buttonId)
    : playerID(id), playerButton(buttonX, buttonY, buttonWidth, buttonHeight, buttonId), 
    playerCard(backCardX, backCardY, faceCardX, faceCardY, cardAngle) {}

void Player::setPlayerID(int id)
{
    this->playerID = id;
}

void Player::updateAtWar(bool isAtWar)
{
    this->isAtWar = isAtWar;
}

std::queue<Card> Player::getPlayerDeck() const
{
    return this->playerDeck;
}

std::stack<Card> Player::getPlayerDiscardedDeck() const
{
    return this->playerDiscardedCards;
}

std::queue<Card>& Player::updatePlayerDeck()
{
    return this->playerDeck;
}

std::stack<Card>& Player::updatePlayerDiscardedDeck()
{
    return this->playerDiscardedCards;
}

Card& Player::setPlayerCard()
{
    return this->playerCard;
}

Button& Player::updatePlayerButton()
{
    return this->playerButton;
}

int Player::getPlayerID() const
{
    return this->playerID;
}

bool Player::getAtWar() const
{
    return this->isAtWar;
}

Card Player::getPlayerCard()
{
    return this->playerCard;
}

Button Player::getPlayerButton()
{
    return this->playerButton;
}
