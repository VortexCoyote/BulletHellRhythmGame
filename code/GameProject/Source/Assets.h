#ifndef HEADER_ASSETS
#define HEADER_ASSETS

#include "Core\Image.h"
#include <SFML\Audio\Music.hpp>

namespace Textures
{
	static Image* BULLET_SPRITE = new Image("bullet.png");
}

namespace Song
{
	static sf::Music MUSIC;

	static float TIME = 0;
	static float COUNTER = 0;
}

#endif