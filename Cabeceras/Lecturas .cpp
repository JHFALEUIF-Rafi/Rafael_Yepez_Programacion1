#include <iostream>
using namespace std;

void validarPositivo(int &positivo)
{
    do
    {
        cout << "Ingrese un numero positivo: ";
        cin >> positivo;
        if (positivo < 1)
        {
            cout << "El numero ingresado no es positivo" << endl;
        }
    } while (positivo < 1);
}

void validarNegativo(int &negativo)
{
    do
    {
        cout << "Ingrese un numero negativo: ";
        cin >> negativo;
        if (negativo > -1)
        {
            cout << "El numero ingresado no es negativo" << endl;
        }
    } while (negativo > -1);
}

void validarRango(int &rango)
{
    do
    {
        cout << "Ingrese un numero en el rango de 0 a 10: ";
        cin >> rango;
        if (rango < 0 || rango > 10)
        {
            cout << "El numero debe estar entre 0 y 10" << endl;
        }
    } while (rango < 0 || rango > 10);
}