#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_LIBROS = 10;

struct Libro
{
    string id;
    string titulo;
    string autor;
    string anoPublicacion;
    string estado;
};

bool validarIDUnico(const Libro biblioteca[], int totalLibros, const string &id)
{
    for (int i = 0; i < totalLibros; i++)
    {
        if (biblioteca[i].id == id)
        {
            return false;
        }
    }
    return true;
}

int buscarLibroPorID(const Libro biblioteca[], int totalLibros, const string &id)
{
    for (int i = 0; i < totalLibros; i++)
    {
        if (biblioteca[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

void mostrarMenu()
{
    cout << "\n================================"<<endl;
    cout << "   GESTION DE BIBLIOTECA"<<endl;
    cout << "================================"<<endl;
    cout << "1. Registrar nuevo libro"<<endl;
    cout << "2. Mostrar todos los libros"<<endl;
    cout << "3. Buscar libro"<<endl;
    cout << "4. Actualizar estado"<<endl;
    cout << "5. Eliminar libro"<<endl;
    cout << "6. Salir"<<endl;
    cout << "================================"<<endl;
}

bool esNumero(const string &str)
{
    if (str.empty())
        return false;
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

void registrarLibro(Libro biblioteca[], int &totalLibros)
{
    if (totalLibros >= MAX_LIBROS)
    {
        cout << "\nError: Biblioteca llena (max " << MAX_LIBROS << " libros)\n";
        return;
    }

    cout << "\n--- REGISTRAR LIBRO ---\n";

    string id;
    bool idValido = false;

    // Validación del ID
    while (!idValido)
    {
        cout << "ID del libro: ";
        cin >> id;

        if (!esNumero(id))
        {
            cout << "Error: El ID debe contener solo numeros\n";
        }
        else if (!validarIDUnico(biblioteca, totalLibros, id))
        {
            cout << "Error: Este ID ya existe\n";
        }
        else
        {
            idValido = true;
        }
    }

    cin.ignore(); // Limpiar buffer

    string titulo;
    cout << "Titulo: ";
    getline(cin, titulo);

    string autor;
    cout << "Autor: ";
    getline(cin, autor);

    string ano;
    bool anoValido = false;

    // Validación del año
    while (!anoValido)
    {
        cout << "Ano de publicacion: ";
        cin >> ano;

        if (!esNumero(ano))
        {
            cout << "Error: El ano debe contener solo numeros\n";
        }
        else
        {
            // Verificar rango del año
            int anoNum = 0;
            for (int i = 0; i < ano.length(); i++)
            {
                anoNum = anoNum * 10 + (ano[i] - '0');
            }

            if (anoNum < 0 || anoNum > 2024)
            {
                cout << "Error: Ingrese un ano valido (0-2024)\n";
            }
            else
            {
                anoValido = true;
            }
        }
    }

    biblioteca[totalLibros].id = id;
    biblioteca[totalLibros].titulo = titulo;
    biblioteca[totalLibros].autor = autor;
    biblioteca[totalLibros].anoPublicacion = ano;
    biblioteca[totalLibros].estado = "Disponible";

    totalLibros++;
    cout << "\nLibro registrado exitosamente!\n";
}

void mostrarLibros(const Libro biblioteca[], int totalLibros)
{
    if (totalLibros == 0)
    {
        cout << "\nNo hay libros registrados\n";
        return;
    }

    cout << "\n--- LISTA DE LIBROS ---\n";
    cout << "============================================================\n";
    cout << left << setw(8) << "ID"
         << setw(25) << "TITULO"
         << setw(20) << "AUTOR"
         << setw(8) << "ANO"
         << setw(12) << "ESTADO" << "\n";
    cout << "============================================================\n";

    for (int i = 0; i < totalLibros; i++)
    {
        cout << left << setw(8) << biblioteca[i].id
             << setw(25) << (biblioteca[i].titulo.length() > 22 ? biblioteca[i].titulo.substr(0, 22) + "..." : biblioteca[i].titulo)
             << setw(20) << (biblioteca[i].autor.length() > 17 ? biblioteca[i].autor.substr(0, 17) + "..." : biblioteca[i].autor)
             << setw(8) << biblioteca[i].anoPublicacion
             << setw(12) << biblioteca[i].estado << "\n";
    }
    cout << "============================================================\n";
    cout << "Total: " << totalLibros << "/" << MAX_LIBROS << " libros\n";
}

void buscarLibro(const Libro biblioteca[], int totalLibros)
{
    if (totalLibros == 0)
    {
        cout << "\nNo hay libros registrados\n";
        return;
    }

    int opcion;
    cout << "\n--- BUSCAR LIBRO ---\n";
    cout << "1. Buscar por ID\n";
    cout << "2. Buscar por titulo (exacto)\n";
    cout << "3. Buscar por autor (exacto)\n";
    cout << "Seleccione: ";
    cin >> opcion;
    cin.ignore();

    if (opcion == 1)
    {
        string id;
        cout << "Ingrese ID: ";
        cin >> id;

        int indice = buscarLibroPorID(biblioteca, totalLibros, id);

        if (indice != -1)
        {
            cout << "\n--- LIBRO ENCONTRADO ---\n";
            cout << "ID: " << biblioteca[indice].id << endl;
            cout << "Titulo: " << biblioteca[indice].titulo << endl;
            cout << "Autor: " << biblioteca[indice].autor << endl;
            cout << "Ano: " << biblioteca[indice].anoPublicacion << endl;
            cout << "Estado: " << biblioteca[indice].estado << endl;
        }
        else
        {
            cout << "\nLibro no encontrado\n";
        }
    }
    else if (opcion == 2)
    {
        string titulo;
        cout << "Ingrese titulo exacto: ";
        getline(cin, titulo);

        bool encontrado = false;

        for (int i = 0; i < totalLibros; i++)
        {
            if (biblioteca[i].titulo == titulo)
            { // Comparación EXACTA
                cout << "\n--- LIBRO ENCONTRADO ---\n";
                cout << "ID: " << biblioteca[i].id << endl;
                cout << "Titulo: " << biblioteca[i].titulo << endl;
                cout << "Autor: " << biblioteca[i].autor << endl;
                cout << "Ano: " << biblioteca[i].anoPublicacion << endl;
                cout << "Estado: " << biblioteca[i].estado << endl;
                encontrado = true;
                break; // Solo muestra el primero que encuentre
            }
        }

        if (!encontrado)
        {
            cout << "\nLibro no encontrado\n";
        }
    }
    else if (opcion == 3)
    {
        string autor;
        cout << "Ingrese autor exacto: ";
        getline(cin, autor);

        bool encontrado = false;

        for (int i = 0; i < totalLibros; i++)
        {
            if (biblioteca[i].autor == autor)
            { // Comparación EXACTA
                cout << "\n--- LIBRO ENCONTRADO ---\n";
                cout << "ID: " << biblioteca[i].id << endl;
                cout << "Titulo: " << biblioteca[i].titulo << endl;
                cout << "Autor: " << biblioteca[i].autor << endl;
                cout << "Ano: " << biblioteca[i].anoPublicacion << endl;
                cout << "Estado: " << biblioteca[i].estado << endl;
                encontrado = true;
                break; // Solo muestra el primero que encuentre
            }
        }

        if (!encontrado)
        {
            cout << "\nLibro no encontrado\n";
        }
    }
    else
    {
        cout << "Opcion no valida\n";
    }
}

void actualizarEstado(Libro biblioteca[], int totalLibros)
{
    if (totalLibros == 0)
    {
        cout << "\nNo hay libros registrados\n";
        return;
    }

    cout << "\n--- ACTUALIZAR ESTADO ---\n";

    string id;
    cout << "Ingrese ID del libro: ";
    cin >> id;

    int indice = buscarLibroPorID(biblioteca, totalLibros, id);

    if (indice != -1)
    {
        cout << "\nLibro: " << biblioteca[indice].titulo << endl;
        cout << "Estado actual: " << biblioteca[indice].estado << endl;

        int opcion;
        cout << "\nNuevo estado:\n";
        cout << "1. Disponible\n";
        cout << "2. Prestado\n";
        cout << "Seleccione: ";
        cin >> opcion;

        if (opcion == 1)
        {
            biblioteca[indice].estado = "Disponible";
            cout << "Estado actualizado a: Disponible\n";
        }
        else if (opcion == 2)
        {
            biblioteca[indice].estado = "Prestado";
            cout << "Estado actualizado a: Prestado\n";
        }
        else
        {
            cout << "Opcion no valida\n";
        }
    }
    else
    {
        cout << "\nLibro no encontrado\n";
    }
}

void eliminarLibro(Libro biblioteca[], int &totalLibros)
{
    if (totalLibros == 0)
    {
        cout << "\nNo hay libros registrados\n";
        return;
    }

    cout << "\n--- ELIMINAR LIBRO ---\n";

    string id;
    cout << "Ingrese ID del libro a eliminar: ";
    cin >> id;

    int indice = buscarLibroPorID(biblioteca, totalLibros, id);

    if (indice != -1)
    {
        cout << "\nLibro a eliminar:\n";
        cout << "Titulo: " << biblioteca[indice].titulo << endl;
        cout << "Autor: " << biblioteca[indice].autor << endl;

        char confirmar;
        cout << "\n¿Seguro que desea eliminar? (s/n): ";
        cin >> confirmar;

        if (confirmar == 's' || confirmar == 'S')
        {
            for (int i = indice; i < totalLibros - 1; i++)
            {
                biblioteca[i] = biblioteca[i + 1];
            }
            totalLibros--;
            cout << "Libro eliminado\n";
        }
        else
        {
            cout << "Cancelado\n";
        }
    }
    else
    {
        cout << "\nLibro no encontrado\n";
    }
}

int main()
{
    Libro biblioteca[MAX_LIBROS];
    int totalLibros = 0;
    int opcion;

    do
    {
        mostrarMenu();
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            registrarLibro(biblioteca, totalLibros);
            break;
        case 2:
            mostrarLibros(biblioteca, totalLibros);
            break;
        case 3:
            buscarLibro(biblioteca, totalLibros);
            break;
        case 4:
            actualizarEstado(biblioteca, totalLibros);
            break;
        case 5:
            eliminarLibro(biblioteca, totalLibros);
            break;
        case 6:
            cout << "\nSaliendo del sistema...\n";
            break;
        default:
            cout << "\nOpcion no valida!\n";
        }

    } while (opcion != 6);

    return 0;
}