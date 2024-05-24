#include "OnlineMenuState.h"
#include "OnlineState.h"
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
	AdresEnterTextBlock = EnterTextBlock("Adres", sf::Vector2f(300, 50), sf::Vector2f(150, 350), font, window);
}

OnlineMenuState::~OnlineMenuState()
{
}

void OnlineMenuState::Update()
{
	
}

void OnlineMenuState::Render()
{
	window.draw(HostButton);
	window.draw(JoinButton);
	window.draw(BackButton);
	window.draw(AdresEnterTextBlock);

	sf::Text text(sf::IpAddress::getLocalAddress().toString(), font);
	text.setPosition(250, 5);
	text.setFillColor(sf::Color::Black);
	window.draw(text);
}

void OnlineMenuState::Event(sf::Event& event)
{
	AdresEnterTextBlock.Event(event);

	if (BackButton.IsPresed())
	{
		isRuning = false;
	}
	else if (HostButton.IsPresed())
	{
		StateMachine.AddStateFirst(new OnlineState(StateMachine));
	}
	else if (JoinButton.IsPresed())
	{
		StateMachine.AddStateFirst(new OnlineState(StateMachine, AdresEnterTextBlock.GetEnterText()));
	}
}