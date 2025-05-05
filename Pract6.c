#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Autora: Orozco Barrientos Ana Raquel

bool esPrimo(int n);
void genFibonacci(int *fib, int *n, int K);
int minFibonacci(int *fib, int n, int K);

int main() {
    int dia, mes, anio;
    printf("Introduce tu fecha de nacimiento (DD MM AAAA): ");
    scanf("%d %d %d", &dia, &mes, &anio);

    // Paso 1: Calcular K
    int K = dia * 100 + mes * 10 + (anio % 100);
    printf("Valor de K calculado: %d\n", K);

    // Paso 2: Generar secuencia Fibonacci modificada
    int fib[100];
    int n = 0;
    genFibonacci(fib, &n, K);

    printf("Secuencia de Fibonacci filtrada (sin posiciones primas):\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    // Paso 3: Resolver usando estrategia voraz
    int numTerminos = minFibonacci(fib, n, K);
    printf("Numero minimo de terminos requeridos: %d\n", numTerminos);

    return 0;
}

bool esPrimo(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= (int)sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

void genFibonacci(int *fib, int *n, int K) {
    int a = 0, b = 1;
    int pos = 1;

    while (a <= K) {
        if (!esPrimo(pos)) {
            fib[*n] = a;
            (*n)++;
        }
        int temp = a + b;
        a = b;
        b = temp;
        pos++;
    }
}

int minFibonacci(int *fib, int n, int K) {
    int count = 0;
    int i = n - 1;

    while (K > 0) {
        if (fib[i] <= K) {
            K -= fib[i];
            count++;
        }
        i--;
    }

    return count;
}
