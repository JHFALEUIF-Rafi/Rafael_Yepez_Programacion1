#include <iostream>
#define MAX 10
using namespace std;

int main()
{
    int nota[MAX];

    // Ingreso
    for (int i = 0; i < MAX; i++)
    {
        cout << "Alumno " << i + 1 << endl;
        cout << "Ingrese la nota (0-10): ";
        cout << nota[i] << endl;
    }

    // Impresion
    for (int i = 0; i < MAX; i++)
    {
        cout << "Alumno " << i + 1 << endl;
        cout << "Nota: " << nota[i];
    }

    //maximo o minimo
    int maximo = nota[0];
    for (int i = 0; i < MAX; i++)
    {
        if(nota[i] > maximo){
            maximo > nota[i];
        }
    }
    return 0;
}
