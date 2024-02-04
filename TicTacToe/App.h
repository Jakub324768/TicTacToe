#pragma once
#include<SFML/Graphics.hpp>
#include"GameStateMachine.h"

class App
{
	int WindowHeigh, WindowWidth;
	sf::RenderWindow window;
	void InitWindow();

	void Update();
	void Render();

	void Events();
	sf::Event event;

	GameStateMachine* StateMachine;
public:
	App();
	~App();

	int RUN();
};

