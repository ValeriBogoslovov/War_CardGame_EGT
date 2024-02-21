#include "Player.h"

void Player::addCard(Card c)
{
    playerDeck.push(c);
}

void Player::setPlayerID(std::string id)
{
    this->playerID = id;
}

std::queue<Card>& Player::getPlayerDeck()
{
    return this->playerDeck;
}

//std::queue<Card>& Player::getDicardedDeck()
//{
//    return this->discardedCards;
//}

std::string Player::getPlayerID() const
{
    return this->playerID;
}
