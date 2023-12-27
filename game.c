#include "game.h"
 
#define PADDLE_LEFT		0
#define PADDLE_RIGHT	1
#define BALL			2
#define WALL_TOP		3
#define WALL_BOTTOM		4

#define BOARD_WIDTH		1000
#define BOARD_HEIGHT	600

#define DEBUG 1

void game_init(Game* game)
{
	if (game == NULL)return;
	
	game->title = "Gierka";
	game->maxFps = 60;
	game->lastFrame = 0;

	int window_width = 1000;
	int window_height = 800;

	long paddle_width = 20;
	long paddle_height = 150;

	long board_height = BOARD_HEIGHT;
	long board_width = BOARD_WIDTH;

	window* wnd = createWindow(window_width, window_height, game->title);
	if (wnd == NULL)
	{
		return -1;
	}
	game->window = wnd;
	game->userPoints = 0;
	game->computerPoints = 0;
	game->gameObjectsCount = 5;
	game->gameObjects = malloc(game->gameObjectsCount * sizeof(gameObjectRect));


	//ball and paddles
	game->gameObjects[0] = createGameObject_rect(10.0f, board_height / 2 - paddle_height / 2,paddle_width, paddle_height,0.0f,Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	game->gameObjects[1] = createGameObject_rect(board_width - paddle_width - 26.0f, board_height / 2 - paddle_height / 2,paddle_width,paddle_height,0.0f,Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	game->gameObjects[2] = createGameObject_circle(board_width / 2, board_height / 2, paddle_width / 2, 0, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	
	//Top and bottom walls
	game->gameObjects[3] = createGameObject_rect(0.0f, 0.0f, board_width, 10, 0.0f, Color4f(1.0f, 1.0f, 1.0f, 1.0f));
	game->gameObjects[4] = createGameObject_rect(0.0f, board_height - 10, board_width, 10, 0.0f, Color4f(1.0f, 1.0f, 1.0f, 1.0f));


	//Set ball speed
	gameObjectCircle* ball = (gameObjectCircle*)game->gameObjects[2];
	ball->speedX = 10;
	ball->speedY = -5;
}

void game_udpate(Game* game)
{
	if (game == NULL)return;

	gameObjectCircle *ball = (gameObjectCircle*)game->gameObjects[BALL];
	gameObjectRect* paddle1 = (gameObjectRect*)game->gameObjects[PADDLE_LEFT];
	gameObjectRect* paddle2 = (gameObjectRect*)game->gameObjects[PADDLE_RIGHT];
	gameObjectRect* wallTop = (gameObjectRect*)game->gameObjects[WALL_TOP];
	gameObjectRect* wallBottom = (gameObjectRect*)game->gameObjects[WALL_BOTTOM];
	ball->super->x += ball->speedX;
	ball->super->y += ball->speedY;

	if (checkBallCollision(ball, paddle1) || checkBallCollision(ball, paddle2))ball->speedX *= -1;
	if (checkBallCollision(ball, wallTop) || checkBallCollision(ball, wallBottom))ball->speedY *= -1;
	computerMove(game);
	keyboardEvents(game);
	checkPoint(game);
	
}

void game_draw(Game* game)
{
	if (game == NULL)return;

	startDraw(game->window);

	for (int i = 0; i < game->gameObjectsCount; i++)
	{
		gameObjectRect* obj_tmp = (gameObjectRect*)game->gameObjects[i];
		
		//printf("OBJECT TYPE: %d\n", obj_tmp->type);
		switch (obj_tmp->super->type)
		{
		case GO_RECT:
		{
			gameObjectRect* obj = (gameObjectRect*)game->gameObjects[i];
			drawRect(obj->super->x, obj->super->y, obj->w, obj->h, obj->super->color, obj->depth, game->window);
			break;
		}
		case GO_CIRCLE:
		{
			gameObjectCircle* obj = (gameObjectCircle*)game->gameObjects[i];
			drawCircle(obj->super->x, obj->super->y, obj->r, 360, obj->super->color, obj->depth, game->window);
			break;
		}
		default: 
			break;
		}
	}

	drawRect(0, game->window->height - 20 - game->window->offsetY, game->window->width, 10, Color4f(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, game->window);

	endDraw(game->window);
}

void game_destruct(Game* game)
{
	printf("window closed");
	freeGameObjects(game->gameObjects, game->gameObjectsCount);
	free(game->window);
}

int checkBallCollision(gameObjectCircle* obj1, gameObjectRect* obj2)
{
	if (
		obj1->super->x + obj1->r	>	obj2->super->x				&&
		obj1->super->x - obj1->r	<	obj2->super->x + obj2->w	&&
		obj1->super->y + obj1->r	>	obj2->super->y				&&
		obj1->super->y - obj1->r	<	obj2->super->y + obj2->h	
		)
		return 1;
	return 0;
}

void checkPoint(Game* game)
{
	gameObjectCircle* ball = (gameObjectCircle*)game->gameObjects[BALL];
	gameObjectRect* paddleLeft = (gameObjectRect*)game->gameObjects[PADDLE_LEFT];
	gameObjectRect* paddleRight = (gameObjectRect*)game->gameObjects[PADDLE_RIGHT];

	if (ball->super->x - ball->r < paddleLeft->super->x)
	{
		ball->super->x = game->window->width / 2;
		ball->super->y = game->window->height / 2;
		game->computerPoints++;
		if (DEBUG)printf("USER %d : %d COMPUTER\n", game->userPoints, game->computerPoints);
	}
	else if (ball->super->x + ball->r > paddleRight->super->x + paddleRight->w)
	{
		ball->super->x = game->window->width / 2;
		ball->super->y = game->window->height / 2;
		game->userPoints++;
		if (DEBUG)printf("USER %d : %d COMPUTER\n", game->userPoints, game->computerPoints);

	}
}


int keyboardEvents(Game* game)
{
	gameObjectRect* paddleLeft = (gameObjectRect*)game->gameObjects[PADDLE_LEFT];
	if (game->window->keysPressed[VK_UP] && paddleLeft->super->y > 0)paddleLeft->super->y -= 5;
	if (game->window->keysPressed[VK_DOWN] && paddleLeft->super->y + paddleLeft->h < BOARD_HEIGHT)paddleLeft->super->y += 5;
}

void computerMove(Game* game)
{
	gameObjectCircle* ball = (gameObjectCircle*)game->gameObjects[BALL];
	gameObjectRect* paddleRight = (gameObjectRect*)game->gameObjects[PADDLE_RIGHT];

	if (ball->speedX > 0 && ball->super->x > BOARD_WIDTH / 2)
	{
		if (ball->super->y > paddleRight->super->y + paddleRight->h && paddleRight->super->y + paddleRight->h < BOARD_HEIGHT)paddleRight->super->y+=2;
		else if(paddleRight->super->y > 0) paddleRight->super->y-=2;
	}

	if (ball->speedX > 0 && ball->super->x > BOARD_WIDTH * (4.0/5.0))
	{
		if (ball->super->y > paddleRight->super->y + paddleRight->h && paddleRight->super->y + paddleRight->h < BOARD_HEIGHT)paddleRight->super->y += 5;
		else if (paddleRight->super->y > 0) paddleRight->super->y -= 5;
	}

}