#include "OnlineState.h"

OnlineState::OnlineState(GameStateMachine& Machine) : State(Machine)
{
	game = new Game(true, window, this);
}

OnlineState::OnlineState(GameStateMachine& Machine, std::string Adres) : State(Machine)
{
	game = new Game(false, window, Adres, this);
}

OnlineState::~OnlineState()
{
	delete game;
}

void OnlineState::Update()
{
	game->Update();
}

void OnlineState::Render()
{
	game->Render();
}

void OnlineState::Event(sf::Event& event)
{
	game->Event(event);
}