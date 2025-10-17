#include <iostream>
#define MAX 10
using namespace std;

int main()
{
    const int meses = 2;
    const int anios = 2;
    float lluvias[anios][meses];
    float sumaAnual[anios];
    float promedioAnual[anios];
    float promedioPorAnio;

    for (int i = 0; i < anios; i++)
    {
        for (int j = 0; j < anios; j++)
        {
            cout << "Ingrese la cantidad de lluvia del anio " << i + 1 << " y del mes " << j + 1 << ": ";
            cin >> lluvias[i][j];
        }
    }

    cout << "====CUADRO DE PROMEDIO DE LLUVIAS DURANTE LOS ULTIMOS ANIOS====" << endl;
    cout << "Anio" << "\t" << "Mes1" << "\t" << "Mes2" << "\t" << "Suma Anual" << "\t" << "Promedio Anual" << endl;

    /*for (int i = 0; i < anios; i++)
    {
        for (int j = 0; j < meses; j++)
        {
            cout << lluvias[i][j] << "\t";
        }
        cout << endl;
    }*/

    for (int i = 0; i < anios; i++)
    {
        sumaAnual[i] = 0;
        for (int j = 0; j < meses; j++)
        {
            sumaAnual[i] += lluvias[i][j];
        }
    }

    for (int i = 0; i < anios; i++)
    {
        promedioAnual[i] = sumaAnual[i] / anios;
    }

    for (int i = 0; i < anios; i++)
    {
        cout << i + 1 << "\t";
        for (int j = 0; j < meses; j++)
        {
            cout << lluvias[i][j] << "\t";
        }
        cout << sumaAnual[i] << "\t\t" << promedioAnual[i] << endl;
    }

    // promedio por año
    for (int i = 0; i < anios; i++)
    {
        promedioPorAnio = 0;
    }
    cout << "Promedio: " << promedioPorAnio;
    return 0;
}