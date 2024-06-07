#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "tetrisheader.h"

// gameBoardinfo[21][12];

int tetris() {
    
    posX = 12;
    posY = 0;
    speed = 30; // 블록 이동 속도
    score = 0;
    block_id = 0;
    
    int i, j;
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 12; j++) {
            gameBoardInfo[i][j] = 0;
        }
    }

    srand((unsigned int)time(NULL)); // 난수 생성
    removeCursor();  // 커서 제거
    DrawGameBoard(); // 게임 보드 그리기

    // 메인 게임 루프
    while (1) {
        if (IsGameOver() == 0) { // 게임 오버 확인
            break;
        }
        while (1)
        {
            if (BlockDown() == 0) // 블록이 더 이상 내려갈 수 없는 경우
            {
                AddBlockToBoard();  // 블록을 게임 보드에 추가
                RemoveFillUpLine(); // 가득 찬 줄 제거
                DrawGameBoard(); // 게임 보드 그리기
                break;
            }
            ProcessKeyInput(); // 키 입력 처리
        }
        // 새로운 블록 생성 위치
        posX = 6; posY = 2;
        block_id = (rand() % 7) * 4; // 새로운 블록 랜덤 생성
    }
    // 게임 오버 메시지 출력
    setCurrentCursorPos(11, 1);
    puts("GameOver");

    checkScore(tetrisGameName, score);

    Sleep(100);
    return -1;
}