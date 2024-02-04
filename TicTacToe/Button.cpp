#include "Button.h"
#include <iostream>

Button::Button() : _window(nullptr)
{

}

Button::Button(std::string text, sf::Vector2f size, sf::Vector2f position, sf::Font& font, sf::RenderWindow& window) : _window(&window)
{
	shape.setFillColor(sf::Color(192,192,192));
	shape.setOutlineColor(sf::Color::Black);
	shape.setPosition(position);
	shape.setSize(size);
	shape.setOutlineThickness(1);

	buttonText.setFillColor(sf::Color::Black);
	buttonText.setString(text);
	buttonText.setFont(font);
	buttonText.setPosition(position);
	
	if (buttonText.getGlobalBounds().width < size.x)
	{
		buttonText.setPosition(position.x + (size.x - buttonText.getGlobalBounds().width) / 2, position.y);
	}
}

const bool Button::IsPresed()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !presed)
	{
		presed = true; 
		if (sf::Mouse::getPosition(*_window).x >= shape.getPosition().x && sf::Mouse::getPosition(*_window).x <= shape.getPosition().x + shape.getSize().x && sf::Mouse::getPosition(*_window).y >= shape.getPosition().y && sf::Mouse::getPosition(*_window).y <= shape.getPosition().y + shape.getSize().y)
		{
			return true;
		}
		else
			return false;
	}
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		presed = false;
	
	return false;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(buttonText, states);
}