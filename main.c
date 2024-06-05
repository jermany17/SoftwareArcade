#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "score_manager.h"

enum ColorType {
    BLACK, darkBLUE, DarkGreen, darkSkyBlue, DarkRed,
    DarkPurple, DarkYellow, GRAY, DarkGray, BLUE,
    GREEN, SkyBlue, RED, PURPLE, YELLOW, WHITE
} COLOR; // 컬러 선택 할 수 있음

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13 

#define T_height 1
#define T_width 25 // 타이틀 시작 좌표
#define M_height 20
#define M_width 45 // 메뉴 시작 좌표
#define Title_Speed 35
const int M_num = 4;
int Selected_Menu_Num = 0; // 메뉴 넘버

void PrintTitle();
void PrintMenu(int n);
int SelectMenu();
void Delete_Menu();
void eraseTitle();
void textcolor(int color);
int todo = -1;

int main() {
    console(); // 콘솔 크기 지정
    removeCursor();

    database_init("game_scores.db");    // 데이터 베이스 확인 & 초기화

    while (1) {
        switch (todo) {
        case -1: // 시작화면
            todo = ShowTitle();
            system("cls"); // 화면 지우기
            break;
        case 0: // 스네이크 게임
            todo=snake();
            getch();
            system("cls");
            break;
        case 1: // 테트리스 게임
            todo=tetris();
            getch();
            system("cls");
            break;
        case 2: // 틱택토 게임
            todo=tictactoe();
            getch();
            system("cls");
            break;
        case 3: // 종료
            return 0;
        }
        system("cls");
        textcolor(WHITE);
    }

    system("cls");
    textcolor(WHITE);
    return 0;
}

int ShowTitle() {
    int select_m = -1;
    system("cls");
    while (select_m == -1) {
        textcolor(WHITE);
        PrintTitle();
        select_m = SelectMenu();
        if (select_m != -1)
            break;

        eraseTitle();
        textcolor(RED);
        PrintTitle();
        select_m = SelectMenu();
        eraseTitle();
    }
    return select_m;
}
void PrintTitle() {
    setCurrentCursorPos(T_width, T_height);
    printf("      _=====_                               _=====_\n");
    setCurrentCursorPos(T_width, T_height + 1);
    printf("     / _____ \\                             / _____ \\\n");
    setCurrentCursorPos(T_width, T_height + 2);
    printf("   +.-'_____'-.---------------------------.-'_____'-.+\n");
    setCurrentCursorPos(T_width, T_height + 3);
    printf("  /   |     |  '.                       .'  |  _  |   \\\n");
    setCurrentCursorPos(T_width, T_height + 4);
    printf(" / ___| /|\\ |___ \\                     / ___| /_\\ |___ \\\n");
    setCurrentCursorPos(T_width, T_height + 5);
    printf("/ |      |      | ;  __           _   ; | _         _ | ;\n");
    setCurrentCursorPos(T_width, T_height + 6);
    printf("| | <---   ---> | | |__|         |_:> | ||_|       (_)| |\n");
    setCurrentCursorPos(T_width, T_height + 7);
    printf("| |___   |   ___| ;SELECT       START ; |___       ___| ;\n");
    setCurrentCursorPos(T_width, T_height + 8);
    printf("|\\    | \\|/ |    /  _     ___      _   \\    | (X) |    /|\n");
    setCurrentCursorPos(T_width, T_height + 9);
    printf("| \\   |_____|  .','\" \"', |___|  ,'\" \"', '.  |_____|  .' |\n");
    setCurrentCursorPos(T_width, T_height + 10);
    printf("|  '-.______.-' /       \/RETRO/       \\  '-._____.-'   |\n");
    setCurrentCursorPos(T_width, T_height + 11);
    printf("|               |       |------|       |                |\n");
    setCurrentCursorPos(T_width, T_height + 12);
    printf("|              /\\       /      \\       /\\               |\n");
    setCurrentCursorPos(T_width, T_height + 13);
    printf("|             /  '.___.'        '.___.'  \\              |\n");
    setCurrentCursorPos(T_width, T_height + 14);
    printf("|            /                            \\             |\n");
    setCurrentCursorPos(T_width, T_height + 15);
    printf(" \\          /                              \\           /\n");
    setCurrentCursorPos(T_width, T_height + 16);
    printf("  \\________/                                \\_________/\n");
}


void PrintMenu(int n) {
    char MenuArr[4][10] = { "SNAKE", "TETRIS", "TICTACTOE", "EXIT " };
    // 각 게임 들어갈 수 있도록
    for (int i = 0; i < 4; i++) {
        if (n == i) {
            textcolor(darkSkyBlue);
            setCurrentCursorPos(M_width, M_height + i * 2);
            printf(">>"); // 화살표로 선택
        }
        else {
            textcolor(GRAY); 
        }

        setCurrentCursorPos(M_width + 4, M_height + i * 2);
        for (int j = 0; j < 10; j++)
            printf("%c", MenuArr[i][j]);
    }

    setCurrentCursorPos(M_width, M_height + n * 2);
    textcolor(darkSkyBlue);
    printf(">>");
}
int SelectMenu() {
    int key;
    int arrM[4] = { 0, 1, 2, 3 };
    PrintMenu(Selected_Menu_Num);

    while (1) {
        if (_kbhit()) {
            key = _getch();
            switch (key) {
            case DOWN:
                Delete_Menu();
                Selected_Menu_Num++; // 아래로 내리면 메뉴 넘버 up
                if (Selected_Menu_Num > M_num - 1) // 맨아래로 내렸을 경우 
                    Selected_Menu_Num = 0; // 맨위로
                PrintMenu(Selected_Menu_Num);
                break;
            case UP:
                Delete_Menu();
                Selected_Menu_Num--;
                if (Selected_Menu_Num < 0) //맨위로 올렸을 경우
                    Selected_Menu_Num = M_num - 1; // 가장 아래로
                PrintMenu(Selected_Menu_Num);
                break;
            case ENTER: // 엔터 치면 게임 선택
                return arrM[Selected_Menu_Num];
            }
        }
        Sleep(Title_Speed);
    }
}
void Delete_Menu() {
    for (int i = 0; i < 4; i++) {
        setCurrentCursorPos(M_width, M_height + i * 2);
        printf("                  ");
    }
}
void eraseTitle() {
    int n = 15;

    for (int i = 0; i < 7; i++) {
        setCurrentCursorPos(T_width + n, T_height + i);
        printf("                                              \n");
    }

    for (int i = 0; i < 7; i++) {
        setCurrentCursorPos(T_width, T_height + 8 + i);
        printf("                                                                     \n");
    }
}
