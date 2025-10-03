#include <iostream>
using namespace std;

void ingresarCalificacion(float calificaciones[], int &cantidad)
{
    float nota;
    char continuar;

    do
    {
        cout << "Ingrese la calificacion (1-10): ";

        while (!(cin >> nota))
        {
            cout << "Ingrese una opcion valida (1-10)" << endl;
            cout << "Ingrese la calificacion (1-10): ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        if (nota < 1 || nota > 10)
        {
            cout << "\nPor favor, ingrese la calificacion (1-10)" << endl;
            continue;
        }

        calificaciones[cantidad] = nota;
        cantidad++;
        cout << "Calificacion: " << nota << " agregada exitosamente." << endl;
        // cin.ignore(1000, '\n');

        bool entradaValida = false;
        do
        {
            cout << "Desea ingresar otra calificacion? (s/n): ";
            cin >> continuar;
            cin.ignore(1000, '\n');

            if (continuar == 's' || continuar == 'S' || continuar == 'n' || continuar == 'N')
            {
                entradaValida = true;
            }
            else
            {
                cout << "Por favor ingrese 's' para si o 'n' para no." << endl;
            }
        } while (!entradaValida);

    } while ((continuar == 's' || continuar == 'S') && cantidad < 100);

    cout << "Total de calificaciones ingresadas: " << cantidad << endl;
}

void calcularPromedio(float calificaciones[], int cantidad)
{
    if (cantidad == 0)
    {
        cout << "No hay calificaciones ingresadas...." << endl;
        return;
    }

    float suma = 0;
    for (int i = 0; i < cantidad; i++)
    {
        suma += calificaciones[i];
    }

    double promedio = suma / cantidad;
    int promedioEntero = promedio * 100;
    promedio = promedioEntero / 100.0;
    cout << "El promedio de las " << cantidad << " calificaciones es: " << promedio << endl;
}

void mostrarNotas(float calificaciones[], int cantidad)
{
    if (cantidad == 0)
    {
        cout << "No hay calificaciones ingresadas...." << endl;
        return;
    }
    
    cout << "***NOTAS INGRESADAS***" << endl;
    for (int i = 0; i < cantidad; i++)
    {
        cout << "Calificacion " << (i + 1) << ": " << calificaciones[i] << endl;
    }
}

void menu(float calificaciones[], int &cantidad)
{
    int opcion;
    bool validar = true;

    do
    {
        cout << "\nSeleccione una opcion:" << endl;
        cout << "1. Ingresar Calificacion" << endl;
        cout << "2. Obtener Promedio" << endl;
        cout << "3. Mostrar calificaciones" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";

        while (!(cin >> opcion))
        {
            cout << "Ingrese una opcion valida (1-4)" << endl;
            cout << "Opcion: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (opcion)
        {
        case 1:
            ingresarCalificacion(calificaciones, cantidad);
            break;
        case 2:
            calcularPromedio(calificaciones, cantidad);
            break;
        case 3:
            mostrarNotas(calificaciones, cantidad);
            break;
        case 4:
            cout << "Saliendo del programa..." << endl;
            validar = false;
            break;
        default:
            cout << "Opcion no valida, por favor intente de nuevo." << endl;
            break;
        }
    } while (validar);
}

int main()
{
    float calificaciones[15];
    int cantidad = 0;
    menu(calificaciones, cantidad);
    return 0;
}