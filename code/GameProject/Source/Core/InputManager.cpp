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
        myButtons[i].isDown = false;
        myButtons[i].wasDown = false;
    }
}

void InputManager::Update()
{
    for (int i = 0; i < eTOTAL_SIZE; ++i)
    {
        myButtons[i].wasDown = myButtons[i].isDown;
    }

	UpdateButtonStates();
	UpdateCursorPosition();
}

bool InputManager::IsButtonDown(Button button)
{
    if (button >= eTOTAL_SIZE || button < 0)
    {
        return false;
    }

    return myButtons[button].isDown;
}

bool InputManager::WasButtonPressed(Button button)
{
    if (button >= eTOTAL_SIZE || button < 0)
    {
        return false;
    }

    return myButtons[button].isDown && !myButtons[button].wasDown;
}

void InputManager::UpdateButtonStates()
{
	if (!Game::GetGameWindow()->GetRenderWindow()->hasFocus())
		return;

	myButtons[eMoveUp].isDown		= sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	myButtons[eMoveDown].isDown		= sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	myButtons[eMoveLeft].isDown		= sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	myButtons[eMoveRight].isDown	= sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	myButtons[eFire].isDown			= sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void InputManager::UpdateCursorPosition()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*Game::GetGameWindow()->GetRenderWindow());
    myCursorPos.Set((float)mousePos.x, (float)mousePos.y);
}

void InputManager::GetCursorPosition(float& X, float& Y)
{
    X = myCursorPos.x;
    Y = myCursorPos.y;
}
