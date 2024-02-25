#include "Button.h"

Button::Button(int xPos, int yPos, int width, int height, std::string id)
    : buttonXPos(xPos), buttonYpos(yPos), buttonWidth(width), buttonHeight(height), buttonId(id){}

void Button::updateXPos(int x)
{
    this->buttonXPos = x;
}

void Button::updateYPos(int y)
{
    this->buttonYpos = y;
}

void Button::updateWidth(int width)
{
    this->buttonWidth = width;
}

void Button::updateHeight(int height)
{
    this->buttonHeight = height;
}

void Button::updateIsActive(bool isActive)
{
    this->isActive = isActive;
}

void Button::updateId(std::string id)
{
    this->buttonId = id;
}

int Button::getXPos() const
{
    return this->buttonXPos;
}

int Button::getYPos() const
{
    return this->buttonYpos;
}

int Button::getWidth() const
{
    return this->buttonWidth;
}

int Button::getHeight() const
{
    return this->buttonHeight;
}

bool Button::getIsActive() const
{
    return this->isActive;
}

std::string Button::getId() const
{
    return this->buttonId;
}
