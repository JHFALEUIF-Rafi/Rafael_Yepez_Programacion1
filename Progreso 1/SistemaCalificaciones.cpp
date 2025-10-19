#include <iostream>
using namespace std;

void ingresoEstudianteCompleto(string estudiantes[], string asignaturas[][3], float calificaciones[][3], int &contadorEstudiantes)
{
    if (contadorEstudiantes >= 5)
    {
        cout << "Limite de estudiantes alcanzado (maximo 5)" << endl;
        return;
    }

    string nombre;
    bool nombreValido = false;

    while (!nombreValido)
    {
        cout << "Ingrese nombre del estudiante: ";
        if (contadorEstudiantes == 0)
            cin.ignore();
        getline(cin, nombre);

        nombreValido = true;
        for (char c : nombre)
        {
            if (isdigit(c))
            {
                cout << "Error: El nombre no puede contener numeros" << endl;
                nombreValido = false;
                break;
            }
        }

        if (nombre.empty())
        {
            cout << "Error: El nombre no puede estar vacio" << endl;
            nombreValido = false;
        }
    }

    estudiantes[contadorEstudiantes] = nombre;

    cout << "\nIngrese las 3 asignaturas para " << nombre << ":" << endl;
    for (int i = 0; i < 3; i++)
    {
        string asignatura;
        bool asignaturaValida = false;

        // Ingresar nombre de asignatura
        while (!asignaturaValida)
        {
            cout << "\nAsignatura " << (i + 1) << ": ";
            getline(cin, asignatura);

            asignaturaValida = true;
            for (char c : asignatura)
            {
                if (isdigit(c))
                {
                    cout << "Error: La asignatura no puede contener numeros" << endl;
                    asignaturaValida = false;
                    break;
                }
            }

            if (asignatura.empty())
            {
                cout << "Error: La asignatura no puede estar vacia" << endl;
                asignaturaValida = false;
            }
        }

        asignaturas[contadorEstudiantes][i] = asignatura;

        cout << "Ingreso de calificaciones para " << asignatura << ":" << endl;
        float sumaCalificaciones = 0;
        int contadorNotas = 0;
        char otraNota;

        do
        {
            float nota;
            bool notaValida = false;

            while (!notaValida)
            {
                cout << "Nota " << (contadorNotas + 1) << ": ";
                if (cin >> nota)
                {
                    if (nota >= 0 && nota <= 10)
                    {
                        notaValida = true;
                    }
                    else
                    {
                        cout << "Error: La nota debe estar entre 0 y 10" << endl;
                    }
                }
                else
                {
                    cout << "Error: Ingrese un numero valido" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }

            sumaCalificaciones += nota;
            contadorNotas++;

            bool entradaValida = false;
            do
            {
                cout << "Desea ingresar otra calificacion? (s/n): ";
                cin >> otraNota;
                cin.ignore(1000, '\n');

                if (otraNota == 's' || otraNota == 'S' || otraNota == 'n' || otraNota == 'N')
                {
                    entradaValida = true;
                }
                else
                {
                    cout << "Por favor ingrese 's' para si o 'n' para no." << endl;
                }
            } while (!entradaValida);

        } while (otraNota == 's' || otraNota == 'S');

        calificaciones[contadorEstudiantes][i] = sumaCalificaciones / contadorNotas;
        cout << "Promedio de " << asignatura << ": " << calificaciones[contadorEstudiantes][i] << endl;
    }

    contadorEstudiantes++;
    cout << "\nEstudiante, asignaturas y calificaciones ingresados exitosamente!" << endl;
}

void calcularPromedio(string estudiantes[], string asignaturas[][3], float calificaciones[][3], int contadorEstudiantes)
{
    if (contadorEstudiantes == 0)
    {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }

    cout << "\n=== CALCULO DE PROMEDIOS ===" << endl;

    cout << "Estudiantes registrados:" << endl;
    for (int i = 0; i < contadorEstudiantes; i++)
    {
        cout << (i + 1) << ". " << estudiantes[i] << endl;
    }

    int opcion;
    cout << "Seleccione el estudiante (1-" << contadorEstudiantes << "): ";
    cin >> opcion;

    if (opcion < 1 || opcion > contadorEstudiantes)
    {
        cout << "Opcion invalida!" << endl;
        return;
    }

    int indiceEstudiante = opcion - 1;

    system("cls");
    cout << "\n=== PROMEDIOS DE " << estudiantes[indiceEstudiante] << " ===" << endl;

    float sumaGeneral = 0;
    int asignaturasConNotas = 0;

    cout << "\n--- PROMEDIO POR MATERIA ---" << endl;
    for (int i = 0; i < 3; i++)
    {
        if (!asignaturas[indiceEstudiante][i].empty())
        {
            float nota = calificaciones[indiceEstudiante][i];
            int temporal = nota * 100;
            float notaRedondeada = temporal / 100.0;

            cout << asignaturas[indiceEstudiante][i] << ": " << notaRedondeada << endl;
            sumaGeneral += calificaciones[indiceEstudiante][i];
            asignaturasConNotas++;
        }
    }

    if (asignaturasConNotas > 0)
    {
        float promedioGeneral = sumaGeneral / asignaturasConNotas;

        int tempPromedio = promedioGeneral * 100;
        float promedioRedondeado = tempPromedio / 100.0;

        cout << "\n--- PROMEDIO GENERAL ---" << endl;
        cout << "Promedio general: " << promedioRedondeado << endl;

        cout << "Estado: ";
        if (promedioRedondeado >= 6.0)
        {
            cout << "APROBADO" << endl;
        }
        else
        {
            cout << "REPROBADO" << endl;
        }
    }
    else
    {
        cout << "\nEl estudiante no tiene calificaciones registradas." << endl;
    }
}

void mostrarResumen(string estudiantes[], string asignaturas[][3], float calificaciones[][3], int contadorEstudiantes)
{
    if (contadorEstudiantes == 0)
    {
        cout << "No hay estudiantes registrados." << endl;
        return;
    }

    system("cls");
    cout << "\n=== RESUMEN GENERAL DEL SISTEMA ===" << endl;

    int aprobados = 0;
    int reprobados = 0;
    float mayorCalificacion = -1;
    float menorCalificacion = 11;
    string estudianteMayor, estudianteMenor;

    for (int i = 0; i < contadorEstudiantes; i++)
    {
        cout << "\n--- " << estudiantes[i] << " ---" << endl;

        float sumaEstudiante = 0;
        int materiasConNota = 0;

        for (int j = 0; j < 3; j++)
        {
            if (!asignaturas[i][j].empty())
            {
                float nota = calificaciones[i][j];
                int temporal = nota * 100;
                float notaRedondeada = temporal / 100.0;

                cout << asignaturas[i][j] << ": " << notaRedondeada << endl;
                sumaEstudiante += calificaciones[i][j];
                materiasConNota++;
            }
        }

        if (materiasConNota > 0)
        {
            float promedioEstudiante = sumaEstudiante / materiasConNota;

            int tempPromedio = promedioEstudiante * 100;
            float promedioRedondeado = tempPromedio / 100.0;

            cout << "PROMEDIO GENERAL: " << promedioRedondeado << " - ";

            if (promedioRedondeado >= 6.0)
            {
                cout << "APROBADO" << endl;
                aprobados++;
            }
            else
            {
                cout << "REPROBADO" << endl;
                reprobados++;
            }

            if (promedioRedondeado > mayorCalificacion)
            {
                mayorCalificacion = promedioRedondeado;
                estudianteMayor = estudiantes[i];
            }
            if (promedioRedondeado < menorCalificacion)
            {
                menorCalificacion = promedioRedondeado;
                estudianteMenor = estudiantes[i];
            }
        }
        else
        {
            cout << "Sin calificaciones registradas" << endl;
        }
        cout << "----------------------------" << endl;
    }

    cout << "\n=== ESTADISTICAS GENERALES ===" << endl;
    cout << "Total de estudiantes: " << contadorEstudiantes << endl;
    cout << "Estudiantes aprobados: " << aprobados << endl;
    cout << "Estudiantes reprobados: " << reprobados << endl;

    if (aprobados + reprobados > 0)
    {
        int tempMayor = mayorCalificacion * 100;
        int tempMenor = menorCalificacion * 100;

        cout << "Mejor promedio: " << estudianteMayor << " (" << (tempMayor / 100.0) << ")" << endl;
        cout << "Peor promedio: " << estudianteMenor << " (" << (tempMenor / 100.0) << ")" << endl;

        float porcentajeAprobados = (aprobados * 100.0) / (aprobados + reprobados);
        int tempPorcentaje = porcentajeAprobados * 100;
        cout << "Porcentaje de aprobados: " << (tempPorcentaje / 100.0) << "%" << endl;
    }
}
void menu(string estudiantes[], string asignaturas[][3], float calificaciones[][3], int &contadorEstudiantes)
{
    int opcion;
    bool validar = true;

    do
    {
        system("cls");
        cout << "\n=== SISTEMA DE CALIFICACIONES ===" << endl;
        cout << "1. Ingresar Estudiante" << endl;
        cout << "2. Calcular Promedio" << endl;
        cout << "3. Mostrar Resumen" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion:";

        while (!(cin >> opcion))
        {
            cout << "Ingrese opcion valida (1-4)" << endl;
            cout << "Opcion: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (opcion)
        {
        case 1:
            system("cls");
            ingresoEstudianteCompleto(estudiantes, asignaturas, calificaciones, contadorEstudiantes);
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        case 2:
            system("cls");
            calcularPromedio(estudiantes, asignaturas, calificaciones, contadorEstudiantes);
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        case 3:
            system("cls");
            mostrarResumen(estudiantes, asignaturas, calificaciones, contadorEstudiantes);
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            break;
        case 4:
            validar = false;
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            break;
        }
    } while (validar);
}

void parametros()
{
    string estudiantes[5];
    string asignaturas[5][3];
    float calificaciones[5][3];
    int contadorEstudiantes = 0;
    menu(estudiantes, asignaturas, calificaciones, contadorEstudiantes);
}

int main()
{
    parametros();
    return 0;
}