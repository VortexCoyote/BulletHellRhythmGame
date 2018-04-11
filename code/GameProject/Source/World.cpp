#include "World.h"
#include "Core\Image.h"
#include "Core\Timer.h"

//CES
#include "CES\CES.h"
#include "CES\Systems.h"

Scene scene = Scene(4096*2);

void World::Create()
{
	scene.SubmitComponent<Component::Position>();
	scene.SubmitComponent<Component::Velocity>();
	scene.SubmitComponent<Component::Sprite>();
	scene.SubmitComponent<Component::BulletMovement>();
	scene.SubmitComponent<Component::Collision>();
	scene.SubmitComponent<Component::Emitter>();
	
	scene.SubmitUpdateSystem(System::Emitters);
	scene.SubmitUpdateSystem(System::BulletPhysics);
	scene.SubmitUpdateSystem(System::UpdatePosition);
	scene.SubmitUpdateSystem(System::CollisionResponse);

	scene.SubmitDrawSystem(System::DrawSprite);
}

void World::Destroy()
{
	
}

void World::Update()
{
	Song::TIME += Timer::GetElapsedFrameTime();
	Song::COUNTER += Timer::GetElapsedFrameTime()*100;

	if (Song::COUNTER > 4)
	{
		Component::Position position;
		position.x = 1024 / 2 + cos(Song::TIME) * 256;
		position.y = 768  / 2 + sin(Song::TIME) * 256;

		Entity::CreateEmitter(scene, position, BulletPattern::Lerped, Textures::BULLET_SPRITE, 
		1, 1, 0, 12, 3.14159265358 * 2 / 32, 64);

		Song::COUNTER = 0;
	}


	std::cout << "FPS: " << 1/Timer::GetElapsedFrameTime() << std::endl;
	
	scene.Update(Timer::GetElapsedFrameTime());
}

void World::Draw()
{
	scene.Draw(Timer::GetElapsedFrameTime());
}