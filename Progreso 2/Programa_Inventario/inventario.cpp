#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include "inventario.h"
using namespace std;

// Función para convertir a minúsculas
string aMinusculas(string texto)
{
    for (char &c : texto)
    {
        c = tolower(c);
    }
    return texto;
}

// Función para ingresar nombres de productos
void ingresarNombres(string nombres[], int cantidad)
{
    cout << "\n--- INGRESO DE NOMBRES DE PRODUCTOS ---" << endl;
    for (int i = 0; i < cantidad; i++)
    {
        cout << "Ingrese el nombre del producto " << (i + 1) << ": ";
        cin.ignore();
        getline(cin, nombres[i]);
    }
}

// Función para ingresar y validar precios
void ingresarPrecios(double precios[], int cantidad)
{
    cout << "\n--- INGRESO DE PRECIOS ---" << endl;
    for (int i = 0; i < cantidad; i++)
    {
        do
        {
            cout << "Ingrese el precio para el producto " << (i + 1) << ": $";
            cin >> precios[i];

            if (precios[i] <= 0)
            {
                cout << "Error: El precio debe ser positivo. Intente nuevamente." << endl;
            }
        } while (precios[i] <= 0);
    }
}

// Función para ordenar por precio usando método burbuja
void ordenarPorPrecio(string nombres[], double precios[], int cantidad)
{
    for (int i = 0; i < cantidad - 1; i++)
    {
        for (int j = 0; j < cantidad - i - 1; j++)
        {
            if (precios[j] > precios[j + 1])
            {
                // Intercambiar precios
                double tempPrecio = precios[j];
                precios[j] = precios[j + 1];
                precios[j + 1] = tempPrecio;

                // Intercambiar nombres
                string tempNombre = nombres[j];
                nombres[j] = nombres[j + 1];
                nombres[j + 1] = tempNombre;
            }
        }
    }
}

// Función para mostrar todos los productos
void mostrarInventario(string nombres[], double precios[], int cantidad)
{
    cout << "\n--- INVENTARIO COMPLETO ---" << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < cantidad; i++)
    {
        cout << "Producto " << (i + 1) << ": " << nombres[i]
             << " - $" << precios[i] << endl;
    }
}

// Función para calcular el precio total del inventario
double calcularPrecioTotal(double precios[], int cantidad)
{
    double total = 0;
    for (int i = 0; i < cantidad; i++)
    {
        total += precios[i];
    }
    return total;
}

// Función para calcular el precio promedio
double calcularPrecioPromedio(double precios[], int cantidad)
{
    if (cantidad == 0)
        return 0;
    return calcularPrecioTotal(precios, cantidad) / cantidad;
}

// Función para buscar producto por nombre
void buscarPorNombre(string nombres[], double precios[], int cantidad)
{
    if (cantidad == 0)
    {
        cout << "El inventario esta vacio." << endl;
        return;
    }

    cin.ignore();
    string nombreBuscado;
    cout << "Ingrese el nombre del producto a buscar: ";
    getline(cin, nombreBuscado);

    string nombreBuscadoMin = aMinusculas(nombreBuscado);
    bool encontrado = false;

    cout << "\n--- RESULTADOS DE BUSQUEDA ---" << endl;
    for (int i = 0; i < cantidad; i++)
    {
        if (aMinusculas(nombres[i]).find(nombreBuscadoMin) != string::npos)
        {
            cout << "Producto encontrado: " << nombres[i] << " - $" << precios[i] << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
    {
        cout << "No se encontraron productos con el nombre: " << nombreBuscado << endl;
    }
}

// Función para buscar productos por precio
void buscarPorPrecio(string nombres[], double precios[], int cantidad)
{
    if (cantidad == 0)
    {
        cout << "El inventario esta vacio." << endl;
        return;
    }

    double precioBuscado;
    cout << "Ingrese el precio a buscar: $";
    cin >> precioBuscado;

    if (precioBuscado <= 0)
    {
        cout << "Error: El precio debe ser positivo." << endl;
        return;
    }

    double tolerancia = 0.01;
    bool encontrado = false;

    cout << "\n--- RESULTADOS DE BUSQUEDA ---" << endl;
    for (int i = 0; i < cantidad; i++)
    {
        if (abs(precios[i] - precioBuscado) < tolerancia)
        {
            cout << "Producto encontrado: " << nombres[i] << " - $" << precios[i] << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
    {
        cout << "No se encontraron productos con precio: $" << precioBuscado << endl;
    }
}

// Función para mostrar el menú de opciones
void mostrarMenu()
{
    cout << "\n=== MENU DE OPCIONES ===" << endl;
    cout << "1. Buscar producto por nombre" << endl;
    cout << "2. Buscar producto por precio" << endl;
    cout << "3. Mostrar inventario completo" << endl;
    cout << "4. Mostrar estadisticas" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opcion: ";
}