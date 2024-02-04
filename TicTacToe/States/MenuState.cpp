#include "MenuState.h"
#include "NoOnlineState.h"
#include "OnlineMenuState.h"
#include <iostream>

MenuState::MenuState(GameStateMachine& Machine) : State(Machine)
{
	if (!font.loadFromFile("res/TBPROAR.TTF"))
	{
		std::cout << "Error font, Class:MenuState\n";
	}

	buttons[0] = Button("NoOnline", sf::Vector2f(150, 50), sf::Vector2f(225, 150), font, window);
	buttons[1] = Button("Online", sf::Vector2f(150, 50), sf::Vector2f(225, 250), font, window);
	buttons[2] = Button("Exit", sf::Vector2f(150, 50), sf::Vector2f(225, 350), font, window);
}

void MenuState::Update()
{
	for (int i = 0; i < 3; i++)
	{
		Button& buton = buttons[i];

		if (buton.IsPresed())
		{
			switch (i)
			{
			case 0: //NoOnline
				StateMachine.AddStateFirst(new NoOnlineState(StateMachine));
				break;
			case 1: //Online
				std::cout << "Button 2\n";
				break;
			case 2: //Exit
				StateMachine.ClearState();
				break;
			default:
				break;
			}
		}
	}
}

void MenuState::Render()
{
	for (auto b : buttons)
	{
		window.draw(b);
	}
}