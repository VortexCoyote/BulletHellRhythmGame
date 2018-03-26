#include "Game\Game.h"

int main(int argc, char **argv)
{
	if (!Game::Create())
	{
		return 1;
	}
	
	Game::GetInstance()->Run();

	Game::Destroy();

	return 0;
}
