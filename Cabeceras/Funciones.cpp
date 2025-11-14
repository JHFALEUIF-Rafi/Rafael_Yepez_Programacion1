#include <iostream>
#include "Funciones.h"
using namespace std;

void suma(int a, int b)
{
    int suma = a + b;
    cout << "El resultado de la suma de " << a << " y " << b << " es: " << suma << endl;
}

void restar(int a, int b)
{
    int resta = a - b;
    cout << "El resultado de la resta de " << a << " y " << b << " es: " << resta << endl;
}

void multiplicar(int a, int b)
{
    int multiplicacion = a * b;
    cout << "El resultado de la multiplicacion entre " << a << " y " << b << " es: " << multiplicacion << endl;
}

void dividir(float a, float b)
{
    if (b != 0)
    {
        float division = a / b;
        cout << "El resultado de la division entre " << a << " y " << b << " es: " << division << endl;
    }
    else
    {
        cout << "No existe division para cero" << endl;
    }
}

