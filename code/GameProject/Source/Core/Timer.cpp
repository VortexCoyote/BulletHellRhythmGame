#include "Timer.h"

float Timer::sLastFrameTime = 0.0f;
float Timer::sFrameTime = 0.0f;
sf::Clock Timer::sTimer;

void Timer::Update()
{
	sLastFrameTime = sFrameTime;
	sFrameTime = static_cast<float>(sTimer.getElapsedTime().asMilliseconds()) / 1000.f;
}

float Timer::GetElapsedFrameTime()
{
    return sFrameTime - sLastFrameTime;
}

float Timer::GetTime()
{
    return sFrameTime;
}
