#include <stdio.h>
#include <string.h>

// --- CONSTANTES ---
#define NUM_ZONAS 5
#define DIAS_HISTORICOS 30
#include "sga.h"

// Estado global
int predicciones_calculadas = 0;
int main() {
    Zona zonas[NUM_ZONAS];
    int opcion;

    // Carga inicial de datos duros del reporte
    inicializarDatosSterling(zonas);
    // Intentar cargar historico desde archivo si existe
    cargarHistorico(zonas);

    do {
        printf("\n\n"); 
        printf("=================================================================\n");
        printf(" SGA-NYC: MONITOREO AMBIENTAL INTEGRAL (INFORME STERLING 2026)   \n");
        printf(" Fecha de corte: 17 de Enero de 2026                             \n");
        printf(" Emisiones Globales: %s                 \n", EMISIONES_CO2_NYC);
        printf("=================================================================\n");
        printf(" 1. [Actual] Monitoreo Detallado por Region y Contexto\n");
        printf(" 2. [Prediccion] Analisis Climatico y 'Penalizacion Climatica'\n");
        printf(" 3. [Alertas] Tablero de Riesgos OMS\n");
        printf(" 4. [Historico] Tendencias vs Limites OMS (30 dias)\n");
        printf(" 5. [Mitigacion] Estrategias (ULEZ, Ley Local 97, etc.)\n");
        printf(" 6. [Informe] Generar Reporte Tecnico Meticuloso (TXT)\n");
        printf(" 7. Salir\n");
        printf("=================================================================\n");
        
        if (!predicciones_calculadas) {
            printf(" [!] AVISO: Predicciones climaticas NO calculadas. El informe sera parcial.\n");
        } else {
            printf(" [OK] SISTEMA LISTO: Datos climaticos procesados.\n");
        }

        opcion = solicitarEntero(">> Seleccione opcion: ", 1, 7);

        switch (opcion) {
            case 1: req_monitoreoActual(zonas); break;
            case 2: req_calcularPredicciones(zonas); break;
            case 3: req_mostrarAlertas(zonas); break;
            case 4: req_promediosHistoricos(zonas); break;
            case 5: req_generarRecomendaciones(zonas); break;
            case 6: req_exportarDatos(zonas); break;
            case 7:
                printf("\nGuardando registros y cerrando sistema...\n");
                guardarHistorico(zonas);
                if (predicciones_calculadas) guardarPredicciones(zonas);
                break;
        }
        if (opcion != 7) esperarEnter();

    } while (opcion != 7);

    return 0;
}

// Implementaciones movidas a archivos modulares.
