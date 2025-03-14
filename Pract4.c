#include <stdio.h>
#include <stdlib.h>

// Función para comparar dos enteros (necesaria para qsort)
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int sumOfChemistry(int* skill, int skillSize) {
    // Ordenar el arreglo de habilidades
    qsort(skill, skillSize, sizeof(int), compare);
    
    // Calcular la suma total de habilidades
    int totalSum = 0;
    for (int i = 0; i < skillSize; i++) {
        totalSum += skill[i];
    }
    
    // Verificar si la suma total es divisible por el número de equipos
    int numTeams = skillSize / 2;
    if (totalSum % numTeams != 0) {
        return -1;
    }
    
    // Calcular la suma de química de todos los equipos
    int teamSum = totalSum / numTeams;
    int chemistrySum = 0;
    
    // Mostrar los equipos
    printf("Equipos formados:\n");
    for (int i = 0; i < numTeams; i++) {
        int low = skill[i];
        int high = skill[skillSize - 1 - i];
        
        // Verificar si la suma de habilidades de este equipo es igual a teamSum
        if (low + high != teamSum) {
            return -1;
        }
        
        // Mostrar el equipo
        printf("Equipo %d: (%d, %d)\n", i + 1, low, high);
        
        // Calcular la química de este equipo y sumarla
        chemistrySum += low * high;
    }
    
    return chemistrySum;
}

int main() {
    int skill[] = {3, 2, 5, 1, 3, 4};
    int skillSize = sizeof(skill) / sizeof(skill[0]);
    
    int result = sumOfChemistry(skill, skillSize);
    if (result == -1) {
        printf("No es posible dividir a los jugadores en equipos con la misma suma de habilidades.\n");
    } else {
        printf("Suma de la química de todos los equipos: %d\n", result); // Output: 22
    }
    
    return 0;
}