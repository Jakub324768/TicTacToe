#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{

	sf::RenderWindow* _window;

	bool presed = false;

protected:
    sf::Text buttonText;
	sf::RectangleShape shape;

public:
	Button();
	Button(std::string text, sf::Vector2f size, sf::Vector2f position, sf::Font& font, sf::RenderWindow& window);

	const bool IsPresed();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

