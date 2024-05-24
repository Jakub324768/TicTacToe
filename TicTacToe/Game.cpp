#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& Window, State* State) : window(Window), state(State)
{
	bOnline = false;

	symbol = 'X';

	if (!font.loadFromFile("res/TBPROAR.TTF"))
	{
		std::cout << "Error font, Class:Game\n";
	}
	pointText.setFont(font);
	pointText.setFillColor(sf::Color::Black);
	pointText.setCharacterSize(25);
	pointText.setPosition(10, 5);

	quckButton = Button("Q", sf::Vector2f(40, 40), sf::Vector2f(555, 5), font, window);
}

Game::Game(bool isHost, sf::RenderWindow& Window, State* State) : bHost(isHost), window(Window), state(State)
{
	symbol = 'X';

	if (!font.loadFromFile("res/TBPROAR.TTF"))
	{
		std::cout << "Error font, Class:Game\n";
	}
	pointText.setFont(font);
	pointText.setFillColor(sf::Color::Black);
	pointText.setCharacterSize(25);
	pointText.setPosition(10, 5);

	quckButton = Button("Q", sf::Vector2f(40, 40), sf::Vector2f(555, 5), font, window);
    
	std::cout << "Listen" << std::endl;
	Listen();
}

Game::Game(bool isHost, sf::RenderWindow& Window, sf::IpAddress IpAddress, State* State) : bHost(isHost), window(Window), ipAddress(IpAddress), state(State)
{
	playrRound = 2;
	symbol = 'O';

	if (!font.loadFromFile("res/TBPROAR.TTF"))
	{
		std::cout << "Error font, Class:Game\n";
	}
	pointText.setFont(font);
	pointText.setFillColor(sf::Color::Black);
	pointText.setCharacterSize(25);
	pointText.setPosition(10, 5);

	quckButton = Button("Q", sf::Vector2f(40, 40), sf::Vector2f(555, 5), font, window);

	if (!Join())
	{
		state->SetRuning(false);
	}
}

void Game::Update()
{
	if (bOnline)
		UpdateOnline();
	else
		UpdateNoOnline();
}

void Game::UpdateNoOnline()
{
	if (quckButton.IsPresed())
	{
		state->SetRuning(false);
	}

	if (winPlayer == ' ')
	{
		if (FindWin('X'))
		{
			winPlayer = 'X';
			winClock.restart();
		}
		else if (FindWin('O'))
		{
			winPlayer = 'O';
			winClock.restart();
		}
	}
	else
	{
		if (winClock.getElapsedTime().asSeconds() >= 5)
		{
			if (winPlayer == 'X')
			{
				point1++;
			}
			else
			{
				point2++;
			}
			ClearBoard();
			winPlayer = ' ';
		}
	}
}

void Game::UpdateOnline()
{
	if (bHost)
	{
		if (quckButton.IsPresed())
		{
			state->SetRuning(false);
		}

		if (winPlayer == ' ')
		{
			if (FindWin('X'))
			{
				winPlayer = 'X';
				winClock.restart();
			}
			else if (FindWin('O'))
			{
				winPlayer = 'O';
				winClock.restart();
			}
		}
		else
		{
			if (winClock.getElapsedTime().asSeconds() >= 5)
			{
				if (winPlayer == 'X')
				{
					point1++;
				}
				else
				{
					point2++;
				}
				ClearBoard();
				winPlayer = ' ';
			}
		}
		Send();
	}
	else
	{
		if (quckButton.IsPresed())
		{
			state->SetRuning(false);
		}

		if (winPlayer == ' ')
		{
			if (FindWin('X'))
			{
				winPlayer = 'X';
				winClock.restart();
			}
			else if (FindWin('O'))
			{
				winPlayer = 'O';
				winClock.restart();
			}
		}
		else
		{
			if (winClock.getElapsedTime().asSeconds() >= 5)
			{
				if (winPlayer == 'X')
				{
					point1++;
				}
				else
				{
					point2++;
				}
				ClearBoard();
				winPlayer = ' ';
			}
		}
		Receive();
	}
}

void Game::Render()
{
	drawLattice();
	drawPoint();
	drawCrossAndCircle();
	window.draw(quckButton);

	if (winPlayer != ' ')
	{
		//Linia
		/*sf::Vertex vertex[2] =
		{
			sf::Vertex(sf::Vector2f((winPosition[0].y) * 200 + 100, (winPosition[0].x) * 183 + 141),sf::Color::Red),
			sf::Vertex(sf::Vector2f((winPosition[1].y) * 200 + 100, (winPosition[1].x) * 183 + 141),sf::Color::Red)
		};
		window.draw(vertex, 2, sf::PrimitiveType::Lines);*/
		//GrubaLinia
		sf::Vertex vertex[4] =
		{
			sf::Vertex(sf::Vector2f((winPosition[0].y) * 200 + 98, (winPosition[0].x) * 183 + 139),sf::Color::Red),
			sf::Vertex(sf::Vector2f((winPosition[0].y) * 200 + 102, (winPosition[0].x) * 183 + 143),sf::Color::Red),
			sf::Vertex(sf::Vector2f((winPosition[1].y) * 200 + 102, (winPosition[1].x) * 183 + 143),sf::Color::Red),
			sf::Vertex(sf::Vector2f((winPosition[1].y) * 200 + 98, (winPosition[1].x) * 183 + 139),sf::Color::Red)
		};
		window.draw(vertex, 4, sf::PrimitiveType::Quads);
		
	}

	if (bHost)
	{
		sf::Text text(sf::IpAddress::getLocalAddress().toString(), font);
		text.setPosition(300, 5);
		text.setFillColor(sf::Color::Black);
		window.draw(text);
	}
}

void Game::Event(sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		if (event.mouseButton.y > 50)
		{
			int i = (event.mouseButton.y - 50) / 183;
			int j = (event.mouseButton.x) / 200;

			if (board[i][j] == ' ')
			{
				board[i][j] = playrRound++ % 2 ? 'X' : 'O';
				if (playrRound == 9)
					ClearBoard;
			}
		}
	}
}

//Draw

void Game::drawCross(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	crossLine.setPosition(position);
	crossLine.setFillColor(color);
	crossLine.setSize(sf::Vector2f(size.x / 0.7071067811865475f, size.y));
	crossLine.setOrigin((size.x / 0.7071067811865475f) / 2, size.y / 2);
	crossLine.setRotation(45);
	window.draw(crossLine);
	crossLine.setRotation(135);
	window.draw(crossLine);
}

void Game::drawCircle(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	circle.setPosition(position);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOutlineColor(color);
	circle.setOutlineThickness(size.y);
	circle.setRadius(size.x);
	circle.setOrigin(size.x, size.x);
	window.draw(circle);
}

void Game::drawLattice()
{
	sf::RectangleShape shape(sf::Vector2f(600,550));
	shape.setPosition(0, 50);
	shape.setFillColor(sf::Color(192, 192, 192));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
	window.draw(shape);

	for (int i = 1; i <= 2; i++)
	{
		sf::Vertex vertex[2] =
		{
			sf::Vertex(sf::Vector2f(10, i * 183 + 50),sf::Color::Black),
			sf::Vertex(sf::Vector2f(590, i * 183 + 50),sf::Color::Black)
		};
		window.draw(vertex, 2, sf::PrimitiveType::Lines);
	}

	for (int i = 1; i <= 2; i++)
	{
		sf::Vertex vertex[2] =
		{
			sf::Vertex(sf::Vector2f(i * 200, 60),sf::Color::Black),
			sf::Vertex(sf::Vector2f(i * 200, 590),sf::Color::Black)
		};
		window.draw(vertex, 2, sf::PrimitiveType::Lines);
	}
}

void Game::drawPoint()
{
	pointText.setString("Player1: " + std::to_string(point1) + " Player2: " + std::to_string(point2));
	window.draw(pointText);

}

void Game::drawCrossAndCircle()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == 'X')
			{
				drawCross(sf::Vector2f(j * 200 + 100, (i * 183 + 91.5) + 50), sf::Vector2f(160, 3), sf::Color::Black);
			}
			else if (board[i][j] == 'O')
			{
				drawCircle(sf::Vector2f(j * 200 + 100, (i * 183 + 91.5) + 50), sf::Vector2f(80, 3), sf::Color::Black);
			}
		}
	}
}

//EndDraw

bool Game::FindWin(char player)
{
	for (int i = 0; i < 3; i++)
	{
		winPosition[0] = sf::Vector2i(i, 0);
		for (int j = 0; j < 3; j++)
		{
			
			if (board[i][j] == player)
			{
				if (j == 2)
				{
					winPosition[1] = sf::Vector2i(i, 2);
					return true;
				}
			}
			else
			{
				break;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		winPosition[0] = sf::Vector2i(0, i);
		for (int j = 0; j < 3; j++)
		{
			if (board[j][i] == player)
			{
				if (j == 2)
				{
					winPosition[1] = sf::Vector2i(j, i);
					return true;
				}
			}
			else
			{
				break;
			}
		}
	}

	if (board[1][1] == player)
	{
		if (board[0][0] == player && board[2][2] == player)
		{
			winPosition[0] = sf::Vector2i(0, 0);
			winPosition[1] = sf::Vector2i(2, 2);
			return true;
		}
		if (board[0][2] == player && board[2][0] == player)
		{
			winPosition[0] = sf::Vector2i(0, 2);
			winPosition[1] = sf::Vector2i(2, 0);
			return true;
		}
	}

	return false;
}

void Game::ClearBoard()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = ' ';
		}
	}
}

//Online

bool Game::Listen()
{
	if (listener.listen(PORT) != sf::Socket::Done)
	{
		std::cout << "Error listener port: " << PORT << "\n";
		return false;
	}
	if (listener.accept(socet) != sf::Socket::Done)
	{
		std::cout << "Error accept port: " << PORT << "\n";
		return false;
	}
	return true;
}

bool Game::Join()
{
	if (socet.connect(ipAddress, PORT) != sf::Socket::Done)
	{
		std::cout << "Error connect to host.\n";
		return false;
	}
	return true;
}

void Game::Receive()
{
	sf::Packet packet;

	socet.receive(packet);

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			//char* tym;
			//packet >> tym; 
			//board[i][j] = *tym;
			sf::Int8 tym;
			packet >> tym;
			board[i][j] = tym;
		}
			

	packet >> point1 >> point2 >> playrRound;
}

void Game::Send()
{
	sf::Packet packet;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			packet << board[i][j];

	packet << point1 << point2 << playrRound;

	socet.send(packet);
}

//EndInline