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
	struct Emitter 
	{
		float timer;
		float interval;
		
		float angle;
		float angleStep;
		
		int count;

		void(*PatternFunction)(Velocity& velocity, const float time, const float deltaTime, float& angle);
	};
}

namespace BulletPattern
{
	using namespace Component;

	typedef void(*bulletPatternPtr)(Velocity& velocity, const float time, const float deltaTime, float& angle);

	void Default(Velocity& velocity, const float time, const float deltaTime, float& angle)
	{
		velocity.x += cosf(angle)*0.01;// (abs(cosf(time*2.0) + 0.2) * 2);
		velocity.y += sinf(angle)*0.01;// (abs(cosf(time*2.0) + 0.2) * 2);
	}

	void Spiral(Velocity& velocity, const float time, const float deltaTime, float& angle)
	{
		angle += 3.14159265358*0.0025; //deltaTime*1.5;

		velocity.x += cosf(angle)*0.01;// (abs(cosf(time*2.0) + 0.2) * 2);
		velocity.y += sinf(angle)*0.01;// (abs(cosf(time*2.0) + 0.2) * 2);
	}
}

#endif
