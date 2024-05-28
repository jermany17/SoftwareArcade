#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#include "console.h"
#include "snakeMap.h" // map related functions

// user controls
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define GB 120 // x for go back

typedef struct Snake { // create Snake
    struct Snake* front;
    struct Snake* back;
    COORD position;
    char direct;
} Snake;

Snake* head = NULL;
Snake* body = NULL;
Snake* tail = NULL;

void initSnake();

int snake() {
    drawBoard();

	return 0;
}

void initSnake() {

    COORD headPos = { GBOARD_ORIGIN_X + GBOARD_WIDTH , GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2 };
    COORD bodyPos = { GBOARD_ORIGIN_X + GBOARD_WIDTH - 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2 };
    COORD tailPos = { GBOARD_ORIGIN_X + GBOARD_WIDTH - 4, GBOARD_ORIGIN_Y + GBOARD_HEIGHT / 2 };

    head = getNode(NULL, NULL, headPos);
    body = getNode(NULL, NULL, bodyPos);
    tail = getNode(NULL, NULL, tailPos);

    head->back = body;
    body->front = head;
    body->back = tail;
    tail->front = body;

    head->direct = RIGHT;
    body->direct = RIGHT;
    tail->direct = RIGHT;

    int arrX = (head->position.X - GBOARD_ORIGIN_X) / 2;
    int arrY = head->position.Y - GBOARD_ORIGIN_Y;
    gameBoardInfo[arrY][arrX] = 2;
    gameBoardInfo[arrY][arrX - 1] = 2;
    gameBoardInfo[arrY][arrX - 2] = 2;

    gotoxy(head->position.X, head->position.Y, "¡Ý");
    gotoxy(body->position.X, body->position.Y, "¡Ü");
    gotoxy(tail->position.X, tail->position.Y, "¡Ü");
}

