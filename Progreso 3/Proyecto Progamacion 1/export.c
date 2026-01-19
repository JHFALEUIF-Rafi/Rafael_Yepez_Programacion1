#include <stdio.h>
#include <string.h>
#include "sga.h"

extern int predicciones_calculadas;

void req_exportarDatos(Zona zonas[]) {
    const char *filename = "Informe_Sterling_Enero2026.txt";
    FILE *f = fopen(filename, "w");
    if (!f) { printf("[ERROR] Fallo de escritura.\n"); return; }

    fprintf(f, "=================================================================================\n");
    fprintf(f, "               INFORME TECNICO SITUACION ATMOSFERICA NYC                         \n");
    fprintf(f, "=================================================================================\n");
    fprintf(f, "FECHA:           17 de Enero de 2026\n");
    fprintf(f, "AUTOR BASE:      Dr. Sterling (NYCCAS)\n");
    fprintf(f, "EMISIONES CO2e:  %s (Dato anualizado)\n", EMISIONES_CO2_NYC);
    fprintf(f, "NORMATIVA REF:   Guias OMS 2021 (PM2.5 < 5.0 | NO2 < 10.0 | SO2 < 40.0)\n");
    fprintf(f, "---------------------------------------------------------------------------------\n\n");

    if (!predicciones_calculadas) {
        fprintf(f, "[AVISO CRITICO DE SISTEMA]\n");
        fprintf(f, "  - La simulacion meteorologica NO se ha ejecutado.\n");
        fprintf(f, "  - Los valores predictivos y de 'Penalizacion Climatica' no estan disponibles.\n");
        fprintf(f, "  - Se recomienda ejecutar la Opcion 2 en el terminal para un analisis completo.\n\n");
    } else {
        fprintf(f, "[ESTADO DE SIMULACION]\n");
        fprintf(f, "  - Modelo predictivo: ACTIVO.\n");
        fprintf(f, "  - Factores considerados: Velocidad de viento, Humedad y Temperatura.\n\n");
    }

    fprintf(f, "DETALLE POR DISTRITO\n");
    fprintf(f, "====================\n");

    for(int i=0; i<NUM_ZONAS; i++) {
        fprintf(f, "ZONA %d: %s\n", i+1, zonas[i].nombre);
        fprintf(f, "Contexto Ambiental: %s\n", zonas[i].contexto);
        
        float exc_pm = ((zonas[i].actual.pm25 - LIMITE_PM25)/LIMITE_PM25)*100.0;
        float exc_no2 = ((zonas[i].actual.no2 - LIMITE_NO2)/LIMITE_NO2)*100.0;
        
        fprintf(f, "---------------------------------------------------------------------------------\n");
        fprintf(f, "1. NIVELES ACTUALES Y CUMPLIMIENTO OMS\n");
        fprintf(f, "   PARAMETRO | VALOR ACTUAL | LIMITE OMS | BRECHA (%%) | ESTADO\n");
        fprintf(f, "   PM2.5     | %6.2f       | 5.0        | %+6.1f%%    | %s\n", 
                zonas[i].actual.pm25, exc_pm, (exc_pm>0)?"INCUMPLE":"CUMPLE");
        fprintf(f, "   NO2       | %6.2f       | 10.0       | %+6.1f%%    | %s\n", 
                zonas[i].actual.no2, exc_no2, (exc_no2>0)?"INCUMPLE":"CUMPLE");
        fprintf(f, "   SO2       | %6.2f       | 40.0       | N/A        | CUMPLE (Minimos historicos)\n", 
                zonas[i].actual.so2);

        fprintf(f, "\n2. FACTOR METEOROLOGICO Y PREDICCION (24H)\n");
        if (predicciones_calculadas && zonas[i].clima_actual.velocidad_viento != -1) {
            fprintf(f, "   Condiciones Input: %s\n", zonas[i].clima_actual.interpretacion);
            fprintf(f, "   Temp: %.1f C | Viento: %.1f km/h | Humedad: %.0f%%\n", zonas[i].clima_actual.temperatura, zonas[i].clima_actual.velocidad_viento, zonas[i].clima_actual.humedad);
            fprintf(f, "   >> PROYECCION: PM2.5 %.2f | NO2 %.2f\n", zonas[i].prediccion_24h.pm25, zonas[i].prediccion_24h.no2);
        } else {
            fprintf(f, "   >> DATOS NO DISPONIBLES (Requiere ingreso manual de clima)\n");
        }

        fprintf(f, "\n3. ESTRATEGIA DE MITIGACION RECOMENDADA\n");
        fprintf(f, "   %s\n", zonas[i].recomendacion);
        fprintf(f, "\n#################################################################################\n\n");
    }

    fprintf(f, "NOTA ESPECIFICA SOBRE QUEENS:\n");
    fprintf(f, "Los datos mostrados corresponden al Oeste Industrial. Las zonas costeras (Rockaways)\n");
    fprintf(f, "registran valores significativamente menores (PM2.5 ~5.3, NO2 <10).\n");

    fclose(f);
    printf("\n[EXITO] Informe Meticuloso generado: '%s'\n", filename);
    printf("El archivo incluye analisis de brechas porcentuales y estrategias detalladas.\n");
}
