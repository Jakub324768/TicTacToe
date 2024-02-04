#pragma once
#include "../GameStateMachine.h"
#include "../Button.h"

class MenuState : public State
{
	Button buttons[3]; // 0 - NoOnline, 1 - Online, 2 - Exit;
	sf::Font font;

public:
	MenuState(GameStateMachine& Machine);

	virtual void Update() override;
	virtual void Render() override;
};

