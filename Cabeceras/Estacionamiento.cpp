#include <iostream>
#include <cmath>
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
    int tarifaBase = 2;
    float tarifaHoraExtra = 0.50;
    float horaExtra;
    float carga;
    
    if (horas <= 3)
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

void ingresoCliente(float cliente[], int &contadorCarro)
{
    char opcion;
    float minutos, horas, carga;
    
    do
    {
        cout << "\n--- Auto #" << (contadorCarro + 1) << " ---" << endl;
        
        // Validar entrada de minutos
        do
        {
            cout << "Ingrese el tiempo que estuvo estacionado (en minutos): ";
            cin >> minutos;
            if (minutos < 0)
            {
                cout << "Error: El tiempo no puede ser negativo. Intente nuevamente." << endl;
            }
        } while (minutos < 0);

        // Calcular horas y carga
        horas = convertirHoras(minutos);
        carga = calcularCarga(horas);
        
        // Mostrar cobro para este auto
        cobrar(minutos, horas, carga);
        
        // Almacenar en el arreglo (si se desea guardar la carga)
        cliente[contadorCarro] = carga;
        contadorCarro++;
        
        // Preguntar si desea ingresar otro vehículo
        do
        {
            cout << "\n¿Desea ingresar otro vehiculo (s/n): ";
            cin >> opcion;
            
            if (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N')
            {
                cout << "Error: Ingrese 's' para sí o 'n' para no." << endl;
            }
        } while (opcion != 's' && opcion != 'S' && opcion != 'n' && opcion != 'N');
        
    } while ((opcion == 's' || opcion == 'S') && contadorCarro < 90);
}

void mostrarResumen(float cliente[], int contadorCarro)
{
    float total = 0;
    
    cout << "\n=== RESUMEN DE COBROS ===" << endl;
    for (int i = 0; i < contadorCarro; i++)
    {
        cout << "Auto #" << (i + 1) << ": " << cliente[i] << " $" << endl;
        total += cliente[i];
    }
    cout << "========================" << endl;
    cout << "TOTAL A PAGAR: " << total << " $" << endl;
    cout << "========================" << endl;
}