#include <iostream>
#include <cmath>
using namespace std;

void ingresoCliente(float cliente[], float minutos, int contadorCarro)
{
    char opcion;

    do
    {
        cout << "Ingrese el tiempo que estuvo estacionado (en minutos): ";
        cin >> minutos;
        contadorCarro ++;
    } while (minutos < 0);

    do
    {
        cout << "Deseea ingresar otro vehiculo(s/n):";
        cin >> opcion;
    } while (opcion == 's' || opcion == 'S');

    
}

float convertirHoras(float minutos)
{
    float horas;
    int redondeo;
    horas = minutos / 60.0;
    redondeo = (horas * 100 + 0.5);
    horas = redondeo / 100.0;
    return horas;
}

float calcularCarga(float horas)
{
    int tarifaBase = 2;
    float tarifaHoraExtra = 0.50;
    float horaExtra;
    float carga;
    if (horas < 3)
    {
        carga = tarifaBase;
    }
    else if (horas > 3 && horas < 24)
    {
        horaExtra = horas - 3;
        int horaEntera = ceil(horaExtra);
        carga = tarifaBase + (horaEntera * tarifaHoraExtra);
    }
    else if (horas >= 24)
    {
        carga = 10.00;
    }
    return carga;
}

void cobrar(float minutos, float horas, float carga)
{
    cout << "Su carga es de " << minutos << " minutos, es decir, " << horas << " horas y por lo tanto se le cobrara: " << carga << " $" << endl;
}

int main()
{
    const int aforo = 90;
    int contadorCarro = 0;
    float minutos;
    float cliente[aforo];

    float horas = convertirHoras(minutos);
    float carga = calcularCarga(horas);

    cobrar(minutos, horas, carga);

    return 0;
}