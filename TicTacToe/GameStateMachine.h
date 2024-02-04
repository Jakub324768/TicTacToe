#pragma once
#include <stack>
#include<SFML/Graphics.hpp>

class State;

class GameStateMachine
{
	std::stack<State*> s_states;

public:
	GameStateMachine(sf::RenderWindow& a_window);
	~GameStateMachine();

	void Update();
	void Render();
	void Event(sf::Event& event);

	void AddStateFirst(State* state); // Top
	void AddStateEnd(State* state);
	void ClearState();

	sf::RenderWindow& window;
};

class State
{
protected:
	bool isRuning = true;

	GameStateMachine& StateMachine;

	sf::RenderWindow& window;

public:
	State(GameStateMachine& Machine);
	virtual ~State();
	const bool IsRuning() { return isRuning; };
	void SetRuning(bool runing) { isRuning = runing; };

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Event(sf::Event& event);
};