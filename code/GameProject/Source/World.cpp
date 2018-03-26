#include "World.h"
#include "Core\Image.h"
#include "Core\Timer.h"

//CES
#include "CES\CES.h"
#include "CES\SystemsRelated\Systems.h"
#include "CES\SystemsRelated\BulletPatterns.h"

Scene scene = Scene(4096);

//Just testing things out, this will be removed in future iterations
int SpawnBullet(Scene& pScene, Component::Position& pPosition, float pAngle, BulletPattern::bulletPatternPtr pBulletPattern , Image* pImage)
{
	int bullet = scene.RegisterEntity(scene.GetMask<Component::Position>()|
				 scene.GetMask<Component::Velocity>()|
				 scene.GetMask<Component::Sprite >()|
				 scene.GetMask<Component::BulletMovement>()|
				 scene.GetMask<Component::Collision>());
	
	Component::BulletMovement& bulletMovement = scene.GetComponent<Component::BulletMovement>(bullet);
	Component::Velocity& velocity = scene.GetComponent<Component::Velocity>(bullet);
	Component::Collision& collision = scene.GetComponent<Component::Collision>(bullet);

	scene.GetComponent<Component::Position>(bullet) = pPosition;
	
	velocity.x = 0;
	velocity.y = 0;

	scene.GetComponent<Component::Sprite>(bullet).image = pImage;

	bulletMovement.PatternFunction = pBulletPattern;
	bulletMovement.angle = pAngle;
	bulletMovement.time = 0.0;

	collision.outsideScreen = false;
	collision.collided = false;

	return bullet;
}
float counter;

void World::Create()
{
	m_bulletSprite = new Image("bullet.png");
	
	scene.SubmitComponent<Component::Position>();
	scene.SubmitComponent<Component::Velocity>();
	scene.SubmitComponent<Component::Sprite>();
	scene.SubmitComponent<Component::BulletMovement>();
	scene.SubmitComponent<Component::Collision>();
	
	scene.SubmitUpdateSystem(System::BulletPhysics);
	scene.SubmitUpdateSystem(System::UpdatePosition);
	scene.SubmitUpdateSystem(System::CollisionResponse);

	scene.SubmitDrawSystem(System::DrawSprite);

	counter = 0;
}

void World::Destroy()
{

}

void World::Update()
{
	counter += 1 *(Timer::GetElapsedFrameTime() * 100);

	if (counter > 8)
	{
		for (float i = 0; i < 3.14159265358 * 2; i += 3.14159265358 / 8)
		{
			Component::Position position;

			position.x = 1024 / 2;
			position.y = 768  / 2;

			SpawnBullet(scene, position, i, BulletPattern::DefaultPattern, m_bulletSprite);
		}

		counter = 0;
	}

	scene.Update(Timer::GetElapsedFrameTime());

	std::cout << "FPS: " << 1/Timer::GetElapsedFrameTime() << std::endl;
}

void World::Draw()
{
	scene.Draw(Timer::GetElapsedFrameTime());
}