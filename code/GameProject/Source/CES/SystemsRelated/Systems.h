#ifndef HEADER_SYSTEMS
#define HEADER_SYSTEMS

#ifndef HEADER_CES
#include "..\CES.h"
#endif

namespace System
{
	using namespace Component;

	SYSTEM(BulletPhysics)
	{
		Mask mask = scene.GetMask<BulletMovement>()|
				    scene.GetMask<Position>()|
			        scene.GetMask<Velocity>()|
				    scene.GetMask<Collision>();

		if (ENTITY(mask))
		{
			BulletMovement& bulletMovement = scene.GetComponent<BulletMovement>(entity);
			Velocity& velocity = scene.GetComponent<Velocity>(entity);
			Position& position = scene.GetComponent<Position>(entity);
			Collision& collision = scene.GetComponent<Collision>(entity);
			
			bulletMovement.PatternFunction(velocity, 
										   bulletMovement.time,
										   deltaTime,
										   bulletMovement.angle);

			if (position.x > 1024) collision.outsideScreen = true;
			if (position.x <  -16) collision.outsideScreen = true;
			if (position.y >  768) collision.outsideScreen = true;
			if (position.y <  -16) collision.outsideScreen = true;

			bulletMovement.time += deltaTime;
		}
	}
	SYSTEM(UpdatePosition)
	{
		Mask mask = scene.GetMask<Position>()|
				    scene.GetMask<Velocity>();

		if (ENTITY(mask))
		{
			Position& position = scene.GetComponent<Position>(entity);
			Velocity& velocity = scene.GetComponent<Velocity>(entity);

			position.x += velocity.x *(deltaTime * 100);
			position.y += velocity.y *(deltaTime * 100);
		}
	}
	SYSTEM(CollisionResponse)
	{
		Mask mask = scene.GetMask<Collision>();

		if (ENTITY(mask))
		{
			Collision& collision = scene.GetComponent<Collision>(entity);

			if (collision.outsideScreen)
			{
				scene.DestroyEntity(entity);
			}
		}
	}
	SYSTEM(DrawSprite)
	{
		Mask mask = scene.GetMask<Position>()| 
					scene.GetMask<Sprite  >();

		if (ENTITY(mask))
		{
			Position& entityPosition = scene.GetComponent<Position>(entity);
			Sprite&   entitySprite   = scene.GetComponent<Sprite  >(entity);

			entitySprite.image->SetPosition(entityPosition.x, 
											entityPosition.y);

			Game::GetRenderer()->Draw(entitySprite.image);	
		}
	}
}

#endif


