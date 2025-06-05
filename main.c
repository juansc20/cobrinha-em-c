#include <stdio.h>
#include <conio.h>   // Para _kbhit() e _getch()
#include <windows.h> // Para Sleep()

#define LARGURA 20
#define ALTURA 20

int x, y, frutaX, frutaY, pontuacao;
int gameOver;
int tamanhoCauda;
int caudaX[100], caudaY[100];
enum Direcao { STOP = 0, ESQUERDA, DIREITA, CIMA, BAIXO };
enum Direcao dir;

void setup() {
    gameOver = 0;
    dir = STOP;
    x = LARGURA / 2;
    y = ALTURA / 2;
    frutaX = rand() % LARGURA;
    frutaY = rand() % ALTURA;
    pontuacao = 0;
}

void desenhar() {
    system("cls");
    for (int i = 0; i < LARGURA + 2; i++) printf("#");
    printf("\n");

    for (int i = 0; i < ALTURA; i++) {
        for (int j = 0; j < LARGURA; j++) {
            if (j == 0) printf("#");

            if (i == y && j == x)
                printf("O"); // Cabeça da cobrinha
            else if (i == frutaY && j == frutaX)
                printf("F");
            else {
                int imp = 0;
                for (int k = 0; k < tamanhoCauda; k++) {
                    if (caudaX[k] == j && caudaY[k] == i) {
                        printf("o");
                        imp = 1;
                    }
                }
                if (!imp) printf(" ");
            }

            if (j == LARGURA - 1) printf("#");
        }
        printf("\n");
    }

    for (int i = 0; i < LARGURA + 2; i++) printf("#");
    printf("\nPontuação: %d\n", pontuacao);
}

void entrada() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': dir = ESQUERDA; break;
            case 'd': dir = DIREITA; break;
            case 'w': dir = CIMA; break;
            case 's': dir = BAIXO; break;
            case 'x': gameOver = 1; break;
        }
    }
}

void logica() {
    int prevX = caudaX[0];
    int prevY = caudaY[0];
    int prev2X, prev2Y;
    caudaX[0] = x;
    caudaY[0] = y;
    for (int i = 1; i < tamanhoCauda; i++) {
        prev2X = caudaX[i];
        prev2Y = caudaY[i];
        caudaX[i] = prevX;
        caudaY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case ESQUERDA: x--; break;
        case DIREITA: x++; break;
        case CIMA: y--; break;
        case BAIXO: y++; break;
        default: break;
    }

    if (x >= LARGURA || x < 0 || y >= ALTURA || y < 0)
        gameOver = 1;

    for (int i = 0; i < tamanhoCauda; i++)
        if (caudaX[i] == x && caudaY[i] == y)
            gameOver = 1;

    if (x == frutaX && y == frutaY) {
        pontuacao += 10;
        frutaX = rand() % LARGURA;
        frutaY = rand() % ALTURA;
        tamanhoCauda++;
    }
}

int main() {
    setup();
    while (!gameOver) {
        desenhar();
        entrada();
        logica();
        Sleep(100); // Velocidade do jogo
    }
    return 0;
}
