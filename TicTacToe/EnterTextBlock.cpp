#include "EnterTextBlock.h"

EnterTextBlock::EnterTextBlock() : Button()
{

}

EnterTextBlock::EnterTextBlock(std::string text, sf::Vector2f size, sf::Vector2f position, sf::Font& font, sf::RenderWindow& window) : Button(text,size,position,font,window)
{
	EnterText.setFont(font);
	EnterText.setPosition(position);
	EnterText.setString(enterText);
	EnterText.setFillColor(sf::Color::Black);
}

void EnterTextBlock::Event(sf::Event& event)
{
	if (Button::IsPresed())
	{
		if (bTextEntered)
			bTextEntered = false;
		else
			bTextEntered = true;
	}
	if (bTextEntered)
	{
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < 128)
			{
				if (event.text.unicode == 8) // Backspace
				{
					if (enterText != "")
						enterText.pop_back();
					EnterText.setString(enterText);
				}
				else if (event.text.unicode == 13) // Enter
				{
					bTextEntered = false;
				}
				else
				{
					enterText += static_cast<char>(event.text.unicode);
					EnterText.setString(enterText);
				}
			}
		}
	}
}

void EnterTextBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(shape, states);
	if (enterText == "" && !bTextEntered)
	{
		target.draw(buttonText, states);
	}
	else
	{
		target.draw(EnterText, states);
	}
}
