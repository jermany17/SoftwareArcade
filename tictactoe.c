#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

// size of gameboard
#define GBOARD_WIDTH 12
#define GBOARD_HEIGHT 12

// starting point of gameboard
#define GBOARD_ORIGIN_X 18
#define GBOARD_ORIGIN_Y 8

#define WIN 2
#define DRAW 1
#define PROGRESS 0

int checkGameState();
void printBoard();
void moveAndPrintChar(int x, int y, int col, char* c);

char board[9] = { '1', '2', '3','4', '5', '6','7', '8', '9' };

int tictactoe() {

    printBoard();

	return 0;
}

void printBoard() {
    // game title
    gotoxycol(45, 2, 14, "★ Tic Tac Toe ★");
    // draw game board
    for (int y = 0; y <= GBOARD_HEIGHT; y++) {
        if (y == 0) gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "★");
        else if (y == GBOARD_HEIGHT) gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "★");
        else {
            gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "★");
            gotoxycol(GBOARD_ORIGIN_X + 9, GBOARD_ORIGIN_Y + y, 14, "|");
            gotoxycol(GBOARD_ORIGIN_X + 18, GBOARD_ORIGIN_Y + y, 14, "|");
        }

        if (y == 0) gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "★");
        else if (y == GBOARD_HEIGHT) gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "★");
        else gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "★");
    }
    for (int x = 1; x < GBOARD_WIDTH + 1; x++) {
        gotoxycol(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y, 14, "★");
        gotoxycol(GBOARD_ORIGIN_X + x * 2, 12, 14, "-");
        gotoxycol(GBOARD_ORIGIN_X + x * 2, 16, 14, "-");
        gotoxycol(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT, 14, "★");
    }


    moveAndPrintChar(GBOARD_ORIGIN_X + 4, GBOARD_ORIGIN_Y + 2, 14, board[0]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 13, GBOARD_ORIGIN_Y + 2, 14, board[1]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 2, 14, board[2]);

    moveAndPrintChar(GBOARD_ORIGIN_X + 4, GBOARD_ORIGIN_Y + 6, 14, board[3]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 13, GBOARD_ORIGIN_Y + 6, 14, board[4]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 6, 14, board[5]);

    moveAndPrintChar(GBOARD_ORIGIN_X + 4, GBOARD_ORIGIN_Y + 10, 14, board[6]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 13, GBOARD_ORIGIN_Y + 10, 14, board[7]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 10, 14, board[8]);

}


void moveAndPrintChar(int x, int y, int col, char* c) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
    printf("%c", c);
}

void switchPlayer(int* player, char* mark) {
    if (*player == 1) {
        *mark = 'O';
        *player = 2;
    }
    else {
        *mark = 'X';
        *player = 1;
    }
}


int checkGameState() {

    //특정 Player가 이긴 상황

    for (int i = 0;i < 9;i += 3) {
        if (board[i] == board[i + 1] && board[i + 1] == board[i + 2]) {
            return WIN;
        }
    }

    for (int i = 0;i < 3;i++) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            return WIN;
        }
    }

    if ((board[0] == board[4] && board[4] == board[8]) ||
        (board[2] == board[4] && board[4] == board[6])) {
        return WIN;
    }

    //게임 진행 중인 상황
    for (int i = 0;i < 9;i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return PROGRESS;
        }
    }

    return DRAW;
}


