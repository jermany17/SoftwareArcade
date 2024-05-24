#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

int main() {
	// snake 게임 시작
	console();
	removeCursor();
	snake();
	getch();
	// snake 끝

	system("cls"); // 콘솔 화면 지우기(다음 게임 이어서)

	// tetris 게임 시작
	tetris();
	getch();
	// tetris 끝

	return 0;
}