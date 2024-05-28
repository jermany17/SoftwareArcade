#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "tetrisheader.h"

int tetris() {
    srand((unsigned int)time(NULL)); // 난수 생성
    removeCursor();  // 커서 제거
    DrawGameBoard(); // 게임 보드 그리기
	return 0;
}