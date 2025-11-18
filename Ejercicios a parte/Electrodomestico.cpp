#include <iostream>
#include <iomanip>
using namespace std;

// Declaraciones de funciones

void leerDatosConsumo(float registro[][DIAS], string electrodomesticos[], string diaSemana[])
{
    for (int i = 0; i < APARATOS; i++)
    {
        for (int j = 0; j < DIAS; j++)
        {
            do
            {
                cout << "Ingrese consumo del " << electrodomesticos[i] << " el dia " << diaSemana[j] << ": ";
                cin >> registro[i][j];
                if (registro[i][j] < 0)
                {
                    cout << "Ingrese un consumo válido" << endl;
                }
            } while (registro[i][j] <= 0);
        }
    }
}

void mostrarRegistroConsumo(float registro[][DIAS], string electrodomesticos[], string diaSemana[])
{
    cout << "\n===REGISTRO DE CONSUMO===\n";
    
    // Encabezado de días
    cout << setw(15) << left << "Electrodomestico";
    for (int i = 0; i < DIAS; i++)
    {
        cout << setw(12) << right << diaSemana[i];
    }
    cout << endl;

    // Datos de consumo
    for (int i = 0; i < APARATOS; i++)
    {
        cout << setw(15) << left << electrodomesticos[i];
        for (int j = 0; j < DIAS; j++)
        {
            cout << setw(12) << right << registro[i][j];
        }
        cout << endl;
    }
}

void calcularConsumoPorElectrodomestico(float registro[][DIAS], float consumoSemana[])
{
    float suma;
    for (int i = 0; i < APARATOS; i++)
    {
        suma = 0;
        for (int j = 0; j < DIAS; j++)
        {
            suma += registro[i][j];
        }
        consumoSemana[i] = suma;
    }
}

int calcularConsumoTotal(float consumoSemana[])
{
    int sumaTotal = 0;
    for (int i = 0; i < APARATOS; i++)
    {
        sumaTotal += consumoSemana[i];
    }
    return sumaTotal;
}

void mostrarPromedios(float consumoSemana[], string electrodomesticos[])
{
    cout << "\n===PROMEDIOS POR ELECTRODOMESTICO===\n";
    for (int i = 0; i < APARATOS; i++)
    {
        cout << "El promedio del electrodomestico " << electrodomesticos[i] 
             << " es " << consumoSemana[i] / DIAS << endl;
    }
}

void encontrarMayorConsumo(float consumoSemana[], string electrodomesticos[])
{
    float mayor = consumoSemana[0];
    int indiceMayor = 0;
    
    for (int i = 1; i < APARATOS; i++)
    {
        if (consumoSemana[i] > mayor)
        {
            mayor = consumoSemana[i];
            indiceMayor = i;
        }
    }
    
    cout << "\nEl electrodomestico que más consume es " << electrodomesticos[indiceMayor] 
         << " con un valor semanal de " << mayor << endl;
}

void mostrarRecomendacion(int sumaTotal)
{
    cout << "\n===RECOMENDACION===\n";
    if (sumaTotal > 150)
    {
        cout << "Disminuye la energía" << endl;
    }
    else
    {
        cout << "Consumo dentro de rangos normales" << endl;
    }
}

int main()
{
    int const APARATOS = 3;
    int const DIAS = 7;
    string electrodomesticos[APARATOS] = {"Refrigerador", "Lavadora", "Televisor"};
    string diaSemana[DIAS] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};
    float registro[APARATOS][DIAS];
    float consumoSemana[APARATOS];
    int sumaTotal;

    // Leer datos de consumo
    leerDatosConsumo(registro, electrodomesticos, diaSemana);
    
    // Mostrar registro
    mostrarRegistroConsumo(registro, electrodomesticos, diaSemana);
    
    // Calcular consumos
    calcularConsumoPorElectrodomestico(registro, consumoSemana);
    sumaTotal = calcularConsumoTotal(consumoSemana);
    
    // Mostrar resultados
    cout << "\nEl total del consumo general por los tres electrodomesticos es: " << sumaTotal << endl;
    
    mostrarPromedios(consumoSemana, electrodomesticos);
    encontrarMayorConsumo(consumoSemana, electrodomesticos);
    mostrarRecomendacion(sumaTotal);

    return 0;
}