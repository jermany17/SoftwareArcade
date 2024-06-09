#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#define LEFT 75
#define RIGHT 77
#define ENTER 13

void checkFileExist();
void checkScore(char* gameName, int curGameScore);
void updateFile(char* gameName, int curGameScore);
void updateTicTacToeScore(char* gameName, int winner);
int getHighestScore(char* gameName);

int ShowScoreBoard();
int printTotalScore(int curGameNum);
void printDiscription(int curGameNum);

#endif 