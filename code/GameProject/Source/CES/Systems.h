#ifndef HEADER_SYSTEMS
#define HEADER_SYSTEMS

#ifndef HEADER_CES
#include "..\CES.h"
#endif

#include "Assets.h"

namespace Entity
{
	using namespace Component;

	int CreateBullet(Scene& pScene, Component::Position& pPosition, float pAngle, BulletPattern::bulletPatternPtr pBulletPattern, Image* pImage)
	{
		int bullet = pScene.RegisterEntity(
			pScene.GetMask<Position>() |
			pScene.GetMask<Velocity>() |
			pScene.GetMask<Sprite >() |
			pScene.GetMask<BulletMovement>() |
			pScene.GetMask<Collision>());

		Component::BulletMovement& bulletMovement = pScene.GetComponent<BulletMovement>(bullet);
		Component::Velocity& velocity = pScene.GetComponent<Velocity>(bullet);
		Component::Collision& collision = pScene.GetComponent<Collision>(bullet);

		pScene.GetComponent<Position>(bullet) = pPosition;

		velocity.x = 0;
		velocity.y = 0;

		pScene.GetComponent<Sprite>(bullet).image = pImage;

		bulletMovement.PatternFunction = pBulletPattern;
		bulletMovement.angle = pAngle;
		bulletMovement.time = 0.0;

		collision.outsideScreen = false;
		collision.collided = false;

		return bullet;
	}
	
	int CreateEmitter(Scene& pScene, Component::Position& pPosition, BulletPattern::bulletPatternPtr pBulletPattern, Image* pImage, 
	float pTimer, float pInterval, float pAngle, float pAngleStep, int pCount)
	{
		int emitter = pScene.RegisterEntity(
					  pScene.GetMask<Position>() |
					  pScene.GetMask<Sprite >() |
					  pScene.GetMask<Emitter>());
		
		pScene.GetComponent<Position>(emitter) = pPosition;
		Component::BulletMovement& bulletMovement = pScene.GetComponent<BulletMovement>(emitter);

		Component::Emitter& emitterComponent = pScene.GetComponent<Emitter>(emitter);
		
		pScene.GetComponent<Sprite>(emitter).image = pImage;

		emitterComponent.timer = pTimer;
		emitterComponent.interval = pInterval;

		emitterComponent.angle = pAngle;
		emitterComponent.angleStep = pAngleStep;

		emitterComponent.count = pCount;
		emitterComponent.PatternFunction = pBulletPattern;
		
		return emitter;
	}
}

namespace System
{
	using namespace Component;

	SYSTEM(Emitters)
	{
		Mask mask = scene.GetMask<Position>()|
				    scene.GetMask<Emitter> ()|
					scene.GetMask<Sprite>  ();

		if (ENTITY(mask))
		{
			Emitter& emitter = scene.GetComponent<Emitter>(entity);
			Position& position = scene.GetComponent<Position>(entity);
			
			emitter.timer -= emitter.interval;

			for (int i = 0; i < emitter.count; ++i)
			{
				emitter.angle += emitter.angleStep;
				
				Entity::CreateBullet(scene, position, emitter.angle, emitter.PatternFunction, scene.GetComponent<Sprite>(entity).image);
			}
			
			if (emitter.timer <= 0) scene.DestroyEntity(entity);
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
				bulletMovement.angle);

			if (position.x > 1024) collision.outsideScreen = true;
			if (position.x < -16) collision.outsideScreen = true;
			if (position.y > 768) collision.outsideScreen = true;
			if (position.y < -16) collision.outsideScreen = true;

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


