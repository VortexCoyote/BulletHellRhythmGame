#ifndef HEADER_COMPONENTS
#define HEADER_COMPOENNTS

#include "..\Core\Image.h"
#include "..\Core\Math.h"

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
		float time;
		float angle;

		float speed;

		void(*PatternFunction)(Velocity& pVelocity, const float pTime, const float pDeltaTime, float& pAngle, float& pSpeed);
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
		
		float speed;

		int count;

		void(*PatternFunction)(Velocity& pVelocity, const float pTime, const float pDeltaTime, float& pAngle, float& pSpeed);
	};
}


namespace BulletPattern
{
	using namespace Component;


	typedef void(*bulletPatternPtr)(Velocity& pVelocity, const float pTime, const float pDeltaTime, float& pAngle, float& pSpeed);

	void Default(Velocity& pVelocity, const float pTime, const float pDeltaTime, float& pAngle, float& pSpeed)
	{
		pVelocity.x += cosf(pAngle)*0.01;// (abs(cosf(time*2.0) + 0.2) * 2);
		pVelocity.y += sinf(pAngle)*0.01;// (abs(cosf(time*2.0) + 0.2) * 2);
	}

	void Accelerated(Velocity& pVelocity, const float pTime, const float pDeltaTime, float& pAngle, float& pSpeed)
	{
		pSpeed += 0.01;

		pVelocity.x = cosf(pAngle)*pSpeed;
		pVelocity.y = sinf(pAngle)*pSpeed;
	}

	void Lerped(Velocity& pVelocity, const float pTime, const float pDeltaTime, float& pAngle, float& pSpeed)
	{
		pSpeed = Math::Lerp(pSpeed, 2.0f, 0.1f);

		pVelocity.x = cosf(pAngle)*pSpeed;
		pVelocity.y = sinf(pAngle)*pSpeed;
	}

	void Spiral(Velocity& pVelocity, const float pTime, const float pDeltaTime, float& pAngle, float& pSpeed)
	{
		pAngle += 3.14159265358*0.0025; //deltaTime*1.5;

		pVelocity.x += cosf(pAngle)*0.01;// (abs(cosf(time*2.0) + 0.2) * 2);
		pVelocity.y += sinf(pAngle)*0.01;// (abs(cosf(time*2.0) + 0.2) * 2);
	}
}

#endif
