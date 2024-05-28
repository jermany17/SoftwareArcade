#pragma once

#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

int main_block[23][11]; // ������ ����
int main_copy[23][11];  // ������ ����







void firsttitle(void) { // ù ȭ�� 
    int x = 5;  // x��ǥ 
    int y = 4;  // y��ǥ 

    int mintColor = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // ��Ʈ
    textcolor(mintColor); // ���� ���� ����

    setCurrentCursorPos(2*x, y + 0); printf("�������  �������  �������  �������  �������   ������"); Sleep(100);
    setCurrentCursorPos(2*x, y + 1); printf("  ���    ���        ���    ���  ���    ���    ����"); Sleep(100);
    setCurrentCursorPos(2*x, y + 2); printf("  ���    ���        ���    �������    ���      ����"); Sleep(100);
    setCurrentCursorPos(2*x, y + 3); printf("  ���    �������    ���    ��� ���     ���       ����"); Sleep(100);
    setCurrentCursorPos(2*x, y + 4); printf("  ���    ���        ���    ���  ���    ���        ����"); Sleep(100);
    setCurrentCursorPos(2*x, y + 5); printf("  ���    ���        ���    ���  ���    ���       ����"); Sleep(100);
    setCurrentCursorPos(2*x, y + 6); printf("  ���    �������    ���    ���  ���  �������  ������"); Sleep(100);

    int defaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    textcolor(defaultColor); // �ȳ� ���� ���� ����

    setCurrentCursorPos(x, y + 11); printf("������ �����Ϸ��� �ƹ�Ű�� ��������"); // �ȳ� ����(�ѱ�)
    setCurrentCursorPos(x, y + 13); printf("P R E S S  A N Y  K E Y"); // �ȳ� ����(ENG)
    while (_kbhit()) _getch(); // ��� Ű ���� ����

    _getch(); // Ű �Է��� ��ٸ�
}

void reset_main_block(void) { // ���� ��� �ʱ�ȭ
    int i, j;

    for (i = 0; i < 23; i++) {       // ������ �ʱ�ȭ  
        for (j = 0; j < 11; j++) {
            main_block[i][j] = 0;
            main_copy[i][j] = 100;
        }
    }
    for (j = 0; j < 11; j++) {      // �ٴ�
        main_block[23 - 1][j] = 1;
    }
    for (j = 1; j < 11; j++) {      // õ�� 
        main_block[3][j] = -1;
    }
    for (i = 1; i < 23 - 1; i++) {  // �¿�
        main_block[i][0] = 1;
        main_block[i][11 - 1] = 1;
    }
}

void draw_main_block(void) { // ���� ��� �׸���
    int i, j;

    for (j = 1; j < 11 - 1; j++) { // õ���� ���ο���� �������� �ٽ� �׷��� 
        if (main_block[3][j] == 0) main_block[3][j] = -1;
    }
    for (i = 0; i < 23; i++) {
        for (j = 0; j < 11; j++) {
            if (main_copy[i][j] != main_block[i][j]) {
                // mina_copy�� �� �� ���� �޶��� �κи� ���� �׸�

                int mintColor = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY; // ��Ʈ
                textcolor(mintColor);// ���� ����
                setCurrentCursorPos(2*(3 + j), 1 + i);

                switch (main_block[i][j]) {
                case 0:  // ��ĭ
                    printf("  ");
                    break;
                case -1: // õ�� 
                    printf(". ");
                    break;
                case 1:  // �� 
                    printf("��");
                    break;
                case 2:  // ������ ��  
                    printf("��");
                    break;
                case -2: // �����̴� ��  
                    printf("��");
                    break;
                }
            }
        }
        int defaultColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; // ���� �������
        textcolor(defaultColor); // ���� ����
    }
    for (i = 0; i < 23; i++) { //�������� �׸� �� main_cpy�� ����  
        for (j = 0; j < 11; j++) {
            main_copy[i][j] = main_block[i][j];
        }
    }
}