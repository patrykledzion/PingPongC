#include "gameObject.h"

gameObjectCircle* createGameObject_circle(long x, long y, long r, long depth, Color4_t color)
{
	gameObjectCircle* obj = malloc(sizeof(gameObjectCircle));

	if (obj == NULL)return NULL;

	obj->type = GO_CIRCLE;
	obj->id = OBJECT_ID;
	obj->x = x;
	obj->y = y;
	obj->r = r;
	obj->depth = depth;
	obj->color = color;
	obj->speedX = 0;
	obj->speedY = 0;

	OBJECT_ID++;

	return obj;
}

gameObjectRect* createGameObject_rect(long x, long y, long w, long h, long depth, Color4_t color)
{
	gameObjectRect* obj = malloc(sizeof(gameObjectRect));

	if (obj == NULL)return NULL;

	obj->type = GO_RECT;
	obj->id = OBJECT_ID;
	obj->x = x;
	obj->y = y;
	obj->w = w;
	obj->h = h;
	obj->depth = depth;
	obj->color = color;
	
	OBJECT_ID++;

	return obj;

}

void freeGameObjects(void** gameObjects, int count)
{
	if (gameObjects == NULL)return;
	for (int i = 0; i < count; i++)
	{
		free(gameObjects[i]);
	}
	free(gameObjects);
}
