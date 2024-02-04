#include "App.h"
#include "States/MenuState.h"

App::App()
{
	InitWindow();

	StateMachine = new GameStateMachine(window);
	StateMachine->AddStateFirst(new MenuState(*StateMachine));
}

App::~App()
{
	delete StateMachine;
}

int App::RUN()
{
	while (window.isOpen())
	{
		Update();

		Render();

		Events();
	}

	return 0;
}

void App::Update()
{
	StateMachine->Update();
}

void App::Render()
{
	window.clear(sf::Color::White);

	StateMachine->Render();

	window.display();
}

void App::Events()
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
		StateMachine->Event(event);
	}
}

void App::InitWindow()
{
    WindowHeigh = 600; WindowWidth = 600;
	
	window.create(sf::VideoMode(WindowWidth, WindowHeigh), "TicTacToe");
	window.setFramerateLimit(200);
}
