#include <iostream>
#include "inventario.h"
#include <iomanip>
using namespace std;

int main() {
    string nombres[MAX_PRODUCTOS];
    double precios[MAX_PRODUCTOS];
    int cantidad;
    
    cout << "=== SISTEMA DE GESTION DE INVENTARIO ===" << endl;
    cout << "Cuantos productos desea ingresar? (max " << MAX_PRODUCTOS << "): ";
    cin >> cantidad;
    
    // Validar que no exceda el máximo
    if (cantidad > MAX_PRODUCTOS || cantidad <= 0) {
        cout << "Cantidad invalida!" << endl;
        return 1;
    }
    
    ingresarNombres(nombres, cantidad);
    ingresarPrecios(precios, cantidad);
    
    // Ordenar los productos por precio
    ordenarPorPrecio(nombres, precios, cantidad);
    
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                buscarPorNombre(nombres, precios, cantidad);
                break;
            case 2:
                buscarPorPrecio(nombres, precios, cantidad);
                break;
            case 3:
                mostrarInventario(nombres, precios, cantidad);
                break;
            case 4:
                cout << "\n--- ESTADISTICAS DEL INVENTARIO ---" << endl;
                cout << fixed << setprecision(2);
                
                double total = calcularPrecioTotal(precios, cantidad);
                cout << "Precio total del inventario: $" << total << endl;
                
                cout << "Producto mas barato: " << nombres[0] << " - $" << precios[0] << endl;
                cout << "Producto mas caro: " << nombres[cantidad - 1] << " - $" << precios[cantidad - 1] << endl;
                
                double promedio = calcularPrecioPromedio(precios, cantidad);
                cout << "Precio promedio: $" << promedio << endl;
                break;
            case 5:
                cout << "¡Gracias por usar el sistema!" << endl;
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente." << endl;
        }
    } while (opcion != 5);
    
    return 0;
}