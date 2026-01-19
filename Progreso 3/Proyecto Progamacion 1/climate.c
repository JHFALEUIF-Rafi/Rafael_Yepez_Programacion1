#include <stdio.h>
#include <string.h>
#include "sga.h"

extern int predicciones_calculadas;

void generarInterpretacionClimatica(Zona *z) {
    char temp_desc[50], viento_desc[50];
    
    if (z->clima_actual.temperatura > 30) strcpy(temp_desc, "Calor Extremo (Riesgo Ozono)");
    else if (z->clima_actual.temperatura > 20) strcpy(temp_desc, "Templado");
    else strcpy(temp_desc, "Frio");

    if (z->clima_actual.velocidad_viento < 5) strcpy(viento_desc, "Estancamiento de aire");
    else if (z->clima_actual.velocidad_viento > 15) strcpy(viento_desc, "Dispersion activa");
    else strcpy(viento_desc, "Ventilacion normal");

    sprintf(z->clima_actual.interpretacion, "%s con %s.", temp_desc, viento_desc);
}

void req_calcularPredicciones(Zona zonas[]) {
    printf("\n--- ANALISIS PREDICTIVO: PENALIZACION CLIMATICA ---\n");
    int id = seleccionarZona(zonas);
    if (id == 5) return;

    printf("\n[INPUT] Ingrese meteorologia para %s:\n", zonas[id].nombre);
    zonas[id].clima_actual.temperatura = solicitarEntrada("   > Temperatura (C): ", -30, 50);
    zonas[id].clima_actual.velocidad_viento = solicitarEntrada("   > Viento (km/h): ", 0, 150);
    zonas[id].clima_actual.humedad = solicitarEntrada("   > Humedad (%): ", 0, 100);

    generarInterpretacionClimatica(&zonas[id]);

    printf("\n[PROCESANDO] Calculando efectos atmosfericos...\n");

    for(int i=0; i<NUM_ZONAS; i++) {
        if(zonas[i].clima_actual.velocidad_viento == -1) continue;

        float factor = 1.0f;
        printf("   > Zona: %s\n", zonas[i].nombre);

        // 1. Efecto Viento
        if (zonas[i].clima_actual.velocidad_viento < 5.0f) {
            factor += 0.20f;
            printf("     - ALERTA: Estancamiento (+20%% concentracion).\n");
        } else if (zonas[i].clima_actual.velocidad_viento > 15.0f) {
            factor -= 0.15f;
            printf("     - INFO: Dispersion por viento (-15%% concentracion).\n");
        }

        // 2. Penalización Climática (Calor -> Reacciones Químicas)
        if (zonas[i].clima_actual.temperatura > 28.0f) {
            factor += 0.15f;
            printf("     - ALERTA: Penalizacion Climatica por calor (+15%%).\n");
        }

        // 3. Efecto Humedad
        if (zonas[i].clima_actual.humedad >= 80.0f) {
            factor += 0.10f;
            printf("     - ALERTA: Humedad alta (+10%% particulas y quimica secundaria).\n");
        } else if (zonas[i].clima_actual.humedad <= 30.0f) {
            factor -= 0.05f;
            printf("     - INFO: Humedad baja (-5%% formacion secundaria).\n");
        }

        float s_pm=0, s_no2=0, p_tot=0;
        for(int d=0; d<DIAS_HISTORICOS; d++) {
            float peso = (d >= DIAS_HISTORICOS-7) ? 2.0f : 1.0f;
            s_pm += zonas[i].historico[d].pm25 * peso;
            s_no2 += zonas[i].historico[d].no2 * peso;
            p_tot += peso;
        }

        zonas[i].prediccion_24h.pm25 = (s_pm/p_tot) * factor;
        zonas[i].prediccion_24h.no2 = (s_no2/p_tot) * factor;

        printf("     -> Resultado: PM2.5 %.2f | NO2 %.2f\n", zonas[i].prediccion_24h.pm25, zonas[i].prediccion_24h.no2);
    }
    predicciones_calculadas = 1;
}
