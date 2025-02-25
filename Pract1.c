#include <stdio.h>

int Palindromo(int num, int *op)
{
    int original = num;
    int inv = 0;

    // Invierte el número
    while (num > 0) {
        int dig = num % 10; 
        inv = inv * 10 + dig;
        num = num / 10; 
        (*op) += 3; 
    }

    // Comparar el número original con el invertido
    (*op)++; 
    return original == inv;
}

int main() 
{
    int num;
    int op = 0;

    printf("Introduce un número entero: ");
    scanf("%d", &num);

    if (Palindromo(num, &op)) {
        printf("El número %d es un palíndromo.\n", num);
    } else {
        printf("El número %d no es un palíndromo.\n", num);
    }

    printf("Número de operaciones básicas realizadas: %d\n", op);

    return 0;
}