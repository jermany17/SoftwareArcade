#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

// size of gameboard
#define GBOARD_WIDTH 12
#define GBOARD_HEIGHT 12

// starting point of gameboard
#define GBOARD_ORIGIN_X 18
#define GBOARD_ORIGIN_Y 8


//GameState
#define COMPUTERWIN 3
#define PLAYERWIN 2
#define DRAW 1
#define PROGRESS 0

void initializeBoard(char board[]);
int getInputNumber();

void displayInputRetryMessage();
void displayDrawMessage();
void displayPlayerWinMessage();
void displayComputerWinMessage();

void computerTurn();
int checkGameState();
void clearScreen();
void printBoard();

void moveAndPrintChar(int x, int y, int col, char* c);
void gotoxycol(int x, int y, int col, char* s);
void gotoxytic(int x, int y);

char board[9] = { '1', '2', '3','4', '5', '6','7', '8', '9' };

int tictactoe() {
    
    int inputNumber;
    int isGameRunning = 1;
    int checkState;

    while (isGameRunning) {
        printBoard();
        gotoxytic(48, 14);
        printf("                                                                ");
        gotoxytic(55, 14);
        printf(" 숫자를 입력해주세요: ");

        inputNumber = getInputNumber();
        gotoxytic(78, 14);
        printf("%d", inputNumber);
        Sleep(500);


        if (board[inputNumber - 1] != 'X' && board[inputNumber - 1] != 'O') {

            board[inputNumber - 1] = 'X';

            checkState = checkGameState();

            if (checkState == DRAW) {
                displayDrawMessage();
                updateTicTacToeScore("TICTACTOE", 2);
                break;
            }
            else if (checkState == PLAYERWIN) {
                displayPlayerWinMessage();
                updateTicTacToeScore("TICTACTOE", 0);
                break;
            }
            else if (checkState == COMPUTERWIN) {
                displayComputerWinMessage();
                updateTicTacToeScore("TICTACTOE", 1);
                break;
            }

        }
        else {
            displayInputRetryMessage();
            continue;
        }

        computerTurn();

        checkState = checkGameState();


        if (checkState == DRAW) {
            displayDrawMessage();
            updateTicTacToeScore("TICTACTOE", 2);
            break;
        }

        else if (checkState == PLAYERWIN) {
            displayPlayerWinMessage();
            updateTicTacToeScore("TICTACTOE", 0);
            break;
        }

        else if (checkState == COMPUTERWIN) {
            displayComputerWinMessage();
            updateTicTacToeScore("TICTACTOE", 1);
            break;
        }

    }

    initializeBoard(board);

    return -1;
}


//board[]를 초기화하는 함수 
void initializeBoard(char board[]) {
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i; 
    }
}



//숫자 입력받는 함수
int getInputNumber() {
    while (1) {
        while (!_kbhit());

        char ch = _getch();

        if (ch >= '0' && ch <= '9') {
            return ch - '0';
        }
    }
}


//이미 입력된 숫자를 입력받았을 때 화면에 띄우는 함수
void displayInputRetryMessage() {

    printBoard();
    gotoxytic(48, 14);
    printf("이미 입력된 숫자입니다. 잠시 기다렸다가 다시입력해주세요.\n");
    Sleep(500);
}


//Player가 이겼을 때 화면에 띄우는 함수
void displayPlayerWinMessage() {
    printBoard();
    gotoxytic(55, 14);
    printf("Player가 이겼습니다!\n");
    Sleep(500);
}


//Computer가 이겼을 때 화면에 띄우는 함수
void displayComputerWinMessage() {
    printBoard();
    gotoxytic(55, 14);
    printf("Computer가 이겼습니다!\n");
    Sleep(500);
}


//비겼을 때 화면에 띄우는 함수
void displayDrawMessage() {
    printBoard();
    gotoxytic(48, 14);
    printf("                                                                ");
    gotoxytic(55, 14);
    printf("비겼습니다!\n");
    Sleep(500);
}


//x,y좌표 정하는 함수 
void gotoxytic(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//화면 지운 후에 현재 게임상황을 반영한 Board를 화면에 게시하는 함수
void printBoard() {

    clearScreen();

    // game title
    gotoxycol(45, 2, 14, "★ Tic Tac Toe ★");
    // draw game board
    for (int y = 0; y <= GBOARD_HEIGHT; y++) {
        if (y == 0) gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "★");
        else if (y == GBOARD_HEIGHT) gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "★");
        else {
            gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "★");
            gotoxycol(GBOARD_ORIGIN_X + 9, GBOARD_ORIGIN_Y + y, 14, "|");
            gotoxycol(GBOARD_ORIGIN_X + 18, GBOARD_ORIGIN_Y + y, 14, "|");
        }

        if (y == 0) gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "★");
        else if (y == GBOARD_HEIGHT) gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "★");
        else gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "★");
    }
    for (int x = 1; x < GBOARD_WIDTH + 1; x++) {
        gotoxycol(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y, 14, "★");
        gotoxycol(GBOARD_ORIGIN_X + x * 2, 12, 14, "-");
        gotoxycol(GBOARD_ORIGIN_X + x * 2, 16, 14, "-");
        gotoxycol(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT, 14, "★");
    }


    moveAndPrintChar(GBOARD_ORIGIN_X + 4, GBOARD_ORIGIN_Y + 2, 14, board[0]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 13, GBOARD_ORIGIN_Y + 2, 14, board[1]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 2, 14, board[2]);

    moveAndPrintChar(GBOARD_ORIGIN_X + 4, GBOARD_ORIGIN_Y + 6, 14, board[3]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 13, GBOARD_ORIGIN_Y + 6, 14, board[4]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 6, 14, board[5]);

    moveAndPrintChar(GBOARD_ORIGIN_X + 4, GBOARD_ORIGIN_Y + 10, 14, board[6]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 13, GBOARD_ORIGIN_Y + 10, 14, board[7]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 10, 14, board[8]);

}


//char 위치 정해서 화면에 출력하는 함수
void moveAndPrintChar(int x, int y, int col, char* c) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
    printf("%c", c);
}


//computer 차례일 때 실행되는 함수
void computerTurn() {


    if ((board[1] == 'X' && board[2] == 'X' || board[3] == 'X' && board[6] == 'X' || board[4] == 'X' && board[8] == 'X') &&
        board[0] != 'X' && board[0] != 'O') {
        board[0] = 'O';
    }
    else if ((board[0] == 'X' && board[2] == 'X' || board[4] == 'X' && board[7] == 'X') &&
        board[1] != 'X' && board[1] != 'O') {
        board[1] = 'O';
    }
    else if ((board[0] == 'X' && board[1] == 'X' || board[4] == 'X' && board[6] == 'X' || board[5] == 'X' && board[8] == 'X') &&
        board[2] != 'X' && board[2] != 'O') {
        board[2] = 'O';
    }
    else if ((board[0] == 'X' && board[6] == 'X' || board[4] == 'X' && board[5] == 'X') &&
        board[3] != 'X' && board[3] != 'O') {
        board[3] = 'O';
    }
    else if ((board[0] == 'X' && board[8] == 'X' || board[2] == 'X' && board[6] == 'X' || board[1] == 'X' && board[7] == 'X' || board[3] == 'X' && board[5] == 'X') &&
        board[4] != 'X' && board[4] != 'O') {
        board[4] = 'O';
    }
    else if ((board[3] == 'X' && board[4] == 'X' || board[2] == 'X' && board[8] == 'X') &&
        board[5] != 'X' && board[5] != 'O') {
        board[5] = 'O';
    }
    else if ((board[0] == 'X' && board[3] == 'X' || board[2] == 'X' && board[4] == 'X' || board[7] == 'X' && board[8] == 'X') &&
        board[6] != 'X' && board[6] != 'O') {
        board[6] = 'O';
    }
    else if ((board[1] == 'X' && board[4] == 'X' || board[6] == 'X' && board[8] == 'X') &&
        board[7] != 'X' && board[7] != 'O') {
        board[7] = 'O';
    }
    else if ((board[0] == 'X' && board[4] == 'X' || board[2] == 'X' && board[5] == 'X' || board[6] == 'X' && board[7] == 'X') &&
        board[8] != 'X' && board[8] != 'O') {
        board[8] = 'O';
    }
    else {

        while (1) {
            int randomNubmer = rand() % 8;
            if (board[randomNubmer] != 'X' && board[randomNubmer] != 'O') {
                board[randomNubmer] = 'O';
                break;
            }
        }

    }

}


//게임상황을 나타내는 함수
int checkGameState() {

    int i = 0;

    for (i = 0;i < 9;i += 3) {
        if (board[i] == board[i + 1] && board[i + 1] == board[i + 2]) {
            if (board[i] == 'X') {
                return PLAYERWIN;
            }
            return COMPUTERWIN;
        }
    }

    for (i = 0;i < 9;i++) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            if (board[i] == 'X') {
                return PLAYERWIN;
            }
            return COMPUTERWIN;
        }
    }


    if ((board[0] == board[4] && board[4] == board[8]) ||
        (board[2] == board[4] && board[4] == board[6])) {
        if (board[4] == 'X') {
            return PLAYERWIN;
        }
        return COMPUTERWIN;
    }


    for (int i = 0;i < 9;i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return PROGRESS;
        }
    }

    return DRAW;
}

