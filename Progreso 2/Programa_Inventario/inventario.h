#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <string>
using namespace std;

const int MAX_PRODUCTOS = 100;

// Prototipos de funciones
string aMinusculas(string texto);
void ingresarNombres(string nombres[], int cantidad);
void ingresarPrecios(double precios[], int cantidad);
void ordenarPorPrecio(string nombres[], double precios[], int cantidad);
void mostrarInventario(string nombres[], double precios[], int cantidad);
double calcularPrecioTotal(double precios[], int cantidad);
double calcularPrecioPromedio(double precios[], int cantidad);
void buscarPorNombre(string nombres[], double precios[], int cantidad);
void buscarPorPrecio(string nombres[], double precios[], int cantidad);
void mostrarMenu();

#endif