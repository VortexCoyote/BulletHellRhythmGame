#include "InputManager.h"

#include "..\Game\Game.h"
#include "GameWindow.h"

#include "SFML\Window\Keyboard.hpp"
#include "SFML\Window\Mouse.hpp"
#include "SFML\Window.hpp"

void InputManager::Init()
{
    for (int i = 0; i < eTOTAL_SIZE; ++i)
    {
        mButtons[i].isDown = false;
        mButtons[i].wasDown = false;
    }
}

void InputManager::Update()
{
    for (int i = 0; i < eTOTAL_SIZE; ++i)
    {
        mButtons[i].wasDown = mButtons[i].isDown;
    }

	UpdateButtonStates();
	UpdateCursorPosition();
}

bool InputManager::IsButtonDown(Button pButton)
{
    if (pButton >= eTOTAL_SIZE || pButton < 0)
    {
        return false;
    }

    return mButtons[pButton].isDown;
}

bool InputManager::WasButtonPressed(Button pButton)
{
    if (pButton >= eTOTAL_SIZE || pButton < 0)
    {
        return false;
    }

    return mButtons[pButton].isDown && !mButtons[pButton].wasDown;
}

void InputManager::UpdateButtonStates()
{
	if (!Game::GetGameWindow()->GetRenderWindow()->hasFocus())
		return;

	mButtons[eMoveUp].isDown		= sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	mButtons[eMoveDown].isDown		= sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	mButtons[eMoveLeft].isDown		= sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	mButtons[eMoveRight].isDown	= sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	mButtons[eFire].isDown			= sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void InputManager::UpdateCursorPosition()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*Game::GetGameWindow()->GetRenderWindow());
    mCursorPos.Set((float)mousePos.x, (float)mousePos.y);
}

void InputManager::GetCursorPosition(float& pX, float& pY)
{
    pX = mCursorPos.x;
    pY = mCursorPos.y;
}
