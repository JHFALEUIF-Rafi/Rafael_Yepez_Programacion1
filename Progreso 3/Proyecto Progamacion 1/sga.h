#ifndef SGA_H
#define SGA_H

#include <stdio.h>

// --- CONSTANTES ---
#define NUM_ZONAS 5
#define DIAS_HISTORICOS 30
#define BUFFER_SIZE 150

// UMBRALES OMS 2021 (Estrictos)
#define LIMITE_PM25 5.0
#define LIMITE_NO2  10.0
#define LIMITE_SO2  40.0

// DATOS GLOBALES DEL INFORME STERLING
#define EMISIONES_CO2_NYC "51.2 Millones de Toneladas CO2e/anio"

// --- ESTRUCTURAS ---

typedef struct {
    float pm25;
    float no2;
    float so2;
} Contaminantes;

typedef struct {
    float temperatura;
    float velocidad_viento;
    float humedad;
    char interpretacion[200];
} Clima;

typedef struct {
    char nombre[50];
    char contexto[100];
    Contaminantes actual;
    Contaminantes historico[DIAS_HISTORICOS];
    Clima clima_actual;
    Contaminantes prediccion_24h;
    Contaminantes promedio_30d;
    char alerta[100];
    char recomendacion[500];
} Zona;

// --- ESTADO GLOBAL ---
extern int predicciones_calculadas;

// --- PROTOTIPOS ---
// Inicialización y persistencia
void inicializarDatosSterling(Zona zonas[]);
void cargarHistorico(Zona zonas[]);
void guardarHistorico(Zona zonas[]);
void guardarPredicciones(Zona zonas[]);

// Clima y predicción
void generarInterpretacionClimatica(Zona *z);
void req_calcularPredicciones(Zona zonas[]);

// Vistas y reportes
void req_exportarDatos(Zona zonas[]);
void req_monitoreoActual(Zona zonas[]);
void req_mostrarAlertas(Zona zonas[]);
void req_promediosHistoricos(Zona zonas[]);
void req_generarRecomendaciones(Zona zonas[]);

// Utilidades
float solicitarEntrada(const char *mensaje, float min, float max);
int solicitarEntero(const char *mensaje, int min, int max);
int seleccionarZona(Zona zonas[]);
void esperarEnter();

#endif // SGA_H
