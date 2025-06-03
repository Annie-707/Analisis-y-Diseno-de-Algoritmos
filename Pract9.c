#include <stdio.h>
#include <stdlib.h>


int atraparAgua(int* altura, int tam) {
    if (tam <= 2) return 0;

    int* maxIzquierda = (int*)malloc(tam * sizeof(int));
    int* maxDerecha = (int*)malloc(tam * sizeof(int));
    int agua = 0;

    maxIzquierda[0] = altura[0];
    for (int i = 1; i < tam; i++) {
        maxIzquierda[i] = (altura[i] > maxIzquierda[i - 1]) ? altura[i] : maxIzquierda[i - 1];
    }

    maxDerecha[tam - 1] = altura[tam - 1];
    for (int i = tam - 2; i >= 0; i--) {
        maxDerecha[i] = (altura[i] > maxDerecha[i + 1]) ? altura[i] : maxDerecha[i + 1];
    }


    for (int i = 0; i < tam; i++) {
        int alturaMinima = (maxIzquierda[i] < maxDerecha[i]) ? maxIzquierda[i] : maxDerecha[i];
        if (alturaMinima > altura[i]) {
            agua += alturaMinima - altura[i];
        }
    }


    free(maxIzquierda);
    free(maxDerecha);

    return agua;
}

int main() {
    // Ejemplo 1
    int altura1[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    int tam1 = sizeof(altura1) / sizeof(altura1[0]);
    printf("Salida del Ejemplo 1: %d\n", atraparAgua(altura1, tam1)); // Esperado: 6

    // Ejemplo 2
    int altura2[] = {4,2,0,3,2,5};
    int tam2 = sizeof(altura2) / sizeof(altura2[0]);
    printf("Salida del Ejemplo 2: %d\n", atraparAgua(altura2, tam2)); // Esperado: 9

    return 0;
}
