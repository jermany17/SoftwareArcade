#pragma once

// size of gameboard
#define GBOARD_WIDTH 26
#define GBOARD_HEIGHT 18

// starting point of gameboard
#define GBOARD_ORIGIN_X 14
#define GBOARD_ORIGIN_Y 5

// size of controls board
#define CBOARD_WIDTH 8
#define CBOARD_HEIGHT 8

// starting point of controls board
#define CBOARD_ORIGIN_X 71
#define CBOARD_ORIGIN_Y 13

void printStage();
void printScore();
void printHighscore();
void drawLife();
void drawControls();
void drawKeys();
void clearScreen();

int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2];
int heart = 3; // maximum num of lives
int currentScore = 0;

char* gameName = "SNAKE";

void initGameBoardInfo() { // setting up boundaries
    for (int y = 0; y < GBOARD_HEIGHT; y++) {
        gameBoardInfo[y][0] = 1;
        gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
    }
    for (int x = 0; x < GBOARD_WIDTH + 2; x++) {
        gameBoardInfo[0][x] = 1;
        gameBoardInfo[GBOARD_HEIGHT][x] = 1;
    }
}

void resetGameBoardInfo() { // resetting boundaries
    for (int y = 1; y < GBOARD_HEIGHT; y++) {
        for (int x = 1; x < GBOARD_WIDTH; x++) {
            gameBoardInfo[y][x] = 0;
        }
    }
}

void drawBoard() {
    // game title
    gotoxycol(38, 2, 14, "SNAKE GAME");
    initGameBoardInfo();
    // draw game board
    for (int y = 0; y <= GBOARD_HEIGHT; y++) {
        if (y == 0) gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "〨");
        else if (y == GBOARD_HEIGHT) gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "〨");
        else gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "〨");

        if (y == 0) gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "〨");
        else if (y == GBOARD_HEIGHT) gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "〨");
        else gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "〨");
    }
    for (int x = 1; x < GBOARD_WIDTH + 1; x++) {
        gotoxycol(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y, 14, "〨");
        gotoxycol(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT, 14, "〨");
    }
    printStage();
    printScore();
    printHighscore();
    drawLife();
    drawControls();
    drawKeys();
}

void printStage() {
    gotoxycol(72, 5, 15, "Stage: Classic");
}

void printHighscore() {
    gotoxycol(72, 7, 15, "Highscore: ");
    setCurrentCursorPos(83, 7);
    //printf("%5d", stageBestScore[stage - 1]);
    // print Highscore after setting cursor position and calling from text file
}

void printScore() {
    gotoxycol(72, 9, 15, "Score: ");
    setCurrentCursorPos(83, 9);
    printf("%5d", currentScore);
    // print Score after setting cursor position
}

void drawLife() {
    gotoxycol(72, 11, 15, "Life:");
    gotoxycol(79, 11, 12, "");
    for (int i = 0; i < heart; i++) printf(" Ⅵ");
    for (int i = heart; i < 3; i++) printf(" Ⅴ");
}

void drawControls() { // draw controls board
    for (int y = 0; y <= CBOARD_HEIGHT; y++) {
        if (y == 0) gotoxycol(CBOARD_ORIGIN_X, CBOARD_ORIGIN_Y + y, 14, "旨");
        else if (y == CBOARD_HEIGHT) gotoxycol(CBOARD_ORIGIN_X, CBOARD_ORIGIN_Y + y, 14, "曲");
        else gotoxycol(CBOARD_ORIGIN_X, CBOARD_ORIGIN_Y + y, 14, "早");

        if (y == 0) gotoxycol(CBOARD_ORIGIN_X + (CBOARD_WIDTH + 1) * 2, CBOARD_ORIGIN_Y + y, 14, "旬");
        else if (y == CBOARD_HEIGHT) gotoxycol(CBOARD_ORIGIN_X + (CBOARD_WIDTH + 1) * 2, CBOARD_ORIGIN_Y + y, 14, "旭");
        else gotoxycol(CBOARD_ORIGIN_X + (CBOARD_WIDTH + 1) * 2, CBOARD_ORIGIN_Y + y, 14, "早");
    }
    for (int x = 1; x < CBOARD_WIDTH + 1; x++) {
        gotoxycol(CBOARD_ORIGIN_X + x * 2, CBOARD_ORIGIN_Y, 14, "收");
        gotoxycol(CBOARD_ORIGIN_X + x * 2, CBOARD_ORIGIN_Y + CBOARD_HEIGHT, 14, "收");
    }
}

void drawKeys() { 
    gotoxycol(77, 14, 14, "CONTROLS");
    gotoxycol(80, 16, 7, "∟");
    gotoxycol(78, 17, 7, "∠  ⊥");
    gotoxycol(80, 18, 7, "⊿");
    gotoxycol(73, 20, 7, "[SPACE] to STOP");
}

void clearScreen() {
    for (int y = 1; y <= GBOARD_HEIGHT - 1; y++) {
        for (int x = 1; x <= GBOARD_WIDTH; x++) {
            gotoxy(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + y, "  ");
        }
    }
}