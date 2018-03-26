#include "GameWindow.h"

GameWindow::GameWindow()
	:mySFMLWindow(sf::VideoMode(1024, 768), "SFML works!")
{
	
}

bool GameWindow::PollEvent(Event& outEvent)
{
	sf::Event event;
	mySFMLWindow.pollEvent(event);

	if (event.type == sf::Event::Closed)
	{
		outEvent = CLOSE;
		return true;
	}

	return false;
}

sf::RenderWindow* GameWindow::GetRenderWindow()
{
	return &mySFMLWindow;
}