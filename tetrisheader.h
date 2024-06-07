#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "BlockModel.h"

int posX, posY; // 커서 위치
#define GBOARD_WIDTH 10   // 게임 보드의 너비
#define GBOARD_HEIGHT 20  // 게임 보드의 높이
#define GBOARD_ORIGIN_X 4 // 게임 보드의 x축
#define GBOARD_ORIGIN_Y 2 // 게임 보드의 y축

#define LEFT 75   // LEFT 키
#define RIGHT 77  // RIGHT 키
#define UP 72 // UP 키
#define DOWN 80 // DOWN 키
#define SPACE 32 // SPACE 키

int block_id;
int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2]; // 게임 보드 상태
void ShowBlock(char blockInfo[4][4]);   // 블록을 화면에 표시하는 함수                      
void DeleteBlock(char blockInfo[4][4]); // 화면에서 블록을 지우는 함수                      
void DrawGameBoard(); // 게임 보드를 그리는 함수
int DetectCollision(int PosX, int PosY, char blockModel[4][4]); // 충돌을 감지하는 함수 
void ShiftRight(void); // 블록을 오른쪽으로 이동시키는 함수
void ShiftLeft(void);  // 블록을 왼쪽으로 이동시키는 함수
int BlockDown();       // 블록을 아래로 한 칸 이동시키는 함수
void RotateBlock();    // 블록을 회전시키는 함수
void SpaceDown();      // 블록을 바닥까지 한 번에 내리는 함수

int speed; //  속도
void ProcessKeyInput(); // 키 입력을 처리하는 함수
int IsGameOver(void); // 게임 오버 여부를 확인하는 함수
void RedrawBlocks(void); // 게임 보드를 다시 그리는 함수
void AddBlockToBoard(void); // 현재 블록을 게임 보드에 추가하는 함수
void RemoveFillUpLine(void); // 가득 찬 줄을 제거하는 함수

int score = 0, best_score = 0; // 게임 점수, 최고 점수
char* gameName = "TETRIS";

void ShowBlock(char blockInfo[4][4]) // 블록을 화면에 표시하는 함수
{
	int x, y;
	COORD curPos = getCurrentCursorPos2(); // 현재 커서 위치
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			setCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y); // 해당 좌표로 커서 이동
			if (blockInfo[y][x] == 1) // 블록이 있으면
				printf("■");          // 블록 표시
		}
	}
	setCurrentCursorPos(curPos.X, curPos.Y); // 원래 위치로 커서 이동
}
void DeleteBlock(char blockInfo[4][4]) // 화면에서 블록을 지우는 함수
{
	int x, y;
	COORD curPos = getCurrentCursorPos2(); // 현재 커서 위치
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			setCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y); // 해당 좌표로 커서 이동
			if (blockInfo[y][x] == 1) // 블록이 있으면
				printf(" ");          // 블록 지움
		}
	}
	setCurrentCursorPos(curPos.X, curPos.Y); // 원래 위치로 커서 이동
}
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


int DetectCollision(int PosX, int PosY, char blockModel[4][4]) // 충돌을 감지하는 함수
{
	int X, Y;
	int arrX = (PosX - GBOARD_ORIGIN_X) / 2;
	int arrY = PosY - GBOARD_ORIGIN_Y;
	for (X = 0; X < 4; X++)
	{
		for (Y = 0; Y < 4; Y++)
		{
			if (blockModel[Y][X] == 1 && gameBoardInfo[arrY + Y][arrX + X] == 2)
				return 0; // 충돌하면 0 반환
		}
	}
	return 1; // 충돌하지 않으면 1 반환
}
void ShiftRight(void) // 블록을 오른쪽으로 이동시키는 함수
{
	if (DetectCollision(posX + 2, posY, blockModel[block_id]) == 0) { // 오른쪽 이동 가능한지 확인
		return; // 충돌하면 이동하지 않음
	}
	DeleteBlock(blockModel[block_id]); // 현재 블록 지움
	posX += 2;
	setCurrentCursorPos(posX, posY); // 커서 이동
	ShowBlock(blockModel[block_id]); // 블록 그리기
}
void ShiftLeft(void) // 블록을 왼쪽으로 이동시키는 함수
{
	if (DetectCollision(posX - 2, posY, blockModel[block_id]) == 0) { // 왼쪽 이동 가능한지 확인
		return; // 충돌하면 이동하지 않음
	}
	DeleteBlock(blockModel[block_id]); // 현재 블록 지움
	posX -= 2;
	setCurrentCursorPos(posX, posY); // 커서 이동
	ShowBlock(blockModel[block_id]); // 블록 그리기
}
int BlockDown() // 블록을 아래로 한 칸 이동시키는 함수
{
	if (!DetectCollision(posX, posY + 1, blockModel[block_id])) { // 아래 이동 가능 확인
		return 0;
	}
	DeleteBlock(blockModel[block_id]); // 현재 블록 지움
	posY += 1;
	setCurrentCursorPos(posX, posY); // 커서 이동
	ShowBlock(blockModel[block_id]); // 블록 그리기
	return 1; // 이동 성공 시 1 반환
}
void RotateBlock()  // 블록을 회전시키는 함수
{
	int block_base;
	block_base = block_id - block_id % 4;
	int block_rotated = block_base + (block_id + 1) % 4;
	if (!DetectCollision(posX, posY, blockModel[block_rotated])) { // 회전할 수 있는지 확인
		return 0; // 충돌하면 회전하지 않음
	}
	DeleteBlock(blockModel[block_id]); // 현재 블록 지움
	block_id = block_rotated;
	ShowBlock(blockModel[block_id]); // 회전된 블록을 그림
}
void SpaceDown()  // 블록을 바닥까지 한 번에 내리는 함수
{
	while (BlockDown()); // 블록이 더 이상 내려갈 수 없을 때까지 계속 내림
}

void ProcessKeyInput() // 키 입력을 처리하는 함수
{
	int i, key;
	for (i = 0; i < 20; i++)
	{
		if (_kbhit() != 0) // 키 입력이 있는지 확인
		{
			key = _getch(); // 키 입력을 받아옴
			switch (key)
			{
			case LEFT:  // 왼쪽 
				ShiftLeft();  // 블록 왼쪽 이동
				break;
			case RIGHT: // 오른쪽
				ShiftRight(); // 블록 오른쪽 이동
				break;
			case UP:    // 위
				RotateBlock(); // 블록 회전
				break;
			case DOWN:  // 아래
				if (DetectCollision(posX, posY + 1, blockModel[block_id])) // 블록이 한 칸 아래로 이동 가능한지 확인
				{
					DeleteBlock(blockModel[block_id]); // 현재 위치의 블록 지움
					posY += 1; // 블록의 Y 위치를 한 칸 아래로 이동
					setCurrentCursorPos(posX, posY); // 커서를 새로운 블록 위치로 이동
					ShowBlock(blockModel[block_id]); // 새로운 위치에 블록을 표시
				}
				break;
			case SPACE: // 스페이스바
				SpaceDown();   // 블록 하드 드롭
				break;
			}
		}
		Sleep(speed);
	}
}
int IsGameOver(void) // 게임 오버 여부를 확인하는 함수
{
	if (DetectCollision(posX, posY, blockModel[block_id]) == 1) // 충돌하지 않으면
	{
		return 1; // 게임 지속
	}
	else return 0; // 충돌하면 게임 종료
}
void RedrawBlocks(void) // 게임 보드를 다시 그리는 함수
{
	int x, y;
	int cursX, cursY;
	for (y = 0; y < GBOARD_HEIGHT; y++)
	{
		for (x = 1; x < GBOARD_WIDTH + 1; x++)
		{
			cursX = x * 2 + GBOARD_ORIGIN_X;
			cursY = y + GBOARD_ORIGIN_Y;
			setCurrentCursorPos(cursX, cursY); // 커서 이동
			if (gameBoardInfo[y][x] == 2)
			{
				printf("■"); // 블록 그리기
			}
			else { printf("  "); } // 빈 공간 그리기
		}
	}
}
void AddBlockToBoard(void) // 현재 블록을 게임 보드에 추가하는 함수
{
	int x, y, arrCurX, arrCurY;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)

		{
			arrCurX = (posX - GBOARD_ORIGIN_X) / 2;
			arrCurY = posY - GBOARD_ORIGIN_Y;

			if (blockModel[block_id][y][x] == 1) // 블록이 있는 부분을
				gameBoardInfo[arrCurY + y][arrCurX + x] = 2; // 게임 보드에 추가
		}
	}
}
void RemoveFillUpLine(void) // 가득 찬 줄을 제거하는 함수
{
	int line, x, y;
	for (y = GBOARD_HEIGHT - 1; y > 0; y--) {
		for (x = 1; x < GBOARD_WIDTH + 1; x++) {
			if (gameBoardInfo[y][x] != 2) // 가득 찬 줄에 빈 칸이 있으면
				break; // 검사 중단
		}
		if (x == (GBOARD_WIDTH + 1)) { // 한 줄이 가득 찬 경우
			score += 10;
			for (line = 0; y - line > 0; line++) {
				// 아래에서부터 줄을 당겨옴
				memcpy(&gameBoardInfo[y - line][1],
					&gameBoardInfo[(y - line) - 1][1], GBOARD_WIDTH * sizeof(int)); // 복사

			}
			y++; // 검사한 줄을 다시 검사
		}
	}
	// 블록 ID가 28인 경우(공백)
	if (block_id == 28) {
		int x, y;
		int arrCurX = (posX - GBOARD_ORIGIN_X) / 2;
		int arrCurY = posY - GBOARD_ORIGIN_Y;
		for (y = arrCurY; y < arrCurY + 4; y++) {
			for (x = 0; x < 4; x++) {
				gameBoardInfo[y][arrCurX + x] = 0; // 블록을 공백으로 설정
			}
		}
	}
	RedrawBlocks(); // 게임 보드 다시 그림
}