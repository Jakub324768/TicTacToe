#pragma once
#include "../GameStateMachine.h"
#include "../Game.h"

class OnlineState : public State
{
	Game* game;
public:
	OnlineState(GameStateMachine& Machine);
	OnlineState(GameStateMachine& Machine, std::string Adres);
	~OnlineState();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Event(sf::Event& event) override;
};

