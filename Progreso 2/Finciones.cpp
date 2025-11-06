#include <iostream>
using namespace std;

// No retorna y no recibe parametros
void suma(int a, int b)
{
    int suma;
    suma = a + b;
    cout << "El resultado de la suma de " << a << " y " << b << " es: " << suma << endl;
}

// no retorna valor, pero si recibe parametro
void restar(int a, int b)
{
    int resta;
    resta = a - b;
    cout << "El resultado de la resta de " << a << " y " << b << " es: " << resta << endl;
}

// no retorna valor y que reciba parametro
void multiplicar(int a, int b)
{
    int multiplicacion;
    multiplicacion = a * b;
    cout << "El resultado de la multiplicacion entre " << a << " y " << b << " es: " << multiplicacion << endl;
}

// retorna valor y no recibe parametro
void dividir(float a, float b)
{
    float division;
    division = a / b;
    if (b != 0)
    {
        cout << "El resultado de la division entre " << a << " y " << b << " es: " << division << endl;
    }
    else
    {
        cout << "No existe division para cero" << endl;
    }
}

int main()
{
    int a, b;
    cout << "Ingrese el primer numero: ";
    cin >> a;
    cout << "Ingrese el segundo numero: ";
    cin >> b;

    suma(a, b);
    restar(a, b);
    multiplicar(a, b);
    dividir(a, b);
    return 0;
}