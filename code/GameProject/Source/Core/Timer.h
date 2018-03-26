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
    
	static float s_lastFrameTime;
    static float s_frameTime;

	static sf::Clock s_timer;
};

#endif