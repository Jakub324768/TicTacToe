#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(sf::RenderWindow& a_window) : window(a_window)
{

}

GameStateMachine::~GameStateMachine()
{
	ClearState();
}

void GameStateMachine::Update()
{
	if (!s_states.empty())
	{
		if (!s_states.top()->IsRuning())
		{
			delete s_states.top();
			s_states.pop();
		}
		else
			s_states.top()->Update();
	}
	else
	{
		window.close();
	}
}

void GameStateMachine::Render()
{
	if (!s_states.empty())
	{
		s_states.top()->Render();
	}
}

void GameStateMachine::Event(sf::Event& event)
{
	if (!s_states.empty())
	{
		s_states.top()->Event(event);
	}
}


void GameStateMachine::AddStateFirst(State* state)
{
	s_states.push(state);
}

void GameStateMachine::AddStateEnd(State* state)
{
	if (s_states.empty())
	{
		s_states.push(state);
	}
	else
	{
		State* tym = s_states.top();
		s_states.pop();
		AddStateEnd(state);
		s_states.push(tym);
	}
}

void GameStateMachine::ClearState()
{
	while (!s_states.empty())
	{
		delete s_states.top();
		s_states.pop();
	}
}

State::State(GameStateMachine& Machine) : StateMachine(Machine), window(Machine.window)
{

}

State::~State()
{

}

void State::Event(sf::Event& event)
{

}
