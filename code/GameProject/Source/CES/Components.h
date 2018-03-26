#ifndef HEADER_COMPONENTS
#define HEADER_COMPOENNTS

#include "..\Core\Image.h"

namespace Component
{
	struct Position
	{
		float x;
		float y;
	};
	struct Velocity
	{
		float x;
		float y;
	};
	struct Sprite
	{
		Image* image;
	};
	struct BulletMovement
	{
		float time = 0.0;
		float angle = 0.0;

		void(*PatternFunction)(Velocity& velocity, const float time, const float deltaTime, float& angle);
	};
	struct Collision
	{
		bool outsideScreen;
		bool collided;
	};
}

#endif