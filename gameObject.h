#pragma once

#include "utils.h"
#include <stdlib.h>

#define GO_CIRCLE 0
#define GO_RECT 1
#define GO_TRIANGLE 2

static int OBJECT_ID = 0;

struct gameObjectRect {
	Color4_t color;
	int type;
	int id;
	long x;
	long y;
	long w;
	long h;
	long depth;
}; typedef struct gameObjectRect gameObjectRect;

struct gameObjectTriangle {
	int type;
	int id;
	Vector3_t c1;
	Vector3_t c2;
	Vector3_t c3;
	Color4_t color;
}; typedef struct gameObjectTriangle gameObjectTriangle;

struct gameObjectCircle {
	Color4_t color;
	int type;
	int id;
	long x;
	long y;
	long r;
	long depth;
	int speedX;
	int speedY;
	
	
}; typedef struct gameObjectCircle gameObjectCircle;

gameObjectCircle* createGameObject_circle(long x, long y, long r, long depth, Color4_t color);
gameObjectRect* createGameObject_rect(long x, long y, long w, long h, long depth, Color4_t color);

void freeGameObjects(void** gameObjects, int count);