#include "Renderer.h"
#include "Image.h"
#include "..\Game\Game.h"

#include "SFML\Graphics\RenderWindow.hpp"

bool Renderer::Init()
{
	mSFMLWindow = Game::GetInstance()->GetGameWindow()->GetRenderWindow();

    return true;
}

void Renderer::Shutdown()
{
	mSFMLWindow = nullptr;
}

void Renderer::Draw(Image* pImage)
{
	mSFMLWindow->draw(pImage->GetSprite());
}

void Renderer::Prepare()
{
	mSFMLWindow->clear();
}

void Renderer::Render()
{
	mSFMLWindow->display();
}
