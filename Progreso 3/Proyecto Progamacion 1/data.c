#include <stdio.h>
#include <string.h>
#include "sga.h"

void inicializarDatosSterling(Zona zonas[]) {
    // 1. MANHATTAN
    strcpy(zonas[0].nombre, "Manhattan (Midtown)");
    strcpy(zonas[0].contexto, "Efecto 'Canon Urbano'");
    zonas[0].actual.pm25 = 7.7; 
    zonas[0].actual.no2 = 27.0; 
    zonas[0].actual.so2 = 2.0;
    strcpy(zonas[0].recomendacion, "Descarbonizacion Residencial (Ley Local 97) y priorizar bombas de calor.");

    // 2. BRONX
    strcpy(zonas[1].nombre, "The Bronx (South)");
    strcpy(zonas[1].contexto, "Trafico pesado camiones diesel");
    zonas[1].actual.pm25 = 6.4; 
    zonas[1].actual.no2 = 20.0; 
    zonas[1].actual.so2 = 2.1;
    strcpy(zonas[1].recomendacion, "Expandir Zonas de Emisiones Ultra Bajas (ULEZ) y barreras vegetativas en Cross Bronx.");

    // 3. BROOKLYN
    strcpy(zonas[2].nombre, "Brooklyn (BQE)");
    strcpy(zonas[2].contexto, "Corredor BQE y Puentes");
    zonas[2].actual.pm25 = 6.4; 
    zonas[2].actual.no2 = 19.0;
    zonas[2].actual.so2 = 2.2;
    strcpy(zonas[2].recomendacion, "Infraestructura de filtrado natural en BQE y electrificacion 'Ultima Milla'.");

    // 4. QUEENS
    strcpy(zonas[3].nombre, "Queens (Industrial W)");
    strcpy(zonas[3].contexto, "Dualidad Industrial/Costera");
    zonas[3].actual.pm25 = 6.8; 
    zonas[3].actual.no2 = 16.5; 
    zonas[3].actual.so2 = 2.5;
    strcpy(zonas[3].recomendacion, "Rediseno logistico: Impedir nuevos centros de distribucion sin carga electrica.");

    // 5. STATEN ISLAND
    strcpy(zonas[4].nombre, "Staten Island");
    strcpy(zonas[4].contexto, "Residencial Moderado");
    zonas[4].actual.pm25 = 5.9; 
    zonas[4].actual.no2 = 11.0;
    zonas[4].actual.so2 = 1.5;
    strcpy(zonas[4].recomendacion, "Mantener cobertura de dosel arboreo (Objetivo 30%) para reducir islas de calor.");

    for (int i = 0; i < NUM_ZONAS; i++) {
        zonas[i].clima_actual.velocidad_viento = -1;
        strcpy(zonas[i].clima_actual.interpretacion, "Datos no ingresados");
        zonas[i].clima_actual.temperatura = 0;
        zonas[i].clima_actual.humedad = 0;

        for(int d=0; d<DIAS_HISTORICOS; d++) {
            float var = (d%2==0) ? 0.98f : 1.02f;
            zonas[i].historico[d].pm25 = zonas[i].actual.pm25 * var;
            zonas[i].historico[d].no2 = zonas[i].actual.no2 * var;
            zonas[i].historico[d].so2 = zonas[i].actual.so2;
        }
    }
}

void guardarHistorico(Zona zonas[]) {
    FILE *f = fopen("historico.csv", "w");
    if (!f) { printf("[ERROR] No se pudo guardar historico.csv\n"); return; }
    for (int i=0; i<NUM_ZONAS; i++) {
        for (int d=0; d<DIAS_HISTORICOS; d++) {
            fprintf(f, "%d,%d,%.3f,%.3f,%.3f\n", i, d,
                zonas[i].historico[d].pm25,
                zonas[i].historico[d].no2,
                zonas[i].historico[d].so2);
        }
    }
    fclose(f);
}

void cargarHistorico(Zona zonas[]) {
    FILE *f = fopen("historico.csv", "r");
    if (!f) return;
    int zi, di; float pm, no2, so2;
    while (fscanf(f, "%d,%d,%f,%f,%f", &zi, &di, &pm, &no2, &so2) == 5) {
        if (zi>=0 && zi<NUM_ZONAS && di>=0 && di<DIAS_HISTORICOS) {
            zonas[zi].historico[di].pm25 = pm;
            zonas[zi].historico[di].no2 = no2;
            zonas[zi].historico[di].so2 = so2;
        }
    }
    fclose(f);
}

void guardarPredicciones(Zona zonas[]) {
    FILE *f = fopen("predicciones.csv", "w");
    if (!f) { printf("[ERROR] No se pudo guardar predicciones.csv\n"); return; }
    for (int i=0; i<NUM_ZONAS; i++) {
        fprintf(f, "%d,%.3f,%.3f,%.3f\n", i,
            zonas[i].prediccion_24h.pm25,
            zonas[i].prediccion_24h.no2,
            zonas[i].prediccion_24h.so2);
    }
    fclose(f);
}
