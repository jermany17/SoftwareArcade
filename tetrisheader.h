#pragma once

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

int score = 0;  // 현재 점수 
int best_score = 0; // 최고 점수

int main_block[23][11]; // 게임판 정보
int main_copy[23][11];  // 게임판 정보

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
                setCurrentCursorPos(2 * (3 + j), 1 + i);

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

void game_info(void) { // 게임 정보      
    int y = 3;
    setCurrentCursorPos(2 * 17, y + 6); printf("      SCORE : %6d", score);       // 현재 점수
    setCurrentCursorPos(2 * 17, y + 8); printf(" BEST SCORE : %6d", best_score);  // 최고 점수

    //조작법
    setCurrentCursorPos(2 * 17, y + 12); printf("  ↑   : 모양 바꾸기");
    setCurrentCursorPos(2 * 17, y + 13); printf("←   → : 블록 이동");
    setCurrentCursorPos(2 * 17, y + 14); printf("  ↓   : Soft Drop");
    setCurrentCursorPos(2 * 17, y + 15); printf("SPACE : Hard Drop");
    setCurrentCursorPos(2 * 17, y + 17); printf("P     : 일시정지");
    setCurrentCursorPos(2 * 17, y + 18); printf("ESC   : 종료");
}