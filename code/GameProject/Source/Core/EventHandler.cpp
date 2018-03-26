#include "EventHandler.h"
#include "..\Game\Game.h"
#include "GameWindow.h"

void EventHandler::Init()
{
}

void EventHandler::HandleEvents()
{
	GameWindow::Event event;
	while (Game::GetInstance()->GetGameWindow()->PollEvent(event))
	{
		if (event == GameWindow::CLOSE)
			OnQuit();
	}
}

void EventHandler::OnQuit()
{
    Game::GetInstance()->Stop();
}
