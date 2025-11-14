#ifndef ESTACIONAMIENTO_H
#define ESTACIONAMIENTO_H
#include <iostream>
float convertirHoras(float minutos);
float calcularCarga(float horas);
void cobrar(float minutos, float horas, float carga);
void ingresoCliente(float cliente[], int &contadorCarro);
void mostrarResumen(float cliente[], int contadorCarro);
#endif