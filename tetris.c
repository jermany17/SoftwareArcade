#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "tetrisheader.h"

int tetris() {
    int i;
    srand((unsigned)time(NULL));
    removeCursor(); //Ŀ���� ���� 
    firsttitle(); // ù ȭ�� 
    system("cls");
    reset_main_block(); // ���� ��� �ʱ�ȭ
    draw_main_block(); // ���� ��� �׸���
	return 0;
}