#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int esPotenciaDe2(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

int **asignarMatriz(int n) {
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        matrix[i] = (int *)calloc(n, sizeof(int));
    return matrix;
}

void liberarMatriz(int **matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

void llenar_Matriz(int **matrix, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = rand() % 10;
}

void sumar(int **A, int **B, int **result, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];
}

void restar(int **A, int **B, int **result, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];
}

void Mult_Strassen(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;

    int **A11 = asignarMatriz(half);
    int **A12 = asignarMatriz(half);
    int **A21 = asignarMatriz(half);
    int **A22 = asignarMatriz(half);
    int **B11 = asignarMatriz(half);
    int **B12 = asignarMatriz(half);
    int **B21 = asignarMatriz(half);
    int **B22 = asignarMatriz(half);
    int **C11 = asignarMatriz(half);
    int **C12 = asignarMatriz(half);
    int **C21 = asignarMatriz(half);
    int **C22 = asignarMatriz(half);
    int **M1 = asignarMatriz(half);
    int **M2 = asignarMatriz(half);
    int **M3 = asignarMatriz(half);
    int **M4 = asignarMatriz(half);
    int **M5 = asignarMatriz(half);
    int **M6 = asignarMatriz(half);
    int **M7 = asignarMatriz(half);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    int **temp1 = asignarMatriz(half);
    int **temp2 = asignarMatriz(half);

    sumar(A11, A22, temp1, half);
    sumar(B11, B22, temp2, half);
    Mult_Strassen
(temp1, temp2, M1, half);

    sumar(A21, A22, temp1, half);
    Mult_Strassen
(temp1, B11, M2, half);

    restar(B12, B22, temp2, half);
    Mult_Strassen
(A11, temp2, M3, half);

    restar(B21, B11, temp2, half);
    Mult_Strassen
(A22, temp2, M4, half);

    sumar(A11, A12, temp1, half);
    Mult_Strassen
(temp1, B22, M5, half);

    restar(A21, A11, temp1, half);
    sumar(B11, B12, temp2, half);
    Mult_Strassen
(temp1, temp2, M6, half);

    restar(A12, A22, temp1, half);
    sumar(B21, B22, temp2, half);
    Mult_Strassen
(temp1, temp2, M7, half);

    sumar(M1, M4, C11, half);
    restar(C11, M5, C11, half);
    sumar(C11, M7, C11, half);

    sumar(M3, M5, C12, half);

    sumar(M2, M4, C21, half);

    sumar(M1, M3, C22, half);
    restar(C22, M2, C22, half);
    sumar(C22, M6, C22, half);

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    liberarMatriz(A11, half); liberarMatriz(A12, half); liberarMatriz(A21, half); liberarMatriz(A22, half);
    liberarMatriz(B11, half); liberarMatriz(B12, half); liberarMatriz(B21, half); liberarMatriz(B22, half);
    liberarMatriz(C11, half); liberarMatriz(C12, half); liberarMatriz(C21, half); liberarMatriz(C22, half);
    liberarMatriz(M1, half); liberarMatriz(M2, half); liberarMatriz(M3, half); liberarMatriz(M4, half);
    liberarMatriz(M5, half); liberarMatriz(M6, half); liberarMatriz(M7, half);
    liberarMatriz(temp1, half); liberarMatriz(temp2, half);
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

    llenar_Matriz(A, n);
    llenar_Matriz(B, n);

    clock_t start = clock();
    Mult_Strassen
(A, B, C, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion (Strassen): %.4f segundos\n", time_taken);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}
