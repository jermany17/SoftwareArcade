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

typedef struct Snake { // create Snake
    struct Snake* front;
    struct Snake* back;
    COORD position;
    char direct;
} Snake;

Snake* head = NULL;
Snake* body = NULL;
Snake* tail = NULL;

int direction = 3;
int stage = 0;
int stageBestScore = 0;
int speed = 15;
int ballCount = 0;
int length = 3;
int minLength = 2;
int maxLength = 40;
int minSpeed = 5;
int maxSpeed = 25;
int speedScore = 50;
int currentScore = 0;

void stage1();

void initSnake();
void addBody();
void deleteBody();

COORD nextHeadPos();
void drawHead(COORD headPos);
void eraseTail();
Snake* getNode(Snake* front, Snake* back, COORD position);
int snakeMove();
void getSomething();

void inPlayKeyInput();
void shiftUp();
void shiftDown();
void shiftLeft();
void shiftRight();
void pausePlay();

int detectCollision(int currentPosX, int currentPosY);
int isGameOver();
void addBall();
void showBall(int arrX, int arrY);
void waitToRecover();

void countScore();

int snake() {
    console();
    removeCursor();

    while (1) {
        system("cls");
        //clearScreen();
        //reset();
        stage1();
    }
    getch();

	return 0;
}

void stage1() {
    drawBoard();
    initSnake();
    addBall();

    int key = 0;

    while (1) {
        if (isGameOver()) break;

        while (1) {
            if (snakeMove() == 0) break;

            inPlayKeyInput();
        }
    }
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

void addBody() {
    if (length + 1 > maxLength) return;

    length++;

    COORD newTailPos = { tail->position.X, tail->position.Y };

    switch (tail->direct) {
        case LEFT:
            newTailPos.X += 2; break;
        case RIGHT:
            newTailPos.X -= 2; break;
        case UP:
            newTailPos.Y++; break;
        case DOWN:
            newTailPos.Y--; break;
        default:
            break;
    }
    Snake* p = getNode(tail, NULL, newTailPos);
    p->direct = tail->direct;
    tail->back = p;
    tail = p;

    if (!detectCollision(tail->position.X, tail->position.Y)) {
        int arrX = (tail->position.X - GBOARD_ORIGIN_X) / 2;
        int arrY = tail->position.Y - GBOARD_ORIGIN_Y;
        gameBoardInfo[arrY][arrX] = 2;
    }
}

void deleteBody() {
    if (length > minLength) { // only runs when length is longer than the minimum length
        eraseTail();
        length--;
    }
}

COORD nextHeadPos() { // returns the next position of the head
    COORD curPos;
    curPos.X = head->position.X;
    curPos.Y = head->position.Y;

    switch (direction) {
        case 0:
            curPos.Y--;
            break;
        case 1:
            curPos.Y++;
            break;
        case 2:
            curPos.X -= 2;
            break;
        case 3:
            curPos.X += 2;
            break;
        default:
            break;
    }

    return curPos;
}

void drawHead(COORD headPos) { // adds a front node as Snake moves
    Snake* node = getNode(NULL, head, headPos);
    head->front = node;
    head = head->front;

    switch (direction) {
    case 0:
        head->direct = UP;
        break;
    case 1:
        head->direct = DOWN;
        break;
    case 2:
        head->direct = LEFT;
        break;
    case 3:
        head->direct = RIGHT;
        break;
    default:
        head->direct = UP;
        break;
    }

    setTextColor(15);

    gotoxy(head->position.X, head->position.Y, "¡Ý");
    gotoxy(head->back->position.X, head->back->position.Y, "¡Ü");

    getSomething();

    int arrX = (headPos.X - GBOARD_ORIGIN_X) / 2;
    int arrY = (headPos.Y - GBOARD_ORIGIN_Y);
    gameBoardInfo[arrY][arrX] = 2;
}

void eraseTail() { // erases end node as Snake moves
    if (tail == NULL) return;

    if (detectCollision(tail->position.X, tail->position.Y) == 2) {
        int arrX = (tail->position.X - GBOARD_ORIGIN_X) / 2;
        int arrY = (tail->position.Y - GBOARD_ORIGIN_Y);
        gameBoardInfo[arrY][arrX] = 0;

        COORD pos = { tail->position.X, tail->position.Y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
        printf("  ");
    }
    Snake* pi = tail;
    tail = tail->front;
    tail->back = NULL;
    free(pi);
}

Snake* getNode(Snake* front, Snake* back, COORD position) // create new Snake node
{
    Snake* node = (Snake*)malloc(sizeof(Snake));
    node->front = front;
    node->back = back;
    node->position = position;

    return node;
}

int snakeMove() {
    COORD nextPos = nextHeadPos();

    if (detectCollision(nextPos.X, nextPos.Y) == 1 || detectCollision(nextPos.X, nextPos.Y) == 2) {
        if (heart > 0) { // when lives are remaining
            waitToRecover();

            return 1;
        }
        else return 0;
    }

    if (detectCollision(nextPos.X, nextPos.Y) != 13) {
        drawHead(nextPos);      
        eraseTail();
    }

    return 1;
}

void getSomething() {
    //countScore();
}

void inPlayKeyInput() { // registers player input
    int i, key;
    int s = speed; if (stage == 5) s *= 2;
    for (i = 0; i < s; i++) {
        if (_kbhit() != 0) {
            key = _getch();
            switch (key)
                {
                case UP:
                    shiftUp();
                    break;
                case DOWN:
                    shiftDown();
                    break;
                case LEFT:
                    shiftLeft();
                    break;
                case RIGHT:
                    shiftRight();
                    break;
                case SPACE:
                    pausePlay();
                    break;
                default:
                    break;
            }
        }
        Sleep(15); // adjusts game play speed
    }
}

void shiftUp() { // when the up arrow key is pressed
    // checks for collision
    if (direction == 0 || direction == 1) return;

    COORD nextPos = nextHeadPos();

    if (detectCollision(nextPos.X, nextPos.Y) == 1) return;

    // updates the direction, redraws the head and the tail
    direction = 0;
    drawHead(nextPos);
    eraseTail();
}

void shiftDown() { // when the down arrow key is pressed
    if (direction == 0 || direction == 1) return;

    COORD nextPos = nextHeadPos();

    if (detectCollision(nextPos.X, nextPos.Y) == 1) return;

    direction = 1;
    drawHead(nextPos);
    eraseTail();
}

void shiftLeft() { // when the left arrow key is pressed
    if (direction == 2 || direction == 3) return;

    COORD nextPos = nextHeadPos();

    if (detectCollision(nextPos.X, nextPos.Y) == 1) return;

    direction = 2;
    drawHead(nextPos);
    eraseTail();
}

void shiftRight() { //when the right arrow key is pressed
    if (direction == 2 || direction == 3) return;

    COORD nextPos = nextHeadPos();

    if (detectCollision(nextPos.X, nextPos.Y) == 1) return;

    direction = 3;
    drawHead(nextPos);
    eraseTail();
}

void pausePlay() { // pauses game when space is pressed
    while (1) {
        if (_kbhit() != 0) {
            int key = _getch();

            if (key == SPACE) break;
        }
        Sleep(speed);
    }
}

int detectCollision(int posX, int posY) { // detects collision by inspecting next head position
    int arrX = (posX - GBOARD_ORIGIN_X) / 2;
    int arrY = (posY - GBOARD_ORIGIN_Y);

    return gameBoardInfo[arrY][arrX];
}


int isGameOver() { // game ends when detectCollision returns 1 or 2
    COORD nextPos = nextHeadPos();
    if (detectCollision(nextPos.X, nextPos.Y) == 1 || detectCollision(nextPos.X, nextPos.Y) == 2) return 1;
    return 0;
}

void addBall() {
    int ballX;
    int ballY;

    do {
        ballX = (rand() % GBOARD_WIDTH) + GBOARD_ORIGIN_X; if (ballX % 2 == 1) ballX++;
        ballY = (rand() % GBOARD_HEIGHT) + GBOARD_ORIGIN_Y;
    } while (detectCollision(ballX, ballY));

    int arrX = (ballX - GBOARD_ORIGIN_X) / 2;
    int arrY = (ballY - GBOARD_ORIGIN_Y);
    gameBoardInfo[arrY][arrX] = 3;
    showBall(ballX, ballY); ballCount++;
}

void showBall(int x, int y) {
    setTextColor(6);
    gotoxy(x, y, "¡Û");
    setTextColor(15);
}


void waitToRecover() {
    int key, flag = 0;
    gotoxycol(72, 23, 4, "PRESS TO CONTINUE!");
    Snake* p = head->back;
    COORD nextPos;

    //speedDown();

    for (int i = 0; i < 5; i++) {
        for (int i = 0; ; i++) {
            gotoxycol(p->position.X, p->position.Y, 15, "¡Û");
            gotoxycol(p->position.X, p->position.Y, 15, "¡Û");
            if (p->back == NULL) break;
            p = p->back;
        }
        Sleep(300);
        p = head->back;

        for (int i = 0; ; i++) {
            gotoxycol(p->position.X, p->position.Y, 15, "¡Ü");
            if (p->back == NULL) break;
            p = p->back;
        }
        Sleep(100);

        for (int i = 0; i < speed; i++) {
            if (_kbhit() != 0) {
                key = _getch();

                if (key == UP) {
                    if (direction == 0 || direction == 1) continue;
                    direction = 0;
                    nextPos = nextHeadPos();
                    drawHead(nextPos);
                    eraseTail();
                    flag = 1;
                }
                else if (key == DOWN) {
                    if (direction == 0 || direction == 1) continue;
                    direction = 1;
                    nextPos = nextHeadPos();
                    drawHead(nextPos);
                    eraseTail();
                    flag = 1;
                }
                else if (key == LEFT) {
                    if (direction == 2 || direction == 3) continue;
                    direction = 2;
                    nextPos = nextHeadPos();
                    drawHead(nextPos);
                    eraseTail();
                    flag = 1;
                }
                else if (key == RIGHT) {
                    if (direction == 2 || direction == 3) continue;
                    direction = 3;
                    nextPos = nextHeadPos();
                    drawHead(nextPos);
                    eraseTail();
                    flag = 1;
                }
                else if (key == SPACE) pausePlay();
            }
            Sleep(15); // adjust play speed
        }
        p = head->back;

        if (flag == 1) break;
    }
    heart--;
    drawLife();
    gotoxycol(72, 23, 14, "                   ");
    gotoxy(GBOARD_WIDTH + 3, GBOARD_HEIGHT + 5, "");
    setTextColor(15);

    if (flag == 0) return;
}