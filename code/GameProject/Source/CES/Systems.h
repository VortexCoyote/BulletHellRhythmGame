#ifndef HEADER_SYSTEMS
#define HEADER_SYSTEMS

#ifndef HEADER_CES
#include "..\CES.h"
#endif

#include "Assets.h"

namespace Entity
{
	using namespace Component;

	int CreateBullet(Scene& pScene, Position& pPosition, float pAngle, float pSpeed, BulletPattern::bulletPatternPtr pBulletPattern, Image* pImage)
	{
		int bullet = pScene.RegisterEntity(
			pScene.GetMask<Position>() |
			pScene.GetMask<Velocity>() |
			pScene.GetMask<Sprite >() |
			pScene.GetMask<BulletMovement>() |
			pScene.GetMask<Collision>());

		BulletMovement& bulletMovement = pScene.GetComponent<BulletMovement>(bullet);
		Velocity& velocity = pScene.GetComponent<Velocity>(bullet);
		Collision& collision = pScene.GetComponent<Collision>(bullet);

		pScene.GetComponent<Position>(bullet) = pPosition;

		velocity.x = cos(pAngle)*pSpeed;
		velocity.y = sin(pAngle)*pSpeed;

		pScene.GetComponent<Sprite>(bullet).image = pImage;

		bulletMovement.PatternFunction = pBulletPattern;
		bulletMovement.angle = pAngle;
		bulletMovement.speed = pSpeed;
		bulletMovement.time = 0.0;

		collision.outsideScreen = false;
		collision.collided = false;

		return bullet;
	}
	
	int CreateEmitter(Scene& pScene, Position& pPosition, BulletPattern::bulletPatternPtr pBulletPattern, Image* pImage, 
	float pTimer, float pInterval, float pAngle, float pSpeed, float pAngleStep, int pCount)
	{
		int emitter = pScene.RegisterEntity(
					  pScene.GetMask<Position>() |
					  pScene.GetMask<Sprite >() |
					  pScene.GetMask<Emitter>());
		
		pScene.GetComponent<Position>(emitter) = pPosition;
		BulletMovement& bulletMovement = pScene.GetComponent<BulletMovement>(emitter);

		Emitter& emitterComponent = pScene.GetComponent<Emitter>(emitter);
		
		pScene.GetComponent<Sprite>(emitter).image = pImage;

		emitterComponent.timer = pTimer;
		emitterComponent.interval = pInterval;

		emitterComponent.angle = pAngle;
		emitterComponent.angleStep = pAngleStep;

		emitterComponent.speed = pSpeed;

		emitterComponent.count = pCount;
		emitterComponent.PatternFunction = pBulletPattern;
		
		return emitter;
	}
	
	int CreatePlayer(Scene& pScene, Position& pPosition, Velocity& pVelocity, Image* pImage)
	{
		int player = pScene.RegisterEntity(
					 pScene.GetMask<Position>() |
					 pScene.GetMask<Velocity>() |
					 pScene.GetMask<Sprite >()) ;

		pScene.GetComponent<Position>(player) = pPosition;
		pScene.GetComponent<Velocity>(player) = pVelocity;
		pScene.GetComponent<Sprite>(player).image = pImage;

		return player;
	}
}

namespace System
{
	using namespace Component;

	//UPDATE
	SYSTEM(Emitters)
	{
		Mask mask = scene.GetMask<Position>()|
				    scene.GetMask<Emitter> ()|
					scene.GetMask<Sprite>  ();

		if (ENTITY(mask))
		{
			Emitter& emitter = scene.GetComponent<Emitter>(entity);
			Position& position = scene.GetComponent<Position>(entity);
			
			//emitter.timer -= emitter.interval;
			emitter.timer -= deltaTime*1000;

			if (emitter.timer <= 0)
			{
				for (int i = 0; i < emitter.count; ++i)
				{
					emitter.angle += emitter.angleStep;
				
					Entity::CreateBullet(scene, position, emitter.angle, emitter.speed, emitter.PatternFunction, Textures::BULLET_SPRITE);
				}

				scene.DestroyEntity(entity);
			}
			
			//if (emitter.timer <= 0) scene.DestroyEntity(entity);
		}
	}
	SYSTEM(BulletPhysics)
	{
		Mask mask = scene.GetMask<BulletMovement>() |
				    scene.GetMask<Position>() |
					scene.GetMask<Velocity>() |
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
						   bulletMovement.angle, 
						   bulletMovement.speed);

			if (position.x > 1024) collision.outsideScreen = true;
			if (position.x <  -16) collision.outsideScreen = true;
			if (position.y >  768) collision.outsideScreen = true;
			if (position.y <  -16) collision.outsideScreen = true;

			bulletMovement.time += deltaTime;
		}
	}
	SYSTEM(UpdatePosition)
	{
		Mask mask = scene.GetMask<Position>() |
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
	
	//DRAW
	SYSTEM(DrawSprite)
	{
		Mask mask = scene.GetMask<Position>() |
			scene.GetMask<Sprite  >();

		if (ENTITY(mask))
		{
			Position& entityPosition = scene.GetComponent<Position>(entity);
			Sprite&   entitySprite = scene.GetComponent<Sprite  >(entity);

			entitySprite.image->SetPosition(entityPosition.x,
				entityPosition.y);

			Game::GetRenderer()->Draw(entitySprite.image);
		}
	}
}

#endif


