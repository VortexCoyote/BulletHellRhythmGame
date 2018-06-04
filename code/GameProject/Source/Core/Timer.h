#ifndef HEADER_TIMER
#define HEADER_TIMER

#include "SFML\System\Clock.hpp"

class Timer
{
public:
   
	static void Update();

    static float GetElapsedFrameTime();
    static float GetTime();

private:
    
	static float sLastFrameTime;
    static float sFrameTime;

	static sf::Clock sTimer;
};

#endif