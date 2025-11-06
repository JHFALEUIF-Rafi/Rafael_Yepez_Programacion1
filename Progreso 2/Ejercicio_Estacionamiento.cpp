#include <iostream>
using namespace std;

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
    float tarifa = 0.50;
    float carga;
    if (horas < 3)
    {
        carga = tarifa * 4;
    }
    else if (horas > 3 && horas < 24)
    {
        carga = horas * tarifa;
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
    float minutos;
    do
    {
        cout << "Ingrese el tiempo que estuvo estacionado (en minutos): ";
        cin >> minutos;
    } while (minutos < 0);

    float horas = convertirHoras(minutos);
    float carga = calcularCarga(horas);
    
    cobrar(minutos, horas, carga);

    return 0;
}