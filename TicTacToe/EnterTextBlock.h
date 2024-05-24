#pragma once
#include"Button.h"
#include<iostream>

class EnterTextBlock : public Button
{
	bool bTextEntered = false;
	std::string enterText = "";

	sf::Text EnterText;

public:
	EnterTextBlock();
	EnterTextBlock(std::string text, sf::Vector2f size, sf::Vector2f position, sf::Font& font, sf::RenderWindow& window);

	std::string GetEnterText() { return enterText; };

	void Event(sf::Event& event);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

