#include <iostream>
using namespace std;

int main()
{
    const int aparatos = 3;
    const int dias = 7;
    string electrodomesticos[aparatos] = {"Refrigerador", "Lavadora", "Televisor"};
    string diaSemana[dias] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};
    float registro[aparatos][dias];

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

    return 0;
}