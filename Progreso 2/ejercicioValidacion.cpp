#include <iostream>
using namespace std;

void validarNombre(string &nombre)
{
    bool nombreValido = false;

    while (!nombreValido)
    {
        cout << "Ingresa tu nombre: ";
        getline(cin, nombre);
        nombreValido = true;
        for (char c : nombre)
        {
            if (isdigit(c))
            {
                cout << "El nombre no debe contener numeros, solo caracteres"<<endl;
                nombreValido = false;
                break;
            }
        }
    }
}

void validarPositivo(int &positivo)
{
    numeroValido
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

int main()
{
    string nombre;
    int positivo;
    int negativo;
    int rango;

    validarNombre(nombre);
    cout << nombre;
}