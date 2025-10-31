#include <iostream>
using namespace std;

int main()
{
    int matriz[3][3];
    int ingreso;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << "Ingresa num para " << " " << i + 1 << " " << j + 1 << ": ";
            cin >> matriz[i][j];
        }
    }

    cout << "Tu matriz es\n";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }

    //suma filas
    int sumafila[3];
    for (int i = 0; i < i; i++)
    {
        for (int j = 0; i < 3; j++)
        {
            sumafila[i] += matriz[i][j];
        }
    }
    

    cout << sumafila;
    return 0;
}