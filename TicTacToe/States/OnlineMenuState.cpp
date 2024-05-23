#include "OnlineMenuState.h"
#include <iostream>

OnlineMenuState::OnlineMenuState(GameStateMachine& Machine) : State(Machine)
{
	if (!font.loadFromFile("res/TBPROAR.TTF"))
	{
		std::cout << "Error font, Class:OnlineMenuState\n";
	}

	HostButton = Button("Host Game", sf::Vector2f(200,50), sf::Vector2f(200, 150), font, window);
	JoinButton = Button("Join Game", sf::Vector2f(200, 50), sf::Vector2f(200, 250), font, window);
	BackButton = Button("Back", sf::Vector2f(200, 50), sf::Vector2f(200, 450), font, window);
}

OnlineMenuState::~OnlineMenuState()
{

}

void OnlineMenuState::Update()
{
	if (BackButton.IsPresed())
	{
		isRuning = false;
	}
}

void OnlineMenuState::Render()
{
	window.draw(HostButton);
	window.draw(JoinButton);
	window.draw(BackButton);
}

void OnlineMenuState::Event(sf::Event& event)
{

}