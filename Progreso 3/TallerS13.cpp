#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

const string ARCHIVO_VEHICULOS = "vehiculos.dat";
const string ARCHIVO_CLIENTES = "clientes.dat";
const string ARCHIVO_VENTAS = "ventas.dat";

struct Vehiculo
{
    int id;
    string marca;
    string modelo;
    string tipo;
    int ano;
    string estado;
    float precio;
    bool disponible;
};

struct Cliente
{
    int id;
    string nombre;
    int edad;
    float presupuesto;
};

struct Venta
{
    int id;
    int idCliente;
    int idVehiculo;
    string fecha;
    float monto;
};

vector<Vehiculo> leerVehiculos()
{
    vector<Vehiculo> vehiculos;
    ifstream archivo(ARCHIVO_VEHICULOS, ios::binary);
    Vehiculo v;
    while (archivo.read((char *)&v, sizeof(Vehiculo)))
    {
        vehiculos.push_back(v);
    }
    archivo.close();
    return vehiculos;
}

vector<Cliente> leerClientes()
{
    vector<Cliente> clientes;
    ifstream archivo(ARCHIVO_CLIENTES, ios::binary);
    Cliente c;
    while (archivo.read((char *)&c, sizeof(Cliente)))
    {
        clientes.push_back(c);
    }
    archivo.close();
    return clientes;
}

vector<Venta> leerVentas()
{
    vector<Venta> ventas;
    ifstream archivo(ARCHIVO_VENTAS, ios::binary);
    Venta v;
    while (archivo.read((char *)&v, sizeof(Venta)))
    {
        ventas.push_back(v);
    }
    archivo.close();
    return ventas;
}

void guardarVehiculo(const Vehiculo &v)
{
    ofstream archivo(ARCHIVO_VEHICULOS, ios::binary | ios::app);
    archivo.write((char *)&v, sizeof(Vehiculo));
    archivo.close();
}

void guardarCliente(const Cliente &c)
{
    ofstream archivo(ARCHIVO_CLIENTES, ios::binary | ios::app);
    archivo.write((char *)&c, sizeof(Cliente));
    archivo.close();
}

void guardarVenta(const Venta &v)
{
    ofstream archivo(ARCHIVO_VENTAS, ios::binary | ios::app);
    archivo.write((char *)&v, sizeof(Venta));
    archivo.close();
}

// Funciones auxiliares
int obtenerNuevoIdVehiculo()
{
    vector<Vehiculo> vehiculos = leerVehiculos();
    if (vehiculos.empty())
        return 1;
    int maxId = 0;
    for (const auto &v : vehiculos)
    {
        if (v.id > maxId)
            maxId = v.id;
    }
    return maxId + 1;
}

int obtenerNuevoIdCliente()
{
    vector<Cliente> clientes = leerClientes();
    if (clientes.empty())
        return 1;
    int maxId = 0;
    for (const auto &c : clientes)
    {
        if (c.id > maxId)
            maxId = c.id;
    }
    return maxId + 1;
}

int obtenerNuevoIdVenta()
{
    vector<Venta> ventas = leerVentas();
    if (ventas.empty())
        return 1;
    int maxId = 0;
    for (const auto &v : ventas)
    {
        if (v.id > maxId)
            maxId = v.id;
    }
    return maxId + 1;
}

void mostrarVehiculo(const Vehiculo &v)
{
    cout << "ID: " << v.id << " | " << v.marca << " " << v.modelo
         << " | " << v.tipo << " | " << v.estado
         << " | $" << fixed << setprecision(2) << v.precio
         << " | " << (v.disponible ? "Disponible" : "Vendido") << endl;
}

void mostrarCliente(const Cliente &c)
{
    cout << "ID: " << c.id << " | " << c.nombre
         << " | Edad: " << c.edad
         << " | Presupuesto: $" << fixed << setprecision(2) << c.presupuesto << endl;
}

void mostrarVenta(const Venta &v)
{
    cout << "ID Venta: " << v.id << " | Cliente: " << v.idCliente
         << " | Vehiculo: " << v.idVehiculo << " | Fecha: " << v.fecha
         << " | Monto: $" << fixed << setprecision(2) << v.monto << endl;
}

// Funciones de gestión
void gestionarVehiculos()
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== GESTION DE VEHICULOS ===\n"
             << "1. Agregar nuevo vehiculo\n"
             << "2. Mostrar todos los vehiculos\n"
             << "3. Volver al menu principal\n"
             << "Seleccione: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1)
        {
            Vehiculo v;
            v.id = obtenerNuevoIdVehiculo();
            v.disponible = true;

            cout << "\n=== AGREGAR NUEVO VEHICULO ===\n";
            cout << "ID asignado: " << v.id << endl;
            cout << "Marca: ";
            getline(cin, v.marca);
            cout << "Modelo: ";
            getline(cin, v.modelo);
            cout << "Tipo: ";
            getline(cin, v.tipo);
            cout << "Ano: ";
            cin >> v.ano;
            cout << "Estado (Nuevo/Usado): ";
            cin.ignore();
            getline(cin, v.estado);
            cout << "Precio: $";
            cin >> v.precio;

            guardarVehiculo(v);
            cout << "\nVehiculo agregado exitosamente!\n";
        }
        else if (opcion == 2)
        {
            vector<Vehiculo> vehiculos = leerVehiculos();
            cout << "\n=== LISTA DE VEHICULOS (" << vehiculos.size() << ") ===\n";
            for (const auto &v : vehiculos)
                mostrarVehiculo(v);
        }

        if (opcion != 3)
        {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }
    } while (opcion != 3);
}

void gestionarClientes()
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== GESTION DE CLIENTES ===\n"
             << "1. Agregar nuevo cliente\n"
             << "2. Mostrar todos los clientes\n"
             << "3. Volver al menu principal\n"
             << "Seleccione: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1)
        {
            Cliente c;
            c.id = obtenerNuevoIdCliente();

            cout << "\n=== AGREGAR NUEVO CLIENTE ===\n";
            cout << "ID asignado: " << c.id << endl;
            cout << "Nombre: ";
            getline(cin, c.nombre);
            cout << "Edad: ";
            cin >> c.edad;
            cout << "Presupuesto: $";
            cin >> c.presupuesto;

            guardarCliente(c);
            cout << "\nCliente agregado exitosamente!\n";
        }
        else if (opcion == 2)
        {
            vector<Cliente> clientes = leerClientes();
            cout << "\n=== LISTA DE CLIENTES (" << clientes.size() << ") ===\n";
            for (const auto &c : clientes)
                mostrarCliente(c);
        }

        if (opcion != 3)
        {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }
    } while (opcion != 3);
}

void buscarVehiculos()
{
    system("cls");
    cout << "=== BUSQUEDA DE VEHICULOS ===\n";

    string marca, tipo, estado;
    float precioMax;

    cout << "Marca (deje vacio para cualquier): ";
    getline(cin, marca);
    cout << "Tipo (deje vacio para cualquier): ";
    getline(cin, tipo);
    cout << "Estado (Nuevo/Usado) (deje vacio para cualquier): ";
    getline(cin, estado);
    cout << "Precio maximo (0 para cualquier): $";
    cin >> precioMax;
    cin.ignore();

    vector<Vehiculo> vehiculos = leerVehiculos();
    vector<Vehiculo> resultados;

    for (const auto &v : vehiculos)
    {
        if (!v.disponible)
            continue;
        if (!marca.empty() && v.marca != marca)
            continue;
        if (!tipo.empty() && v.tipo != tipo)
            continue;
        if (!estado.empty() && v.estado != estado)
            continue;
        if (precioMax > 0 && v.precio > precioMax)
            continue;
        resultados.push_back(v);
    }

    cout << "\n=== RESULTADOS DE BUSQUEDA ===\n";
    if (resultados.empty())
    {
        cout << "No se encontraron vehiculos.\n";
    }
    else
    {
        cout << "Se encontraron " << resultados.size() << " vehiculo(s):\n";
        for (const auto &v : resultados)
            mostrarVehiculo(v);

        if (marca == "Chevrolet" && tipo == "camioneta" && estado == "Usado" && precioMax <= 14000)
        {
            cout << "\n=== VEHICULOS PARA RUBEN ===\n";
            cout << "Cumplen con: Chevrolet, camioneta, usada, menos de $14,000\n";
        }
    }
}

void gestionarVentas()
{
    int opcion;
    do
    {
        system("cls");
        cout << "=== GESTION DE VENTAS ===\n"
             << "1. Registrar nueva venta\n"
             << "2. Mostrar todas las ventas\n"
             << "3. Volver al menu principal\n"
             << "Seleccione: ";
        cin >> opcion;
        cin.ignore();

        if (opcion == 1)
        {
            Venta venta;
            venta.id = obtenerNuevoIdVenta();

            cout << "\n=== REGISTRAR NUEVA VENTA ===\n";
            cout << "ID Venta: " << venta.id << endl;

            // Mostrar clientes
            vector<Cliente> clientes = leerClientes();
            if (clientes.empty())
            {
                cout << "No hay clientes registrados.\n";
                return;
            }
            cout << "\nClientes:\n";
            for (const auto &c : clientes)
                mostrarCliente(c);
            cout << "ID del cliente: ";
            cin >> venta.idCliente;

            // Mostrar vehículos disponibles
            vector<Vehiculo> vehiculos = leerVehiculos();
            cout << "\nVehiculos disponibles:\n";
            for (const auto &v : vehiculos)
            {
                if (v.disponible)
                {
                    cout << "ID: " << v.id << " - " << v.marca << " "
                         << v.modelo << " - $" << v.precio << endl;
                }
            }
            cout << "ID del vehiculo: ";
            cin >> venta.idVehiculo;
            cin.ignore();
            cout << "Fecha (DD/MM/AAAA): ";
            getline(cin, venta.fecha);

            // Buscar y marcar vehículo como vendido
            float precioVenta = 0;
            for (auto &v : vehiculos)
            {
                if (v.id == venta.idVehiculo && v.disponible)
                {
                    precioVenta = v.precio;
                    v.disponible = false;
                    break;
                }
            }

            // Actualizar archivo de vehículos
            ofstream archivo(ARCHIVO_VEHICULOS, ios::binary | ios::trunc);
            for (const auto &v : vehiculos)
            {
                archivo.write((char *)&v, sizeof(Vehiculo));
            }
            archivo.close();

            venta.monto = precioVenta;
            guardarVenta(venta);
            cout << "\nVenta registrada! Monto: $" << fixed << setprecision(2) << venta.monto << endl;
        }
        else if (opcion == 2)
        {
            vector<Venta> ventas = leerVentas();
            cout << "\n=== VENTAS REGISTRADAS (" << ventas.size() << ") ===\n";
            for (const auto &v : ventas)
                mostrarVenta(v);
        }

        if (opcion != 3)
        {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }
    } while (opcion != 3);
}

void mostrarReportes()
{
    system("cls");
    cout << "=== REPORTES DEL SISTEMA ===\n\n";

    vector<Vehiculo> vehiculos = leerVehiculos();
    vector<Cliente> clientes = leerClientes();
    vector<Venta> ventas = leerVentas();

    int disponibles = 0;
    float totalInventario = 0, totalVentas = 0;

    for (const auto &v : vehiculos)
    {
        if (v.disponible)
        {
            disponibles++;
            totalInventario += v.precio;
        }
    }

    for (const auto &v : ventas)
    {
        totalVentas += v.monto;
    }

    cout << "Vehiculos registrados: " << vehiculos.size() << endl;
    cout << "Vehiculos disponibles: " << disponibles << endl;
    cout << "Valor del inventario: $" << fixed << setprecision(2) << totalInventario << endl;
    cout << "\nClientes registrados: " << clientes.size() << endl;
    cout << "Ventas realizadas: " << ventas.size() << endl;
    cout << "Total en ventas: $" << fixed << setprecision(2) << totalVentas << endl;
}

void mostrarMenuPrincipal()
{
    system("cls");
    cout << "========================================\n"
         << "   SISTEMA DE GESTION RUEDAS DE ORO\n"
         << "========================================\n"
         << "1. Gestionar Vehiculos\n"
         << "2. Gestionar Clientes\n"
         << "3. Buscar Vehiculos\n"
         << "4. Gestionar Ventas\n"
         << "5. Mostrar Reportes\n"
         << "6. Salir\n"
         << "========================================\n";
}

int main()
{
    int opcion;

    do
    {
        mostrarMenuPrincipal();
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
            gestionarVehiculos();
            break;
        case 2:
            gestionarClientes();
            break;
        case 3:
            buscarVehiculos();
            break;
        case 4:
            gestionarVentas();
            break;
        case 5:
            mostrarReportes();
            break;
        case 6:
            cout << "\nSaliendo del sistema...\n";
            break;
        default:
            cout << "\nOpcion no valida.\n";
        }

        if (opcion != 6)
        {
            cout << "\nPresione Enter para continuar...";
            cin.get();
        }
    } while (opcion != 6);

    return 0;
}