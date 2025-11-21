#include <iostream>
using namespace std;
int const MAX = 30;

void ingresarNotasV1(int notas[], int *numAlumnos)
{
    int cantidad;
    cout << "Cuantos estudiantes hay en el curso?: ";
    cin >> cantidad;
    *numAlumnos = cantidad;
    for (int i = 0; i < *numAlumnos; i++)
    {
        cout << "Ingrese la nota del estudiante: ";
        cin >> notas[i];
    }
}

void ingresarNotasv2(int notas[], int *numAlumnos)
{
    int opcion;
    do
    {
        cout << "Ingrese la nota del estudiante " << numAlumnos + 1 << ": ";
        cin >> notas[*numAlumnos];

        cout << "1. Para ingresar mas notas, 0 para salir: ";
        cin >> opcion;
    } while (opcion != 0);
}

void ingresarNotasV3(int notas[], int *numAlumnos)
{
    int opcion;
    do
    {
        cout << "Ingrese la nota del estudiante " << *numAlumnos + 1 << ": ";
        cin >> notas[*numAlumnos];
        *numAlumnos += 1;

        if (*numAlumnos == MAX)
        {
            cout << "Se ha alcanzado el maximo de estudiantes";
            break;
        }

        cout << "1. Para ingresar mas notas, 0 para salir: ";
        cin >> opcion;
    } while (opcion != 0);
}

void imprimirNotas(const int notas[], int *numAlumnos)
{
    if (*numAlumnos < MAX)
    {
        cout << "Ingrese la nota del estudiante " << *numAlumnos + 1 << ": ";
        cin >> notas[*numAlumnos];
    }
    else
    {
        cout << "Se ha completado el limite de estudiantes";
    }
}

float promedioCurso(const int notas[], int numAlumnos)
{
}

int main()
{
    int notas[MAX];
    int alumnos = 0;
    ingresarNotasV1(notas, &alumnos);
    ingresarNotasv2(notas, &alumnos);
    ingresarNotasV3(notas, &alumnos);
    return 0;
}