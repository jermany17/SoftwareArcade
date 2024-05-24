#pragma once

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

#define kbhit _kbhit   
#define getch _getch   

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE; // 커서를 숨김
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) { // 색상 지정
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void firsttitle(void) {
    int x = 5;  // 시작 화면이 표시되는 x좌표 
    int y = 4;  // 시작 화면이 표시되는 y좌표 

    int mintColor = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    // 제목
    setColor(mintColor);
    gotoxy(x, y + 0); printf("■■■■■■  ■■■■■■  ■■■■■■  ■■■■■■  ■■■■■■   ■■■■■"); Sleep(100);
    gotoxy(x, y + 1); printf("  ■■    ■■        ■■    ■■  ■■    ■■    ■■■"); Sleep(100);
    gotoxy(x, y + 2); printf("  ■■    ■■        ■■    ■■■■■■    ■■      ■■■"); Sleep(100);
    gotoxy(x, y + 3); printf("  ■■    ■■■■■■    ■■    ■■ ■■     ■■       ■■■"); Sleep(100);
    gotoxy(x, y + 4); printf("  ■■    ■■        ■■    ■■  ■■    ■■        ■■■"); Sleep(100);
    gotoxy(x, y + 5); printf("  ■■    ■■        ■■    ■■  ■■    ■■       ■■■"); Sleep(100);
    gotoxy(x, y + 6); printf("  ■■    ■■■■■■    ■■    ■■  ■■  ■■■■■■  ■■■■■"); Sleep(100);

    int defaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    setColor(defaultColor);
    gotoxy(x, y + 11); printf("게임을 시작하려면 아무키나 누르세요");
    gotoxy(x, y + 13); printf("P R E S S  A N Y  K E Y");
    while (kbhit()) getch(); // 저장된 키 값을 버림
}