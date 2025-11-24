#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int MAX_PRODUCTOS = 5;

// Función para ingresar número positivo
void ingresarPositivo(int &valor, string tipo)
{
    do
    {
        cout << tipo << ": ";
        cin >> valor;
        if (valor <= 0)
        {
            cout << "El valor ingresado no es positivo\n";
        }
    } while (valor <= 0);
}

//Función para ingresar nombre
void ingresarNombre(string &nombre)
{
    bool validar;
    do
    {
        cout << "Nombre (sin numeros): ";
        cin >> nombre;

        validar = false;
        for (char c : nombre)
        {
            if (isdigit(c))
            {
                validar = true;
                break;
            }
        }

        if (validar)
        {
            cout << "El nombre no puede contener caracteres numericos\n";
        }
    } while (validar);
}

// Función para ingresar datos de un producto
void ingresarProducto(string &nombre, int &demanda, int &tiempo, int &recursos, int indice)
{
    cout << "\nProducto " << (indice + 1) << ":\n";
    ingresarNombre(nombre);
    ingresarPositivo(demanda, "Cantidad demandada");
    ingresarPositivo(tiempo, "Tiempo de fabricacion por unidad");
    ingresarPositivo(recursos, "Recursos por unidad");
    cout << "------------------------";
}

// Función para buscar producto por nombre
int buscarProducto(string nombres[], string nombreBuscado, int contador)
{
    for (int i = 0; i < contador; i++)
    {
        if (nombres[i] == nombreBuscado)
        {
            return i; 
        }
    }
    return -1;
}

// Función para editar producto
void editarProducto(string nombres[], int demandas[], int tiempos[], int recursos[], int contador)
{
    string nombreEditar;
    cout << "\nNombre del producto a editar: ";
    cin >> nombreEditar;

    int posicion = buscarProducto(nombres, nombreEditar, contador);

    if (posicion == -1)
    {
        cout << "Producto no encontrado!\n";
        return;
    }

    cout << "\nEditando producto: " << nombres[posicion] << endl;
    cout << "1. Cambiar nombre\n";
    cout << "2. Cambiar cantidad demandada\n";
    cout << "3. Cambiar tiempo de fabricacion\n";
    cout << "4. Cambiar recursos por unidad\n";
    cout << "Opcion: ";

    int opcion;
    cin >> opcion;

    switch (opcion)
    {
    case 1:
        ingresarNombre(nombres[posicion]);
        break;
    case 2:
        ingresarPositivo(demandas[posicion], "Nueva cantidad demandada");
        break;
    case 3:
        ingresarPositivo(tiempos[posicion], "Nuevo tiempo de fabricacion");
        break;
    case 4:
        ingresarPositivo(recursos[posicion], "Nuevos recursos por unidad");
        break;
    default:
        cout << "Opcion invalida!\n";
    }
    cout << "Producto editado correctamente!\n";
}

// Función para eliminar producto
void eliminarProducto(string nombres[], int demandas[], int tiempos[], int recursos[], int &contador)
{
    string nombreEliminar;
    cout << "\nNombre del producto a eliminar: ";
    cin >> nombreEliminar;

    int posicion = buscarProducto(nombres, nombreEliminar, contador);

    if (posicion == -1)
    {
        cout << "Producto no encontrado!\n";
        return;
    }

    // Mover todos los elementos una posición hacia atrás
    for (int i = posicion; i < contador - 1; i++)
    {
        nombres[i] = nombres[i + 1];
        demandas[i] = demandas[i + 1];
        tiempos[i] = tiempos[i + 1];
        recursos[i] = recursos[i + 1];
    }

    contador--; 
    cout << "Producto eliminado correctamente!\n";
}

// Función para calcular tiempos y recursos totales
void calcularTotales(string nombres[], int demandas[], int tiempos[],
                     int recursos[], int contador, int &tiempoTotal, int &recursosTotal)
{
    tiempoTotal = 0;
    recursosTotal = 0;

    for (int i = 0; i < contador; i++)
    {
        tiempoTotal += demandas[i] * tiempos[i];
        recursosTotal += demandas[i] * recursos[i];
    }
}

// Función para verificar capacidad
void verificarCapacidad(int tiempoTotal, int recursosTotal)
{
    int tiempoDisponible, recursosDisponibles;

    cout << "\n=== VERIFICACION DE CAPACIDAD ===\n";
    cout << "Tiempo total requerido: " << tiempoTotal << " unidades\n";
    cout << "Recursos totales necesarios: " << recursosTotal << " unidades\n";

    cout << "\nIngrese tiempo disponible de produccion: ";
    cin >> tiempoDisponible;
    cout << "Ingrese recursos disponibles: ";
    cin >> recursosDisponibles;

    cout << "\n=== RESULTADO ===\n";
    if (tiempoTotal <= tiempoDisponible && recursosTotal <= recursosDisponibles)
    {
        cout << "La fabrica PUEDE cumplir con la demanda!\n";
    }
    else
    {
        cout << "La fabrica NO puede cumplir con la demanda\n";
        if (tiempoTotal > tiempoDisponible)
        {
            cout << " - Faltan " << (tiempoTotal - tiempoDisponible) << " unidades de tiempo\n";
        }
        if (recursosTotal > recursosDisponibles)
        {
            cout << " - Faltan " << (recursosTotal - recursosDisponibles) << " unidades de recursos\n";
        }
    }
}

// Función para mostrar resultados
void mostrarResultados(int tiempoTotal, int recursosTotal)
{
    cout << "\n=== RESULTADOS ===\n";
    cout << "Tiempo total requerido: " << tiempoTotal << " unidades\n";
    cout << "Recursos totales necesarios: " << recursosTotal << " unidades\n";
}

// Función para mostrar todos los productos
void mostrarProductos(string nombres[], int demandas[], int tiempos[], int recursos[], int contador)
{
    cout << "\n=== PRODUCTOS REGISTRADOS ===\n";
    for (int i = 0; i < contador; i++)
    {
        cout << (i + 1) << ". " << nombres[i] << " - Demanda: " << demandas[i]
             << ", Tiempo: " << tiempos[i] << ", Recursos: " << recursos[i] << endl;
    }
}

// Menú principal
void mostrarMenu()
{
    cout << "\n=== MENU PRINCIPAL ===\n";
    cout << "1. Mostrar productos\n";
    cout << "2. Editar producto\n";
    cout << "3. Eliminar producto\n";
    cout << "4. Calcular totales\n";
    cout << "5. Verificar capacidad\n";
    cout << "6. Salir\n";
    cout << "Opcion: ";
}

int main()
{
    string nombres[MAX_PRODUCTOS];
    int demandas[MAX_PRODUCTOS];
    int tiempos[MAX_PRODUCTOS];
    int recursos[MAX_PRODUCTOS];
    int tiempoTotal, recursosTotal;
    int contador = MAX_PRODUCTOS;
    int opcion;

    cout << "=== SISTEMA DE PRODUCCION ===\n\n";

    // Ingreso inicial de datos
    for (int i = 0; i < MAX_PRODUCTOS; i++)
    {
        ingresarProducto(nombres[i], demandas[i], tiempos[i], recursos[i], i);
    }

    // Menú principal
    do
    {
        mostrarMenu();
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            mostrarProductos(nombres, demandas, tiempos, recursos, contador);
            break;
        case 2:
            editarProducto(nombres, demandas, tiempos, recursos, contador);
            break;
        case 3:
            eliminarProducto(nombres, demandas, tiempos, recursos, contador);
            break;
        case 4:
            calcularTotales(nombres, demandas, tiempos, recursos, contador, tiempoTotal, recursosTotal);
            mostrarResultados(tiempoTotal, recursosTotal);
            break;
        case 5:
            calcularTotales(nombres, demandas, tiempos, recursos, contador, tiempoTotal, recursosTotal);
            verificarCapacidad(tiempoTotal, recursosTotal);
            break;
        case 6:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opcion invalida!\n";
        }
    } while (opcion != 6);

    return 0;
}