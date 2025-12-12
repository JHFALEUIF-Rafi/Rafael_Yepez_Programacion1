#include <iostream>
#include <iomanip>
using namespace std;
const int MAX_PACIENTES = 3;

struct Paciente
{
    string nombre;
    float peso;
    float altura;
    int edad;
};

void ingresarPacientes(Paciente pacientes[], int MAX_PACIENTES)
{
    cout << "===Registro de Paciente===" << endl;
    int num;

    do
    {
        cout << "Ingrese el numero de pacientes a registrar (maximo " << MAX_PACIENTES << "): ";
        cin >> num;
        cin.ignore();
        if (num < 1 || num > MAX_PACIENTES)
        {
            cout << "Numero invalido. Intente de nuevo." << endl;
        }

    } while (num < 1 || num > MAX_PACIENTES);

    for (int i = 0; i < num; i++)
    {
        cout << "Ingrese el nombre del paciente: ";
        getline(cin, pacientes[i].nombre);
        cout << "Ingrese el peso del paciente (kg): ";
        cin >> pacientes[i].peso;
        cout << "Ingrese la altura del paciente (m): ";
        cin >> pacientes[i].altura;
        cout << "Ingrese la edad del paciente: ";
        cin >> pacientes[i].edad;
        cin.ignore();
    }
}

void mostrarDatosPacientes(const Paciente pacientes[], int MAX_PACIENTES)
{
    for (int i = 0; i < MAX_PACIENTES; i++)
    {
        cout << "Nombre: " << pacientes[i].nombre << endl;
        cout << "Peso: " << pacientes[i].peso << " kg" << endl;
        cout << "Altura: " << pacientes[i].altura << " m" << endl;
        cout << "Edad: " << pacientes[i].edad << " anios" << endl;
        cout << endl;
    }
}

int main()
{
    struct Paciente pacientes[MAX_PACIENTES];
    ingresarPacientes(pacientes, MAX_PACIENTES);
    mostrarDatosPacientes(pacientes, MAX_PACIENTES);
    return 0;
}