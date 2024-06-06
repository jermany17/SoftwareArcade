#include "score_manager.h"
#include <stdio.h>


void checkFileExist() {

    FILE* fp;
    fp = fopen("SOFTWAREARCADE_SCORE.txt", "r+");

    if (fp == NULL) {
        fp = fopen("SOFTWAREARCADE_SCORE.txt", "w");

        for (int i = 0; i < 10; i++) {          // 스네이크 게임 점수 초기화
            fputs("SNAKE 000000\n", fp);
        }
        for (int i = 0; i < 10; i++) {          // 테트리스 게임 점수 초기화
            fputs("TETRIS 000000\n", fp);
        }
        fputs("TICTACTOE 0 0 0\n", fp);                   // 틱택토 게임 승리/패배/무승부 초기화
        fclose(fp);
    }
    else
        fclose(fp);

}
