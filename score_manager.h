#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

void checkFileExist();
void checkScore(char* gameName, int curGameScore);
void updateFile(char* gameName, int curGameScore);
void updateTicTacToeScore(int winner);
int getHighestScore(char* gameName);

#endif 