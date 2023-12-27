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
	ball->x += ball->speedX;
	ball->y += ball->speedY;

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
		switch (obj_tmp->type)
		{
		case GO_RECT:
		{
			gameObjectRect* obj = (gameObjectRect*)game->gameObjects[i];
			drawRect(obj->x, obj->y, obj->w, obj->h, obj->color, obj->depth, game->window);
			break;
		}
		case GO_CIRCLE:
		{
			gameObjectCircle* obj = (gameObjectCircle*)game->gameObjects[i];
			drawCircle(obj->x, obj->y, obj->r, 360, obj->color, obj->depth, game->window);
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
		obj1->x + obj1->r	> obj2->x &&
		obj1->x	- obj1->r	< obj2->x + obj2->w &&
		obj1->y + obj1->r	> obj2->y &&
		obj1->y - obj1->r	< obj2->y + obj2->h
		)
		return 1;
	return 0;
}

void checkPoint(Game* game)
{
	gameObjectCircle* ball = (gameObjectCircle*)game->gameObjects[BALL];
	gameObjectRect* paddleLeft = (gameObjectRect*)game->gameObjects[PADDLE_LEFT];
	gameObjectRect* paddleRight = (gameObjectRect*)game->gameObjects[PADDLE_RIGHT];

	if (ball->x - ball->r < paddleLeft->x)
	{
		ball->x = game->window->width / 2;
		ball->y = game->window->height / 2;
		game->computerPoints++;
		if (DEBUG)printf("USER %d : %d COMPUTER\n", game->userPoints, game->computerPoints);
	}
	else if (ball->x + ball->r > paddleRight->x + paddleRight->w)
	{
		ball->x = game->window->width / 2;
		ball->y = game->window->height / 2;
		game->userPoints++;
		if (DEBUG)printf("USER %d : %d COMPUTER\n", game->userPoints, game->computerPoints);

	}
}


int keyboardEvents(Game* game)
{
	gameObjectRect* paddleLeft = (gameObjectRect*)game->gameObjects[PADDLE_LEFT];
	if (game->window->keysPressed[VK_UP] && paddleLeft->y > 0)paddleLeft->y -= 5;
	if (game->window->keysPressed[VK_DOWN] && paddleLeft->y + paddleLeft->h < BOARD_HEIGHT)paddleLeft->y += 5;
}

void computerMove(Game* game)
{
	gameObjectCircle* ball = (gameObjectCircle*)game->gameObjects[BALL];
	gameObjectRect* paddleRight = (gameObjectRect*)game->gameObjects[PADDLE_RIGHT];

	if (ball->speedX > 0 && ball->x > BOARD_WIDTH / 2)
	{
		if (ball->y > paddleRight->y + paddleRight->h && paddleRight->y + paddleRight->h < BOARD_HEIGHT)paddleRight->y+=2;
		else if(paddleRight->y > 0) paddleRight->y-=2;
	}

	if (ball->speedX > 0 && ball->x > BOARD_WIDTH * (4.0/5.0))
	{
		if (ball->y > paddleRight->y + paddleRight->h && paddleRight->y + paddleRight->h < BOARD_HEIGHT)paddleRight->y += 5;
		else if (paddleRight->y > 0) paddleRight->y -= 5;
	}

}