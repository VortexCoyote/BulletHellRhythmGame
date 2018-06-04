#include "World.h"
#include "Core\Image.h"
#include "Core\Timer.h"

#include "Windows.h"
#include <chrono>
#include <thread>

#include <map>
#include <fstream>
#include <sstream>

//CES
#include "CES\CES.h"
#include "CES\Systems.h"

Scene mScene = Scene(8192);
int mPlayer;

void World::Create()
{
	mScene.SubmitComponent<Component::Position>();
	mScene.SubmitComponent<Component::Velocity>();
	mScene.SubmitComponent<Component::Sprite>();
	mScene.SubmitComponent<Component::BulletMovement>();
	mScene.SubmitComponent<Component::Collision>();
	mScene.SubmitComponent<Component::Emitter>();
	
	mScene.SubmitUpdateSystem(System::Emitters);
	mScene.SubmitUpdateSystem(System::BulletPhysics);
	mScene.SubmitUpdateSystem(System::UpdatePosition);
	mScene.SubmitUpdateSystem(System::CollisionResponse);

	mScene.SubmitDrawSystem(System::DrawSprite);


	std::ifstream chart;
	chart.open("brain power.brf", std::ifstream::in);
	
	std::string line;

	int parameter = 0;

	//Parse the file format
	if (chart.is_open())
	{
		while (std::getline(chart, line, ';'))
		{
			std::stringstream linestream(line);
			std::string value;

			int values[8];


			while (std::getline(linestream, value, ','))
			{
				//TIME,X,Y,ANGLE,SPEED,COUNT
				//0	   1 2 3     4     5

				values[parameter] = std::stoi(value);

				++parameter;
			}
			
			Component::Position position;
			position.x = values[1]*96;
			position.y = values[2]*86;


			Entity::CreateEmitter(mScene, position, BulletPattern::Lerped, Textures::BLANK_SPRITE,
			values[0]+900, 0, values[3]*(3.14159265358 / 180), values[4], (2.0*3.14159265358)/values[5], values[5]);

			parameter = 0;	
		}
	}
	else std::cout << "Shit doesn't work sorry" << std::endl;
	
	if (!Song::MUSIC.openFromFile("brain power.ogg")) std::cout << "SHIT DOESNT WORK" << std::endl; // error


	//Set Up Rendertexture for collision
	if (!Textures::COLLISION_TEXTURE->create(1024, 768))
		std::cout << "surfaces am I right??" << std::endl;

	
	//Create Player
	Component::Position playerPosition;

	playerPosition.x = 96*3 - 16;
	playerPosition.y = 700;

	Component::Velocity playerVelocity;

	playerVelocity.x = 0;
	playerVelocity.y = 0;

	mPlayer = Entity::CreatePlayer(mScene, playerPosition, playerVelocity, Textures::PLAYER_SPRITE);
}



void World::Destroy()
{
	
}

void World::Update()
{
	//std::cout << "FPS: " << 1/Timer::GetElapsedFrameTime() << std::endl;
	
	if (Song::PLAYING == false) 
	{
		Song::MUSIC.play();
		Song::PLAYING = true;
	}

	sf::Keyboard input;

	//Player Update
	float speed = 3.5;
	if (input.isKeyPressed(input.LShift)) speed = 1.5;

	Component::Position& position = mScene.GetComponent<Component::Position>(mPlayer);

	position.x += (input.isKeyPressed(input.Right) - input.isKeyPressed(input.Left))*speed;
	position.y += (input.isKeyPressed(input.Down) - input.isKeyPressed(input.Up))*speed;
	
	mScene.Update(Timer::GetElapsedFrameTime());
}

void World::Draw()
{
	mScene.Draw(Timer::GetElapsedFrameTime());

	//GUI
	Textures::GUI_SPRITE->SetPosition(6 * 96 + 16, 0);
	Game::GetRenderer()->Draw(Textures::GUI_SPRITE);
}