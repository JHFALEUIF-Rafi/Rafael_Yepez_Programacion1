#include <iostream>
using namespace std;

void ingresarCalificacion()
{
    int asd;
}

void menu()
{
    int opcion;
    bool validar = true;
    cout << "Seleccione una opcion:" << endl;
    cout << "1. Ingresar Calificacion" << endl;
    cout << "2. Obtener Promedio" << endl;
    cout << "3. Mostrar Nota del Progreso" << endl;
    cin >> opcion;

    while (validar)
    {
        switch (opcion)
        {
        case 1:
            cout << "1. Ingresar Alumno" << endl;
            break;
        case 2:
            cout << "2. Calcular promedio" << endl;
            break;
        case 3:
            cout << "Mostrar Alumno";
            break;
        default:
            cout << "Ingrese opcion valida...";
            validar = false;
            break;
        }
    }
}

int main()
{
    menu();
    return 0;
}