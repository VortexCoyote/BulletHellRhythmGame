#include "World.h"
#include "Core\Image.h"
#include "Core\Timer.h"

#include <map>
#include <fstream>
#include <sstream>

//CES
#include "CES\CES.h"
#include "CES\Systems.h"

Scene scene = Scene(8192);

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


	if (!Song::MUSIC.openFromFile("ebony ivory.ogg")) std::cout << "SHIT DOESNT WORK" << std::endl; // error
	Song::MUSIC.play();

	std::ifstream chart;
	chart.open("ebony ivory.brf", std::ifstream::in);
	
	std::string line;

	int parameter = 0;

	if (chart.is_open())
	{
		while (std::getline(chart, line, ';'))
		{
			std::stringstream linestream(line);
			std::string value;

			int values[7];

			while (std::getline(linestream, value, ','))
			{
				//TIME,X,Y,ANGLE,ANGLESTEP,SPEED,COUNT
				//0	   1 2 3     4         5     6

				values[parameter] = std::stoi(value);

				++parameter;
			}

			Component::Position position;
			position.x = values[1]*168;
			position.y = values[2]*100;

			Entity::CreateEmitter(scene, position, BulletPattern::Lerped, Textures::BULLET_SPRITE,
			values[0]+1000, 0, values[3], values[5], values[4]*(3.14159265358/180), values[6]);

			parameter = 0;

		}
	}
	else std::cout << "Shit doesn't work sorry" << std::endl;
}

void World::Destroy()
{
	
}

void World::Update()
{
	std::cout << "FPS: " << 1/Timer::GetElapsedFrameTime() << std::endl;
	
	scene.Update(Timer::GetElapsedFrameTime());
}

void World::Draw()
{
	scene.Draw(Timer::GetElapsedFrameTime());
}