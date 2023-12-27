#include "utils.h"

Vector3_t Vector3(long x, long y, long z)
{
	Vector3_t ret = { x,y,z };
	return ret;
}

Vector2_t Vector2(long x, long y)
{
	Vector2_t ret = { x,y };
	return ret;
}

Color4_t Color4f(float r, float g, float b, float a)
{
	Color4_t ret = { r,g,b,a };
	return ret;
}

 

unsigned long deltaTime(int fps)
{
	
}
