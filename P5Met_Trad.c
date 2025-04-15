#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int esPotenciaDe2(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

int **asignarMatriz(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *)calloc(n, sizeof(int));
    return matrix;
}

void llenarMatriz(int **matrix, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = rand() % 10;
}

void Mult_Trad(int **A, int **B, int **C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
}

void Liberar_Matriz(int **matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

int main() {
    int n;
    printf("Ingrese el tamano n de la matriz (n debe ser potencia de 2): ");
    scanf("%d", &n);

    if (!esPotenciaDe2(n)) {
        printf("Error: %d no es una potencia de 2.\n", n);
        return 1;
    }

    srand(time(NULL));
    int **A = asignarMatriz(n);
    int **B = asignarMatriz(n);
    int **C = asignarMatriz(n);

    llenarMatriz(A, n);
    llenarMatriz(B, n);

    clock_t start = clock();
    Mult_Trad(A, B, C, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %.4f segundos\n", time_taken);

    Liberar_Matriz(A, n);
    Liberar_Matriz(B, n);
    Liberar_Matriz(C, n);

    return 0;
}
