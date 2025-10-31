#include <iostream>
using namespace std;

int main()
{
    const int aparatos = 3;
    const int dias = 7;
    int mayor;
    float suma;
    string electrodomesticos[aparatos] = {"Refrigerador", "Lavadora", "Televisor"};
    string diaSemana[dias] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};
    float registro[aparatos][dias];
    float consumoSemana[aparatos];

    for (int i = 0; i < aparatos; i++)
    {
        for (int j = 0; j < dias; j++)
        {
            do
            {
                cout << "Ingrese consumo del " << electrodomesticos[i] << " el dia " << diaSemana[j] << ": ";
                cin >> registro[i][j];
                if (registro[i][j] < 0)
                {
                    cout << "Ingrese un consumo válido" << endl;
                }
            } while (registro[i][j] <= 0);
        }
    }

    cout << "\n===REGISTRO DE CONSUMO===\n";
    for (int i = 0; i < dias; i++)
    {
        cout << "\t\t";
        cout << diaSemana[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < aparatos; i++)
    {
        cout << electrodomesticos[i] << "\t";
        for (int j = 0; j < dias; j++)
        {
            cout << registro[i][j] << "\t\t\t";
        }
        cout << endl;
    }

    // calcular consumo total
    for (int i = 0; i < aparatos; i++)
    {
        for (int j = 0; j < dias; j++)
        {
            suma += registro[i][j];
        }
        consumoSemana[i] = suma;
    }

    // suma total consumo
    int sumaTotal = 0;
    for (int i = 0; i < aparatos; i++)
    {
        sumaTotal += consumoSemana[i];
    }
    cout << "\nEl total del consumo general por los tres electrodomesticos es: " << sumaTotal << endl;

    //promedio
    for (int i = 0; i < aparatos; i++)
    {
        cout << "El promedio del electrodomestico " << electrodomesticos[i] << " es " << consumoSemana[i] / dias << endl;
    }

    mayor = consumoSemana[0];
    for (int i = 0; i < aparatos; i++)
    {
        if (consumoSemana[i] > mayor)
        {
            mayor = consumoSemana[i];
        }
        cout << "El electrodomestico que más consume es " << electrodomesticos[i] << " con un valor semanal de " << mayor << endl;
    }

    if (sumaTotal > 150)
    {
        cout << "Disminuye la energía" << endl;
    }

    return 0;
}