#include <iostream>
#define MAX 10
using namespace std;

int main()
{
    const int meses = 2;
    const int anios = 2;
    float lluvias[anios][meses];
    float sumaTotal [anios];

    for (int i = 0; i < anios; i++)
    {
        for (int j = 0; j < anios; j++)
        {
            cout << "Ingrese la cantidad de lluvia del anio " << i + 1 << " y del mes " << j + 1<<": ";
            cin >> lluvias[i][j];
        }
    }

    cout << "====CUADRO DE PROMEDIO DE LLUVIAS DURANTE LOS ULTIMOS ANIOS====" << endl;

    for (int i = 0; i < anios; i++)
    {
        for (int j = 0; j < meses; j++)
        {
            cout << lluvias[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < meses; i++)
    {
        //sumar por año;
    }
    
    return 0;
}