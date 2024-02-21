#include "Player.h"


void Player::addCard(Card c)
{
    playerDeck.push(c);
}

void Player::setPlayerID(int id)
{
    this->playerID = id;
}

std::queue<Card>& Player::getPlayerDeck()
{
    return this->playerDeck;
}

int Player::getPlayerID() const
{
    return this->playerID;
}
