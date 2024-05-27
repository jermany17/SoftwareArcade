#pragma once

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

int main_block[23][11]; // 게임판 정보
int main_copy[23][11];  // 게임판 정보







void firsttitle(void) { // 첫 화면 
    int x = 5;  // x좌표 
    int y = 4;  // y좌표 

    int mintColor = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 민트
    textcolor(mintColor); // 제목 색상 지정

    setCurrentCursorPos(2*x, y + 0); printf("■■■■■■  ■■■■■■  ■■■■■■  ■■■■■■  ■■■■■■   ■■■■■"); Sleep(100);
    setCurrentCursorPos(2*x, y + 1); printf("  ■■    ■■        ■■    ■■  ■■    ■■    ■■■"); Sleep(100);
    setCurrentCursorPos(2*x, y + 2); printf("  ■■    ■■        ■■    ■■■■■■    ■■      ■■■"); Sleep(100);
    setCurrentCursorPos(2*x, y + 3); printf("  ■■    ■■■■■■    ■■    ■■ ■■     ■■       ■■■"); Sleep(100);
    setCurrentCursorPos(2*x, y + 4); printf("  ■■    ■■        ■■    ■■  ■■    ■■        ■■■"); Sleep(100);
    setCurrentCursorPos(2*x, y + 5); printf("  ■■    ■■        ■■    ■■  ■■    ■■       ■■■"); Sleep(100);
    setCurrentCursorPos(2*x, y + 6); printf("  ■■    ■■■■■■    ■■    ■■  ■■  ■■■■■■  ■■■■■"); Sleep(100);

    int defaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    textcolor(defaultColor); // 안내 문구 색상 지정

    setCurrentCursorPos(x, y + 11); printf("게임을 시작하려면 아무키나 누르세요"); // 안내 문구(한글)
    setCurrentCursorPos(x, y + 13); printf("P R E S S  A N Y  K E Y"); // 안내 문구(ENG)
    while (_kbhit()) _getch(); // 모든 키 값을 버림

    _getch(); // 키 입력을 기다림
}

void reset_main_block(void) { // 메인 블록 초기화
    int i, j;

    for (i = 0; i < 23; i++) {       // 게임판 초기화  
        for (j = 0; j < 11; j++) {
            main_block[i][j] = 0;
            main_copy[i][j] = 100;
        }
    }
    for (j = 0; j < 11; j++) {      // 바닥
        main_block[23 - 1][j] = 1;
    }
    for (j = 1; j < 11; j++) {      // 천장 
        main_block[3][j] = -1;
    }
    for (i = 1; i < 23 - 1; i++) {  // 좌우
        main_block[i][0] = 1;
        main_block[i][11 - 1] = 1;
    }
}

void draw_main_block(void) { // 메인 블록 그리기
    int i, j;

    for (j = 1; j < 11 - 1; j++) { // 천장은 새로운블럭이 지나가면 다시 그려줌 
        if (main_block[3][j] == 0) main_block[3][j] = -1;
    }
    for (i = 0; i < 23; i++) {
        for (j = 0; j < 11; j++) {
            if (main_copy[i][j] != main_block[i][j]) {
                // mina_copy와 비교 후 값이 달라진 부분만 새로 그림

                int mintColor = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // 민트
                textcolor(mintColor);// 색상 지정
                setCurrentCursorPos(2*(3 + j), 1 + i);

                switch (main_block[i][j]) {
                case 0:  // 빈칸
                    printf("  ");
                    break;
                case -1: // 천장 
                    printf(". ");
                    break;
                case 1:  // 벽 
                    printf("▩");
                    break;
                case 2:  // 도착한 블럭  
                    printf("□");
                    break;
                case -2: // 움직이는 블럭  
                    printf("■");
                    break;
                }
            }
        }
        int defaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // 색상 원래대로
        textcolor(defaultColor); // 색상 지정
    }
    for (i = 0; i < 23; i++) { //게임판을 그린 후 main_cpy에 복사  
        for (j = 0; j < 11; j++) {
            main_copy[i][j] = main_block[i][j];
        }
    }
}