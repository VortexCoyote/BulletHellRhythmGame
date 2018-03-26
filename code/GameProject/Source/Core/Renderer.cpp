#include "Renderer.h"
#include "Image.h"
#include "..\Game\Game.h"

#include "SFML\Graphics\RenderWindow.hpp"

bool Renderer::Init()
{
	mySFMLWindow = Game::GetInstance()->GetGameWindow()->GetRenderWindow();

    return true;
}

void Renderer::Shutdown()
{
	mySFMLWindow = nullptr;
}

void Renderer::Draw(Image* image)
{
	mySFMLWindow->draw(image->GetSprite());
}

void Renderer::Prepare()
{
	mySFMLWindow->clear();
}

void Renderer::Render()
{
	mySFMLWindow->display();
}
