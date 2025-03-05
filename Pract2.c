#include <stdio.h>
#include <limits.h> // Para INT_MAX e INT_MIN

int dividir(int dividendo, int divisor) {
    if (divisor == 0) {
        printf("Error: Division por cero.\n");
        return 0;
    }


    if (dividendo == INT_MIN && divisor == -1) {
        return INT_MAX;
    }

    int signo = ((dividendo < 0) ^ (divisor < 0)) ? -1 : 1;

    long long dividendoAbs = llabs((long long)dividendo);
    long long divisorAbs = llabs((long long)divisor);

    long long cociente = 0;
    while (dividendoAbs >= divisorAbs) {
        dividendoAbs -= divisorAbs;
        cociente++;
    }

    cociente = signo * cociente;
    if (cociente > INT_MAX) return INT_MAX;
    if (cociente < INT_MIN) return INT_MIN;

    return (int)cociente;
}

int main() {
    int dividendo, divisor;

    printf("Introduce el dividendo: ");
    scanf("%d", &dividendo);

    printf("Introduce el divisor: ");
    scanf("%d", &divisor);

    int resultado = dividir(dividendo, divisor);
    printf("El resultado de la division es: %d\n", resultado);

    return 0;
}