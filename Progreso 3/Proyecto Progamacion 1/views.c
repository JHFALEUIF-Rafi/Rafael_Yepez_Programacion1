#include <stdio.h>
#include <string.h>
#include "sga.h"

extern int predicciones_calculadas;

void req_monitoreoActual(Zona zonas[]) {
    printf("\n--- NIVELES ACTUALES (17 ENE 2026) ---\n");
    printf("%-20s | %-20s | PM2.5 (estado) | NO2 (estado)\n", "ZONA", "CONTEXTO");
    printf("--------------------------------------------------------------------------\n");
    for(int i=0; i<NUM_ZONAS; i++) {
        float exc_pm = ((zonas[i].actual.pm25 - LIMITE_PM25)/LIMITE_PM25)*100.0f;
        float exc_no2 = ((zonas[i].actual.no2 - LIMITE_NO2)/LIMITE_NO2)*100.0f;
        printf("%-20s | %-20.20s | %5.2f (%s) | %5.2f (%s)\n",
               zonas[i].nombre,
               zonas[i].contexto,
               zonas[i].actual.pm25,
               (exc_pm>0)?"INCUMPLE":"CUMPLE",
               zonas[i].actual.no2,
               (exc_no2>0)?"INCUMPLE":"CUMPLE");
    }
    printf("\n* Nota: SO2 se mantiene en cumplimiento total en todas las zonas.\n");
}

void req_mostrarAlertas(Zona zonas[]) {
    printf("\n--- TABLERO DE RIESGOS OMS ---\n");
    for(int i=0; i<NUM_ZONAS; i++) {
        float exc_pm = ((zonas[i].actual.pm25 - LIMITE_PM25)/LIMITE_PM25)*100.0f;
        float exc_no2 = ((zonas[i].actual.no2 - LIMITE_NO2)/LIMITE_NO2)*100.0f;

        printf("> %s:\n", zonas[i].nombre);
        if (exc_no2 > 100) printf("  [CRITICO] NO2 actual excede >100%% del limite (%+.0f%%). Causa: %s\n", exc_no2, zonas[i].contexto);
        else if (exc_no2 > 0) printf("  [ALERTA] NO2 actual fuera de norma (%+.0f%%).\n", exc_no2);
        if (exc_pm > 0) printf("  [ALERTA] PM2.5 actual fuera de norma (%+.0f%%).\n", exc_pm);
        if (exc_pm <=0 && exc_no2 <=0) printf("  [OK] Parametros actuales dentro de norma.\n");

        if (predicciones_calculadas && zonas[i].clima_actual.velocidad_viento != -1) {
            float exc_pm_pred = ((zonas[i].prediccion_24h.pm25 - LIMITE_PM25)/LIMITE_PM25)*100.0f;
            float exc_no2_pred = ((zonas[i].prediccion_24h.no2 - LIMITE_NO2)/LIMITE_NO2)*100.0f;
            if (exc_pm_pred > 0 || exc_no2_pred > 0) {
                printf("  [PREVENTIVA] Se preve exceder limites en 24h: PM2.5 %+.0f%%, NO2 %+.0f%%.\n", exc_pm_pred, exc_no2_pred);
            } else {
                printf("  [PROYECCION] Prediccion 24h dentro de norma.\n");
            }
        }
    }
}

void req_promediosHistoricos(Zona zonas[]) {
    printf("\n--- PROMEDIOS 30 DIAS VS OMS ---\n");
    printf("Limite Anual PM2.5: %.1f | Limite Anual NO2: %.1f\n", LIMITE_PM25, LIMITE_NO2);
    for(int i=0; i<NUM_ZONAS; i++) {
        float avg_pm=0, avg_no2=0;
        for(int d=0; d<DIAS_HISTORICOS; d++) {
            avg_pm += zonas[i].historico[d].pm25;
            avg_no2 += zonas[i].historico[d].no2;
        }
        avg_pm /= DIAS_HISTORICOS;
        avg_no2 /= DIAS_HISTORICOS;

        printf("%-20s | Promedio PM2.5: %.2f (%s) | Promedio NO2: %.2f (%s)\n",
            zonas[i].nombre,
            avg_pm, (avg_pm > LIMITE_PM25) ? "EXCEDE" : "CUMPLE",
            avg_no2, (avg_no2 > LIMITE_NO2) ? "EXCEDE" : "CUMPLE");
    }
}

void req_generarRecomendaciones(Zona zonas[]) {
    printf("\n--- ESTRATEGIAS DE MITIGACION ---\n");
    for(int i=0; i<NUM_ZONAS; i++) {
        int excede_actual_pm = (zonas[i].actual.pm25 > LIMITE_PM25);
        int excede_actual_no2 = (zonas[i].actual.no2 > LIMITE_NO2);
        int excede_pred_pm = 0, excede_pred_no2 = 0;
        if (predicciones_calculadas && zonas[i].clima_actual.velocidad_viento != -1) {
            excede_pred_pm = (zonas[i].prediccion_24h.pm25 > LIMITE_PM25);
            excede_pred_no2 = (zonas[i].prediccion_24h.no2 > LIMITE_NO2);
        }

        printf("ZONA: %s\n", zonas[i].nombre);
        printf("ACCION BASE: %s\n", zonas[i].recomendacion);
        if (excede_actual_pm || excede_pred_pm) {
            printf("ACCION ADICIONAL: Suspender actividades al aire libre y reforzar control de fuentes de particulas.\n");
        }
        if (excede_actual_no2 || excede_pred_no2) {
            printf("ACCION ADICIONAL: Reduccion de trafico vehicular y cierre temporal de industrias de alto NOx.\n");
        }
        if (!excede_actual_pm && !excede_pred_pm && !excede_actual_no2 && !excede_pred_no2) {
            printf("ACCION ADICIONAL: Mantener medidas actuales y monitoreo continuo.\n");
        }
        printf("\n");
    }
}
