#include "score_manager.h"
#include <stdio.h>
#include <string.h>

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

void checkScore(char gameName[10], int curGameScore) {

    char savedGameName[10];
    int savedGameScore;

    FILE* file = fopen("game_scores.txt", "r");
    if (file == NULL) {
        printf("score file does not exist");
        exit(-1);
    }

    while (fscanf(file, "%s %d", savedGameName, &savedGameScore) != EOF) {
        if (strcmp(gameName, savedGameName) == 0 && curGameScore > savedGameScore) {
            fclose(file);
            updateScore(gameName, curGameScore);
            return;
        }
    }

    fclose(file);

}