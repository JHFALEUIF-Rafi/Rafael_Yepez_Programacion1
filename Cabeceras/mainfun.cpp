#include <iostream>
#include "Funciones.h"
#include "Lecturas.h"
#include "Estacionamiento.h"
using namespace std;

void mostrarMenu()
{
    cout << "\n=== MENU PRINCIPAL ===" << endl;
    cout << "1. Calculadora Basica" << endl;
    cout << "2. Validacion de Numeros" << endl;
    cout << "3. Sistema de Estacionamiento" << endl;
    cout << "4. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void menuCalculadora()
{
    cout << "\n=== CALCULADORA BASICA ===" << endl;
    int a, b;
    float fa, fb;
    
    cout << "Ingrese primer numero: ";
    cin >> a;
    cout << "Ingrese segundo numero: ";
    cin >> b;
    
    suma(a, b);
    restar(a, b);
    multiplicar(a, b);
    
    cout << "Para division (puede usar decimales):" << endl;
    cout << "Ingrese primer numero: ";
    cin >> fa;
    cout << "Ingrese segundo numero: ";
    cin >> fb;
    dividir(fa, fb);
}

void menuValidacion()
{
    cout << "\n=== VALIDACION DE NUMEROS ===" << endl;
    int numero;
    
    validarPositivo(numero);
    cout << "Numero positivo validado: " << numero << endl;
    
    validarNegativo(numero);
    cout << "Numero negativo validado: " << numero << endl;
    
    validarRango(numero);
    cout << "Numero en rango validado: " << numero << endl;
}

void menuEstacionamiento()
{
    cout << "\n=== SISTEMA DE COBRO DE ESTACIONAMIENTO ===" << endl;
    const int aforo = 90;
    int contadorCarro = 0;
    float cliente[aforo]; 
    
    ingresoCliente(cliente, contadorCarro);
    mostrarResumen(cliente, contadorCarro);
    cout << "\nGracias por usar nuestro servicio!" << endl;
}

int main()
{
    int opcion;
    
    do
    {
        mostrarMenu();
        cin >> opcion;
        
        switch(opcion)
        {
            case 1:
                menuCalculadora();
                break;
                
            case 2:
                menuValidacion();
                break;
                
            case 3:
                menuEstacionamiento();
                break;
                
            case 4:
                cout << "¡Hasta luego!" << endl;
                break;
                
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
                break;
        }
        
        if (opcion != 4)
        {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
        
    } while (opcion != 4);
    
    return 0;
}