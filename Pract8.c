#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Función auxiliar para duplicar los primeros n caracteres de una cadena
char *duplicarSubcadena(const char *cadena, int n) {
    char *nueva = (char *)malloc(n + 1); // +1 para el carácter nulo
    if (nueva == NULL) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }
    strncpy(nueva, cadena, n);
    nueva[n] = '\0'; // Aseguramos el final de la cadena
    return nueva;
}

// Verifica si las cadenas tienen los mismos caracteres con las mismas frecuencias
bool mismasFrecuencias(const char *s1, const char *s2, int len) {
    int cuenta[26] = {0};
    for (int i = 0; i < len; i++) {
        cuenta[s1[i] - 'a']++;
        cuenta[s2[i] - 'a']--;
    }
    for (int i = 0; i < 26; i++) {
        if (cuenta[i] != 0) return false;
    }
    return true;
}

// Función principal para verificar si s2 es una cadena revuelta de s1
bool esRevuelta(const char *s1, const char *s2) {
    int len = strlen(s1);
    if (len != strlen(s2)) return false;
    if (strcmp(s1, s2) == 0) return true;
    if (!mismasFrecuencias(s1, s2, len)) return false;

    for (int i = 1; i < len; i++) {
        // Dividir s1
        char *s1_izq = duplicarSubcadena(s1, i);
        char *s1_der = duplicarSubcadena(s1 + i, len - i);

        // Dividir s2 sin swap
        char *s2_izq = duplicarSubcadena(s2, i);
        char *s2_der = duplicarSubcadena(s2 + i, len - i);

        if (esRevuelta(s1_izq, s2_izq) && esRevuelta(s1_der, s2_der)) {
            free(s1_izq); free(s1_der); free(s2_izq); free(s2_der);
            return true;
        }

        // Dividir s2 con swap
        char *s2_izq_swap = duplicarSubcadena(s2 + len - i, i);
        char *s2_der_swap = duplicarSubcadena(s2, len - i);

        if (esRevuelta(s1_izq, s2_izq_swap) && esRevuelta(s1_der, s2_der_swap)) {
            free(s1_izq); free(s1_der); free(s2_izq); free(s2_der);
            free(s2_izq_swap); free(s2_der_swap);
            return true;
        }

        // Liberar memoria
        free(s1_izq); free(s1_der);
        free(s2_izq); free(s2_der);
        free(s2_izq_swap); free(s2_der_swap);
    }

    return false;
}

// Función principal
int main() {
    char s1[31], s2[31];

    printf("Ingrese la primera cadena (s1): ");
    scanf("%30s", s1);

    printf("Ingrese la segunda cadena (s2): ");
    scanf("%30s", s2);

    if (esRevuelta(s1, s2)) {
        printf("La cadena '%s' ES una cadena revuelta de '%s'.\n", s2, s1);
    } else {
        printf("La cadena '%s' NO es una cadena revuelta de '%s'.\n", s2, s1);
    }

    return 0;
}
