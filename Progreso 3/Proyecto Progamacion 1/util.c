#include <stdio.h>
#include <string.h>
#include "sga.h"

int seleccionarZona(Zona zonas[]) {
    printf("\nSeleccione Zona para Clima:\n");
    for(int i=0; i<NUM_ZONAS; i++) printf("  %d. %s\n", i+1, zonas[i].nombre);
    printf("  6. Volver\n");
    return solicitarEntero("Opcion: ", 1, 6) - 1;
}

float solicitarEntrada(const char *mensaje, float min, float max) {
    char buffer[BUFFER_SIZE];
    float val;
    do {
        printf("%s", mensaje);
        fgets(buffer, BUFFER_SIZE, stdin);
        if (sscanf(buffer, "%f", &val) == 1 && val >= min && val <= max) return val;
    } while (1);
}

int solicitarEntero(const char *mensaje, int min, int max) {
    char buffer[BUFFER_SIZE];
    int val;
    do {
        printf("%s", mensaje);
        fgets(buffer, BUFFER_SIZE, stdin);
        if (sscanf(buffer, "%d", &val) == 1 && val >= min && val <= max) return val;
    } while (1);
}

void esperarEnter() { printf("\n[ENTER] para continuar..."); getchar(); }
