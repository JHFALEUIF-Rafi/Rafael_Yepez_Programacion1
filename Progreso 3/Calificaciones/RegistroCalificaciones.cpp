#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
const int MAX_ESTUDIANTES = 10;

struct Calificacion
{
    string nombreEstudiante;
    float calificacion1;
    float calificacion2;
    float calificacion3;
};

void registrarCalificaciones()
{
    ofstream archivo("calificaciones.dat", ios::binary);
    if (!archivo)
    {
        cout << "Error al abrir el archivo para escribir." << endl;
        return;
    }

    for (int i = 0; i < MAX_ESTUDIANTES; i++)
    {
        Calificacion calif;
        cout << "Ingrese el nombre del estudiante #" << (i + 1) << ": ";
        getline(cin, calif.nombreEstudiante);
        cout << "Ingrese la calificacion 1: ";
        cin >> calif.calificacion1;
        cout << "Ingrese la calificacion 2: ";
        cin >> calif.calificacion2;
        cout << "Ingrese la calificacion 3: ";
        cin >> calif.calificacion3;
        cin.ignore(); // Limpiar el buffer

        archivo.write((char *)&calif, sizeof(Calificacion));
    }

    archivo.close();
    cout << "Calificaciones registradas exitosamente." << endl;
}
