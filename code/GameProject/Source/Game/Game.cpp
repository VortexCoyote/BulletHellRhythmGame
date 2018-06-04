#include "Game.h"
//#include "Renderer.h"
#include "..\Core\Timer.h"

Game* Game::sGame = nullptr;

bool Game::Create()
{
    if (sGame == nullptr)
    {
		sGame = new Game();
        if (!sGame->Init())
        {
            delete sGame;
            return false;
        }
    }
    return true;
}

Game* Game::GetInstance()
{
    return sGame;
}

void Game::Destroy()
{
    if (sGame)
    {
		sGame->Shutdown();
        delete sGame;
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
    mRenderer.Init();
    mInputManager.Init();
    mEventHandler.Init();

    return true;
}

bool Game::Run()
{
    mRunning = true;

    mWorld.Create();

    while (mRunning)
    {
        Update();
        Render();
    }

    mWorld.Destroy();

    return true;
}

void Game::Render()
{
	mRenderer.Prepare();

    mWorld.Draw();

    mRenderer.Render();
}

void Game::Stop()
{
    mRunning = false;
}

bool Game::Shutdown()
{
    mRenderer.Shutdown();
    return true;
}

void Game::Update()
{
    Timer::Update();

	mEventHandler.HandleEvents();

    mInputManager.Update();

    mWorld.Update();
}


// Static getters
GameWindow* Game::GetGameWindow()
{
	if (sGame)
	{
		return &sGame->mGameWindow;
	}

	return nullptr;
}

Renderer* Game::GetRenderer()
{
    if (sGame)
    {
        return &sGame->mRenderer;
    } 

    return nullptr;
}

InputManager* Game::GetInput()
{
    if (sGame)
    {
        return &sGame->mInputManager;
    } 

    return nullptr;
}

World* Game::GetWorld()
{
    if (sGame)
    {
        return &sGame->mWorld;
    } 

    return nullptr;
}
