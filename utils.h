#pragma once

#include <sys/utime.h>

struct Color4 {
	float r;
	float g;
	float b;
	float a;
}; typedef struct Color4 Color4_t;

struct Vector3 {
	long x;
	long y;
	long z;
}; typedef struct Vector3 Vector3_t;

struct Vector2 {
	long x;
	long y;
	long z;
}; typedef struct Vector2 Vector2_t;

Vector3_t Vector3(long x, long y, long z);
Vector2_t Vector2(long x, long y);
Color4_t Color4f(float r, float g, float b, float a);


unsigned long deltaTime(int fps);