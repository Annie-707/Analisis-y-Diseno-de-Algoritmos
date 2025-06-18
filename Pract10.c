#include <stdio.h>

#define NUM_OBJETOS 4
#define PESO_MAXIMO 4

typedef struct {
    char nombre[10];
    int peso;
    int valor;
} Objeto;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    Objeto objetos[NUM_OBJETOS] = {
        {"Guitarra", 1, 1500},
        {"Estereo",  4, 3000},
        {"Laptop",   3, 2000},
        {"iPhone",   1, 2000}
    };

    int matriz[NUM_OBJETOS + 1][PESO_MAXIMO + 1];

    for (int i = 0; i <= NUM_OBJETOS; i++) {
        for (int w = 0; w <= PESO_MAXIMO; w++) {
            if (i == 0 || w == 0) {
                matriz[i][w] = 0;
            } else if (objetos[i - 1].peso <= w) {
                matriz[i][w] = max(
                    objetos[i - 1].valor + matriz[i - 1][w - objetos[i - 1].peso],
                    matriz[i - 1][w]
                );
            } else {
                matriz[i][w] = matriz[i - 1][w];
            }
        }
    }

    printf("Valor maximo: $%d\n", matriz[NUM_OBJETOS][PESO_MAXIMO]);

    int w = PESO_MAXIMO;
    printf("Objetos seleccionados:\n");
    for (int i = NUM_OBJETOS; i > 0 && w > 0; i--) {
        if (matriz[i][w] != matriz[i - 1][w]) {
            printf(" - %s\n", objetos[i - 1].nombre);
            w -= objetos[i - 1].peso;
        }
    }

    return 0;
}
