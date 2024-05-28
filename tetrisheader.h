#pragma once

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

#define GBOARD_WIDTH 10   // 게임 보드의 너비
#define GBOARD_HEIGHT 20  // 게임 보드의 높이
#define GBOARD_ORIGIN_X 4 // 게임 보드의 x축
#define GBOARD_ORIGIN_Y 2 // 게임 보드의 y축

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2]; // 게임 보드 상태
void DrawGameBoard(); // 게임 보드를 그리는 함수

int score = 0, best_score = 0; // 게임 점수, 최고 점수

void DrawGameBoard() { // 게임 보드를 그리는 함수
	int x, y;
	for (y = 0; y <= GBOARD_HEIGHT; y++) {
		setCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
		if (y == GBOARD_HEIGHT)
			printf("┗"); // 왼쪽 아래 모서리
		else
			printf("┃"); // 왼쪽 벽
	}
	for (y = 0; y <= GBOARD_HEIGHT; y++) {
		setCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
		if (y == GBOARD_HEIGHT)
			printf("┛"); // 오른쪽 아래 모서리
		else
			printf("┃"); // 오른쪽 벽
	}
	for (x = 1; x < GBOARD_WIDTH + 1; x++) {
		setCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		printf("━"); // 아래 벽
	}
	setCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH, 0);

	// 게임 보드 배열 초기화
	for (x = 0; x < GBOARD_WIDTH + 2; x++) {
		gameBoardInfo[GBOARD_HEIGHT][x] = 2; // 바닥을 2로 설정
	}
	for (y = 0; y < GBOARD_HEIGHT; y++) {
		gameBoardInfo[y][0] = 2;				// 왼쪽 벽을 2로 설정
		gameBoardInfo[y][GBOARD_WIDTH + 1] = 2; // 오른쪽 벽을 2로 설정
	}

	// 게임 정보, 조작 설명
	setCurrentCursorPos(34, 9);  printf("      SCORE : %6d", score);       // 현재 점수
	setCurrentCursorPos(34, 12); printf(" BEST SCORE : %6d", best_score);  // 최고 점수
	setCurrentCursorPos(34, 15); printf("  ↑   : 모양 바꾸기");
	setCurrentCursorPos(34, 16); printf("←   → : 블록 이동");
	setCurrentCursorPos(34, 17); printf("  ↓   : Soft Drop");
	setCurrentCursorPos(34, 18); printf("SPACE : Hard Drop");
}