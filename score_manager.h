#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

void checkFileExist();
void checkScore(char gameName[10], int curGameScore);
void updateFile(char gameName[10], int curGameScore);
void updateTicTacToeScore(int winner);

#endif 