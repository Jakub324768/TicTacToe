#pragma once
#include "../GameStateMachine.h"
#include "../EnterTextBlock.h"

class OnlineMenuState : public State
{
	Button HostButton, JoinButton, BackButton;
	sf::Font font;
	EnterTextBlock AdresEnterTextBlock;

public:

	OnlineMenuState(GameStateMachine& Machine);
	~OnlineMenuState();

	virtual void Update() override;
	virtual void Render() override;
	virtual void Event(sf::Event& event) override;
};

