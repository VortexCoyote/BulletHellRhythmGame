#ifndef HEADER_BULLETPATTERNS
#define HEADER_BULLETPATTERNS

#ifndef HEADER_CES
#include "..\CES.h"
#endif

namespace BulletPattern
{
	using namespace Component;

	typedef void(*bulletPatternPtr)(Velocity& velocity, const float time, const float deltaTime, float& angle);

	void DefaultPattern(Velocity& velocity, const float time, const float deltaTime, float& angle)
	{
		angle += 3.14159265358*0.0025; //deltaTime*1.5;

		velocity.x += cosf(angle)*0.01;// (abs(cosf(time*2.0) + 0.2) * 2);
		velocity.y += sinf(angle)*0.01;// (abs(cosf(time*2.0) + 0.2) * 2);
	}
}

#endif