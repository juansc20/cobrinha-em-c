#include <stdio.h>
#include <conio.h>
#include <windows.h>

int x = 10, y = 10, frutaX = 15, frutaY = 15, score = 0;
int gameOver = 0, dir;

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw() {
    system("cls");
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            if (i == 0 || i == 19 || j == 0 || j == 19)
                printf("#");
            else if (i == y && j == x)
                printf("O");
            else if (i == frutaY && j == frutaX)
                printf("F");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("Pontuação: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = 1; break;
            case 'd': dir = 2; break;
            case 'w': dir = 3; break;
            case 's': dir = 4; break;
            case 'x': gameOver = 1; break;
        }
    }
}

void logic() {
    switch (dir) {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
    }
    if (x <= 0 || x >= 19 || y <= 0 || y >= 19)
        gameOver = 1;
    if (x == frutaX && y == frutaY) {
        score += 10;
        frutaX = rand() % 18 + 1;
        frutaY = rand() % 18 + 1;
    }
}

int main() {
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(100);
    }
    printf("Game Over!\n");
    return 0;
}
