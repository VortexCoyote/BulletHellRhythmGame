#ifndef HEADER_ASSETS
#define HEADER_ASSETS

#include "Core\Image.h"
#include <SFML\Audio\Music.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Graphics\RenderTexture.hpp>

namespace Textures
{
	static Image* BULLET_SPRITE = new Image("bullet.png");
	static Image* EMITTER_SPRITE = new Image("emitter.png");
	static Image* GUI_SPRITE = new Image("gui.png");
	static Image* BLANK_SPRITE = new Image("blank.png");
	static Image* PLAYER_SPRITE = new Image("player.png");

	static sf::RenderTexture* COLLISION_TEXTURE = new sf::RenderTexture();
}

namespace Song
{
	static sf::Music MUSIC;

	static float TIME = 0;
	static float COUNTER = 0;

	static bool PLAYING = false;
}

#endif