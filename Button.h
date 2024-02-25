#pragma once
#include <string>


class Button
{
public:
	Button(int xPos = 0, int yPos = 0, int width = 0, int height = 0, std::string id = "");

	void updateXPos(int x);
	void updateYPos(int y);
	void updateWidth(int width);
	void updateHeight(int height);
	void updateIsActive(bool isActive);
	void updateId(std::string id);

	int getXPos() const;
	int getYPos() const;
	int getWidth() const;
	int getHeight() const;
	bool getIsActive() const;
	std::string getId() const;
private:
	int buttonXPos, buttonYpos, buttonWidth, buttonHeight;
	bool isActive = true;
	std::string buttonId;
};

