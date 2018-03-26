#ifndef HEADER_VECTOR2F
#define HEADER_VECTOR2F

#include <math.h>

struct Vector2f
{
	Vector2f() : x(0), y(0)
	{

	}

	Vector2f(float anX, float anY) : x(anX), y(anY)
	{

	}

	Vector2f operator-(Vector2f& v2)
	{
		return Vector2f(x - v2.x, y - v2.y);
	}

	void Set(float anX, float anY)
	{
		x = anX;
		y = anY;
	}

	void Normalize()
	{
		float l = Length();
		x = x / l;
		y = y / l;
	}

	float Length()
	{
		return (float)sqrt(x*x + y*y);
	}

	float x;
	float y;
};

#endif
