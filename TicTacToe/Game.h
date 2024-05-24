#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "Button.h"
#include "GameStateMachine.h"

class Game
{
	State* state;

	bool bHost = false;
	bool bOnline = true;

	char board[3][3] = { {' ',' ',' '},{' ',' ',' '} ,{' ',' ',' '}};
	int point1 = 0, point2 = 0;
	int playrRound = 1;
	char symbol = ' ';
	char winPlayer = ' ';
	sf::Vector2i winPosition[2];

	sf::Clock winClock;
	
	sf::RectangleShape crossLine;
	sf::CircleShape circle;
	
	sf::RenderWindow& window;

	sf::TcpListener listener;
	sf::TcpSocket socet;
	const unsigned short PORT = 55999;
	sf::IpAddress ipAddress = sf::IpAddress::Any;

	sf::Font font;
	sf::Text pointText;

	Button quckButton;

    void drawCross(sf::Vector2f position,sf::Vector2f size,sf::Color color);
	void drawCircle(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	void drawLattice();
	void drawPoint();
	void drawCrossAndCircle();

	void Receive();
	void Send();

	void UpdateOnline();
	void UpdateNoOnline();
public:
	Game(sf::RenderWindow& Window, State* State);
	Game(bool isHost, sf::RenderWindow& Window, State* State);
	Game(bool isHost, sf::RenderWindow& Window, sf::IpAddress IpAddress, State* State);

	void Update();
	void Render();
	void Event(sf::Event& event);

	bool FindWin(char player);
	void ClearBoard();

	bool Listen();
	bool Join();
};

