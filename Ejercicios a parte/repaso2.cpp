#include <iostream>
using namespace std;

void ingresarPrecios(float precios[], int tamaño)
{
    cout << "INGRESO DE PRECIOS" << endl;
    for (int i = 0; i < tamaño; i++)
    {
        cout << "Precio " << (i + 1) << ": $";
        cin >> precios[i];
    }
}

void mostrarPrecios(float precios[], int tamaño, string mensaje)
{
    cout << mensaje << ": ";
    for (int i = 0; i < tamaño; i++)
    {
        cout << "$" << precios[i] << " ";
    }
    cout << endl;
}

void ordenarBurbuja(float arr[], int tamaño)
{
    for (int i = 0; i < tamaño - 1; i++)
    {
        for (int j = 0; j < tamaño - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    const int TAMANO = 4;
    float precios[TAMANO];

    ingresarPrecios(precios, TAMANO);
    cout << endl;

    mostrarPrecios(precios, TAMANO, "Precios originales");

    ordenarBurbuja(precios, TAMANO);

    mostrarPrecios(precios, TAMANO, "Precios ordenados");

    return 0;
}