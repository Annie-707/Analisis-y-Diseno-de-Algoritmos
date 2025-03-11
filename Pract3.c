#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMBINATIONS 1000

// Mapeo de dígitos a letras
const char* digitToLetters[] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

// Función recursiva para generar combinaciones
void backtrack(char* digits, int index, char* current, char** result, int* returnSize) {
    if (index == strlen(digits)) {
        current[index] = '\0'; // Terminar la cadena actual
        result[*returnSize] = strdup(current); // Guardar la combinación
        (*returnSize)++;
        return;
    }

    int digit = digits[index] - '0'; // Convertir carácter a entero
    const char* letters = digitToLetters[digit];

    for (int i = 0; letters[i] != '\0'; i++) {
        current[index] = letters[i]; // Elegir letra
        backtrack(digits, index + 1, current, result, returnSize); // Llamada recursiva
    }
}

char** letterCombinations(char* digits, int* returnSize) {
    if (digits == NULL || strlen(digits) == 0) {
        *returnSize = 0;
        return NULL;
    }

    char** result = (char**)malloc(MAX_COMBINATIONS * sizeof(char*));
    char* current = (char*)malloc((strlen(digits) + 1) * sizeof(char));
    *returnSize = 0;

    backtrack(digits, 0, current, result, returnSize);

    free(current);
    return result;
}

int main() {
    char digits[5]; // Hasta 4 dígitos + 1 para el terminador nulo
    printf("Ingrese los dígitos (2-9): ");
    scanf("%4s", digits); // Leer hasta 4 caracteres

    int returnSize;
    char** combinations = letterCombinations(digits, &returnSize);

    printf("Combinaciones posibles:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", combinations[i]);
        free(combinations[i]); // Liberar memoria de cada combinación
    }

    free(combinations); // Liberar memoria del arreglo de combinaciones
    return 0;
}