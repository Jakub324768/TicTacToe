#pragma once
#include "../GameStateMachine.h"
#include "../Game.h"

class NoOnlineState : public State
{
	Game* game;
public:
	NoOnlineState(GameStateMachine& Machine);
	~NoOnlineState();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Event(sf::Event& event) override;
};

