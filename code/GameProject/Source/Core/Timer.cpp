#include "Timer.h"

float Timer::s_lastFrameTime = 0.0f;
float Timer::s_frameTime = 0.0f;
sf::Clock Timer::s_timer;

void Timer::Update()
{
	s_lastFrameTime = s_frameTime;
	s_frameTime = static_cast<float>(s_timer.getElapsedTime().asMilliseconds()) / 1000.f;
}

float Timer::GetElapsedFrameTime()
{
    return s_frameTime - s_lastFrameTime;
}

float Timer::GetTime()
{
    return s_frameTime;
}
