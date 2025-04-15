#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Verifica si n es potencia de 2
int esPotenciaDe2(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Asignar memoria para una matriz
int **asignarMtriz(int n) {
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

void llenarMatriz(int **matrix, int n) {
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

void DaC_Multiplicacion(int **A, int **B, int **C, int n) {
    if (n == 1) {
        C[0][0] += A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;

    // Submatrices
    int **A11 = asignarMtriz(half);
    int **A12 = asignarMtriz(half);
    int **A21 = asignarMtriz(half);
    int **A22 = asignarMtriz(half);
    int **B11 = asignarMtriz(half);
    int **B12 = asignarMtriz(half);
    int **B21 = asignarMtriz(half);
    int **B22 = asignarMtriz(half);
    int **C11 = asignarMtriz(half);
    int **C12 = asignarMtriz(half);
    int **C21 = asignarMtriz(half);
    int **C22 = asignarMtriz(half);

    // Dividir A y B
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

    // Temporales
    int **temp1 = asignarMtriz(half);
    int **temp2 = asignarMtriz(half);

    // C11 = A11*B11 + A12*B21
    DaC_Multiplicacion(A11, B11, temp1, half);
    DaC_Multiplicacion(A12, B21, temp2, half);
    sumar(temp1, temp2, C11, half);

    // C12 = A11*B12 + A12*B22
    for (int i = 0; i < half; i++) for (int j = 0; j < half; j++) temp1[i][j] = temp2[i][j] = 0;
    DaC_Multiplicacion(A11, B12, temp1, half);
    DaC_Multiplicacion(A12, B22, temp2, half);
    sumar(temp1, temp2, C12, half);

    // C21 = A21*B11 + A22*B21
    for (int i = 0; i < half; i++) for (int j = 0; j < half; j++) temp1[i][j] = temp2[i][j] = 0;
    DaC_Multiplicacion(A21, B11, temp1, half);
    DaC_Multiplicacion(A22, B21, temp2, half);
    sumar(temp1, temp2, C21, half);

    // C22 = A21*B12 + A22*B22
    for (int i = 0; i < half; i++) for (int j = 0; j < half; j++) temp1[i][j] = temp2[i][j] = 0;
    DaC_Multiplicacion(A21, B12, temp1, half);
    DaC_Multiplicacion(A22, B22, temp2, half);
    sumar(temp1, temp2, C22, half);

    // Combinar resultado en C
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half] = C12[i][j];
            C[i + half][j] = C21[i][j];
            C[i + half][j + half] = C22[i][j];
        }
    }

    // Liberar
    liberarMatriz(A11, half); liberarMatriz(A12, half); liberarMatriz(A21, half); liberarMatriz(A22, half);
    liberarMatriz(B11, half); liberarMatriz(B12, half); liberarMatriz(B21, half); liberarMatriz(B22, half);
    liberarMatriz(C11, half); liberarMatriz(C12, half); liberarMatriz(C21, half); liberarMatriz(C22, half);
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
    int **A = asignarMtriz(n);
    int **B = asignarMtriz(n);
    int **C = asignarMtriz(n);

    llenarMatriz(A, n);
    llenarMatriz(B, n);

    clock_t start = clock();
    DaC_Multiplicacion(A, B, C, n);
    clock_t end = clock();

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion: %.4f segundos\n", time_taken);

    liberarMatriz(A, n);
    liberarMatriz(B, n);
    liberarMatriz(C, n);

    return 0;
}
