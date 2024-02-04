#include "NoOnlineState.h"

NoOnlineState::NoOnlineState(GameStateMachine& Machine) : State(Machine)
{
	game = new Game(window, this);
}

NoOnlineState::~NoOnlineState()
{
	delete game;
}

void NoOnlineState::Update()
{
	game->Update();
}

void NoOnlineState::Render()
{
	game->Render();
}

void NoOnlineState::Event(sf::Event& event)
{
	game->Event(event);
}
