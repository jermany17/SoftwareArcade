#include "score_manager.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>
#pragma warning(disable:4996)

void setCPos(int x, int y) { // set current cursor position
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void checkFileExist() {

    FILE* fp;
    fp = fopen("SOFTWAREARCADE_SCORE.txt", "r+");

    if (fp == NULL) {
        fp = fopen("SOFTWAREARCADE_SCORE.txt", "w");

        for (int i = 0; i < 10; i++) {          // 스네이크 게임 점수 초기화
            fputs("SNAKE 0\n", fp);
        }
        for (int i = 0; i < 10; i++) {          // 테트리스 게임 점수 초기화
            fputs("TETRIS 0\n", fp);
        }
        fputs("TICTACTOE 0 0 0\n", fp);         // 틱택토 게임 승리/패배/무승부 초기화
        fclose(fp);
    }
    else
        fclose(fp);

}

void checkScore(char *gameName, int curGameScore) {

    char savedGameName[10];
    int savedGameScore;

    FILE* file = fopen("SOFTWAREARCADE_SCORE.txt", "r");
    if (file == NULL) {
        printf("score file does not exist\n");
        exit(-1);
    }

    while (fscanf(file, "%s %d", savedGameName, &savedGameScore) != EOF) {
        if (strcmp(gameName, savedGameName) == 0 && curGameScore > savedGameScore) {
            fclose(file);
            updateFile(gameName, curGameScore);
            return;
        }
    }

    fclose(file);
}

void updateFile(char *gameName, int newScore) {     // 기존 점수보다 높은 점수 파일에 추가

    FILE* fp = fopen("SOFTWAREARCADE_SCORE.txt", "r");
    FILE* tempFile = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("Could not open file");
        exit(-1);
    }

    char buffer[256];
    char name[10];
    int score;
    int tempScore = newScore;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        sscanf(buffer, "%s %d", name, &score);
        if (strcmp(name, gameName) == 0) {
            if (tempScore > score) {
                fprintf(tempFile, "%s %d\n", gameName, tempScore);
                tempScore = score;
            }
            else {
                fprintf(tempFile, "%s %d\n", name, score);
            }
        }
        else {
            fprintf(tempFile, "%s", buffer);
        }
    }

    fclose(fp);
    fclose(tempFile);

    remove("SOFTWAREARCADE_SCORE.txt");
    rename("temp.txt", "SOFTWAREARCADE_SCORE.txt");
}

int getHighestScore(char* gameName) {       // 입력받은 게임의 최고 점수 반환

    char savedGameName[10];
    int savedGameScore;

    FILE* file = fopen("SOFTWAREARCADE_SCORE.txt", "r");
    if (file == NULL) {
        printf("score file does not exist\n");
        exit(-1);
    }

    while (fscanf(file, "%s %d", savedGameName, &savedGameScore) != EOF) {
        if (strcmp(gameName, savedGameName) == 0) {
            fclose(file);
            return savedGameScore;
        }
    }

    fclose(file);
    return -1;

}

void updateTicTacToeScore(char *gameName, int winner) {

    char savedGameName[10];
    int computerS, playerS, drawnS;
    bool found = false;
    long pos;

    FILE* file = fopen("SOFTWAREARCADE_SCORE.txt", "r+");
    if (file == NULL) {
        printf("score file does not exist\n");
        exit(-1);
    }

    while (true) {
        pos = ftell(file);
        if (fscanf(file, "%s", savedGameName) != EOF) {
            if (strcmp(gameName, savedGameName) == 0) {

                found = true;
                fseek(file, pos, SEEK_SET); // 이전에 읽은 줄의 시작 위치로 이동
                fscanf(file, "%s %d %d %d", savedGameName, &playerS, &computerS, &drawnS);

                switch (winner) {
                case 0:
                    playerS++;
                    break;
                case 1:
                    computerS++;
                    break;
                case 2:
                    drawnS++;
                    break;
                default:
                    break;
                }
                fseek(file, pos, SEEK_SET);      // 파일 포인터 이전에 읽은 줄의 시작 위치로 설정

                fprintf(file, "\n%s %d %d %d\n", savedGameName, playerS, computerS, drawnS);
                fflush(file);
                break;
            }
        }
        else
            break;
    }

    fclose(file);

}


int ShowScoreBoard()
{

    int currentgameNum = 0;   

    printDiscription(currentgameNum);
    printTotalScore(currentgameNum);

    int key = 0;

    while (key != 13) {     // 스코어보드 내에서 좌우로 움직이며 게임 점수 확인
        if (_kbhit() != 0)
        {
            key = _getch();
            switch (key)
            {
            case LEFT:
                currentgameNum--;
                if (currentgameNum < 0)
                    currentgameNum += 3;
                printDiscription(currentgameNum);
                printTotalScore(currentgameNum);
                break;
            case RIGHT:
                currentgameNum++;
                if (currentgameNum > 2)
                    currentgameNum -= 3;
                printDiscription(currentgameNum);
                printTotalScore(currentgameNum);
                break;
            case ENTER:
                return -1;
                break;
            }
        }
    }


    return -1;

}

int printTotalScore(int curGameNum)      //순위, 점수, 이름 출력
{

    FILE* fp;
    fp = fopen("SOFTWAREARCADE_SCORE.txt", "r");
    if (fp == NULL) {
        printf("score file does not exist\n");
        return -1;
    }

    char gameName[50];
    int score1, score2, score3;
    char targetGame[50];

    switch (curGameNum) {      // curGameNum 값에 따라 출력할 게임 이름 설정
    case 0:
        strcpy(targetGame, "SNAKE");
        break;
    case 1:
        strcpy(targetGame, "TETRIS");
        break;
    case 2:
        strcpy(targetGame, "TICTACTOE");
        break;
    default:
        printf("Invalid game number\n");
        fclose(fp);
        return -1;
    }

    int x = 52, y = 8;
    int lineNum = 0;

    while (fscanf(fp, "%s", gameName) != EOF) {
        if (strcmp(gameName, targetGame) == 0) {
            if (curGameNum == 2) { // TICTACTOE의 경우 점수가 3개
                fscanf(fp, "%d %d %d", &score1, &score2, &score3);
                setCPos(x + 1, y + 2 * lineNum);
                printf("%d : %d", score1, score2);
                setCPos(x - 12, y + 2 * lineNum);
                printf("WIN");
                setCPos(x + 15, y + 2 * lineNum);
                printf("LOSE");

                setCPos(x + 1, y + 2 * lineNum + 4);
                printf("DRAWN");
                setCPos(x + 3, y + 2 * lineNum + 6);
                printf("%d", score3);
            }
            else { // SNAKE, TETRIS의 경우 점수 1개
                fscanf(fp, "%d", &score1);
                setCPos(x, y + 2 * lineNum);
                printf("%08d\n", score1);
            }
            lineNum++;
        }
        else {
            if (curGameNum == 2) { // 다른 게임 건너뛰기 위해 읽기
                fscanf(fp, "%d %d %d", &score1, &score2, &score3);
            }
            else {
                fscanf(fp, "%d", &score1);
            }
        }
    }

    

    fclose(fp);
}

void printDiscription(int curGameNum) {     // 점수를 제외한 스코어보드 출력

    system("cls");

    int Score_posX = 48;
    int Score_posY = 3;

    setCPos(Score_posX , Score_posY );
    printf("<< SCORE BOARD >>");;

    switch (curGameNum) {       // 게임 이름에 따라 다르게 출력
    case 0 :
        setCPos(Score_posX+3, Score_posY + 2);
        printf("SNAKE GAME");
        break;
    case 1:
        setCPos(Score_posX + 3, Score_posY + 2);
        printf("TETIRS GAME");
        break;
    case 2:
        setCPos(Score_posX + 3, Score_posY + 2);
        printf("TICTACTOE");
        break;
    }

    setCPos(Score_posX - 7, Score_posY + 26);
    printf("Press ENTER  to go to Main Menu");

    setCPos(10, Score_posY + 26);
    printf("<-");
    setCPos(98, Score_posY + 26);
    printf("->");

    return;
}