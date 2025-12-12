#include <iostream>
#include <iomanip>
using namespace std;

struct Paciente
{
    string nombre;
    float peso;
    float altura;
    int edad;
};

void validarNombre(string &nombre)
{
    char c;
    while (nombre.empty())
    {
        cout << "El nombre no puede estar vacio. Ingrese nuevamente: ";
        getline(cin, nombre);
    }

    for (char c : nombre)
    {
        if (!isalpha(c) && c != ' ')
        {
            cout << "El nombre solo puede contener letras y espacios. Ingrese nuevamente: ";
            getline(cin, nombre);
            validarNombre(nombre);
            return;
        }
    }
    
}

int main()
{
    struct Paciente paciente1;
    int frecuenciaMaxima;
    float imc;

    cout << "===Registro de Paciente===" << endl;
    cout << "Ingrese el nombre del paciente: ";
    getline(cin, paciente1.nombre);
    cout << "Ingrese el peso del paciente (kg): ";
    cin >> paciente1.peso;
    cout << "Ingrese la altura del paciente (m): ";
    cin >> paciente1.altura;
    cout << "Ingrese la edad del paciente: ";
    cin >> paciente1.edad;

    frecuenciaMaxima = 220 - paciente1.edad;
    imc = paciente1.peso / (paciente1.altura * paciente1.altura);

    cout << "\n---Datos del Paciente---" << endl;
    cout << "Nombre: " << paciente1.nombre << endl;
    cout << "Peso: " << paciente1.peso << " kg" << endl;
    cout << "Altura: " << paciente1.altura << " m" << endl;
    cout << "Edad: " << paciente1.edad << " anios" << endl;
    cout << "Frecuencia Cardiaca Maxima: " << frecuenciaMaxima << " latidos por minuto" << endl;
    cout << "Indice de Masa Corporal (IMC): " << fixed << setprecision(2) << imc << endl;

    return 0;
}