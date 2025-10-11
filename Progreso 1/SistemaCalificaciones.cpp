#include <iostream>
using namespace std;

void ingresoEstudiante(string estudiantes[], int &contadorEstudiantes)
{
    if (contadorEstudiantes >= 5)
    {
        cout << "Limite de estudiantes alcanzado" << endl;
        return;
    }

    string nombre;
    bool nombreValido = false;

    while (!nombreValido)
    {
        cout << "Ingrese nombre del estudiante: ";
        cin.ignore();
        getline(cin, nombre);

        nombreValido = true;
        for (char c : nombre)
        {
            if (isdigit(c))
            {
                cout << "El nombre no puede contener numeros" << endl;
                nombreValido = false;
                break;
            }
        }

        if (nombre.empty())
        {
            cout << "Por favor complete el campo" << endl;
            nombreValido = false;
        }
    }
    estudiantes[contadorEstudiantes] = nombre;
    contadorEstudiantes++;
}

void ingresoAsignatura(string asignaturas[], int &contadorAsignaturas)
{
    
}

void ingresoCalificacion()
{
}

void calcularPromedio(float calificaciones[])
{
}

void buscarCalificacion()
{
}

void menu()
{
    int opcion;
    bool validar = true;

    do
    {
        system("clear");
        cout << "\n=== SISTEMA DE CALIFICACIONES ===" << endl;
        cout << "1. Ingresar Estudiante" << endl;
        cout << "2. Calcular Promedio" << endl;
        cout << "3. Mostrar Resumen" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion:";

        while (!(cin >> opcion))
        {
            cout << "Ingrese opcion valida (1-4)" << endl;
            cout << "Opcion: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (opcion)
        {
        case 1:
            system("cls");
            cin.ignore();
            cin.get();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
        }
    } while (validar);
}

void parametros()
{
    string estudiantes[5];
    string asignaturas[3];
    float calificaciones[100];
    int contadorEstudiantes = 0;
    int contadorAsignaturas = 0;
    int contadorCalificaciones = 0;
}

int main()
{

    return 0;
}