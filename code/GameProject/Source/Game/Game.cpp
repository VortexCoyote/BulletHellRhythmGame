#include "Game.h"
//#include "Renderer.h"
#include "..\Core\Timer.h"

Game* Game::ourGame = nullptr;

bool Game::Create()
{
    if (ourGame == nullptr)
    {
        ourGame = new Game();
        if (!ourGame->Init())
        {
            delete ourGame;
            return false;
        }
    }
    return true;
}

Game* Game::GetInstance()
{
    return ourGame;
}

void Game::Destroy()
{
    if (ourGame)
    {
        ourGame->Shutdown();
        delete ourGame;
    }
}

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Init()
{
    myRenderer.Init();
    myInputManager.Init();
    myEventHandler.Init();

    return true;
}

bool Game::Run()
{
    myRunning = true;

    myWorld.Create();

    while (myRunning)
    {
        Update();
        Render();
    }

    myWorld.Destroy();

    return true;
}

void Game::Render()
{
	myRenderer.Prepare();

    myWorld.Draw();

    myRenderer.Render();
}

void Game::Stop()
{
    myRunning = false;
}

bool Game::Shutdown()
{
    myRenderer.Shutdown();
    return true;
}

void Game::Update()
{
    Timer::Update();

	myEventHandler.HandleEvents();

    myInputManager.Update();

    myWorld.Update();
}


// Static getters
GameWindow* Game::GetGameWindow()
{
	if (ourGame)
	{
		return &ourGame->myGameWindow;
	}

	return nullptr;
}

Renderer* Game::GetRenderer()
{
    if (ourGame)
    {
        return &ourGame->myRenderer;
    } 

    return nullptr;
}

InputManager* Game::GetInput()
{
    if (ourGame)
    {
        return &ourGame->myInputManager;
    } 

    return nullptr;
}

World* Game::GetWorld()
{
    if (ourGame)
    {
        return &ourGame->myWorld;
    } 

    return nullptr;
}
