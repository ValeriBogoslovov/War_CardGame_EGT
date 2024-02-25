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
