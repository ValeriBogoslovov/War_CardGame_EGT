#include "Player.h"
#include <iostream>

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

bool Player::cardCounter(SDL_Renderer* ren)
{
    if (TTF_Init() == -1) // return error
    {
        std::cout << SDL_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont("./assets/segoepr.ttf", 30);

    SDL_Surface* tempSurfaceText = NULL;
    tempSurfaceText = TTF_RenderText_Blended(font, "Cards: ", { 255,255,255,255 });
    cardsText = SDL_CreateTextureFromSurface(ren, tempSurfaceText);

    tempSurfaceText = TTF_RenderText_Blended(font, std::to_string(playerDeck.size()).data(), {255,255,255,255});
    cardsCount = SDL_CreateTextureFromSurface(ren, tempSurfaceText);

    int tw, th;
    SDL_QueryTexture(cardsText, 0, 0, &tw, &th);
    SDL_QueryTexture(cardsCount, 0, 0, &tw, &th);
    //cardsTextDestRect = { 10,15,100,45 };
    //cardsCountDestRect = { 130,12,35,45 };

    SDL_RenderCopy(ren, cardsText, NULL, &this->cardsTextDestRect);
    SDL_RenderCopy(ren, cardsCount, NULL, &this->cardsCountDestRect);

    SDL_FreeSurface(tempSurfaceText);
    return true;
}

void Player::updateCardText(int x, int y, int w, int h)
{
    this->cardsTextDestRect.x = x;
    this->cardsTextDestRect.y = y;
    this->cardsTextDestRect.w = w;
    this->cardsTextDestRect.h = h;
}

void Player::updateCardCounter(int x, int y, int w, int h)
{
    this->cardsCountDestRect.x = x;
    this->cardsCountDestRect.y = y;
    this->cardsCountDestRect.w = w;
    this->cardsCountDestRect.h = h;
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

SDL_Rect Player::getCardText() const
{
    return this->cardsTextDestRect;
}

SDL_Rect Player::getCardCounter() const
{
    return this->cardsCountDestRect;
}
