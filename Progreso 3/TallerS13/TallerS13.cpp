#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <cstdlib>

using namespace std;

const string ARCHIVO_VEHICULOS = "vehiculos.txt";
const string ARCHIVO_CLIENTES = "clientes.txt";
const string ARCHIVO_VENTAS = "ventas.txt";

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

int leerEnteroValido(const string& mensaje, int min, int max) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            if (valor >= min && valor <= max) {
                cin.ignore(10000, '\n');
                return valor;
            } else {
                cout << "Error: Debe ser entre " << min << " y " << max << endl;
            }
        } else {
            cout << "Error: Ingrese un numero valido" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

float leerFloatValido(const string& mensaje, float min = 0) {
    float valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            if (valor >= min) {
                cin.ignore(10000, '\n');
                return valor;
            } else {
                cout << "Error: El valor debe ser mayor o igual a " << min << endl;
            }
        } else {
            cout << "Error: Ingrese un numero valido" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

string leerString(const string& mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar()
{
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

vector<Vehiculo> leerVehiculos()
{
    vector<Vehiculo> lista;
    ifstream archivo(ARCHIVO_VEHICULOS);
    if (!archivo.is_open())
        return lista;

    string id, marca, modelo, tipo, ano, estado, precio, disponible;
    while (getline(archivo, id, ','))
    {
        Vehiculo v;
        v.id = stoi(id);
        getline(archivo, v.marca, ',');
        getline(archivo, v.modelo, ',');
        getline(archivo, v.tipo, ',');
        getline(archivo, ano, ',');
        v.ano = stoi(ano);
        getline(archivo, v.estado, ',');
        getline(archivo, precio, ',');
        v.precio = stof(precio);
        getline(archivo, disponible, '\n');
        v.disponible = (disponible == "1");
        lista.push_back(v);
    }
    archivo.close();
    return lista;
}

vector<Cliente> leerClientes()
{
    vector<Cliente> lista;
    ifstream archivo(ARCHIVO_CLIENTES);
    if (!archivo.is_open())
        return lista;

    string id, nombre, edad, presupuesto;
    while (getline(archivo, id, ','))
    {
        Cliente c;
        c.id = stoi(id);
        getline(archivo, c.nombre, ',');
        getline(archivo, edad, ',');
        c.edad = stoi(edad);
        getline(archivo, presupuesto, '\n');
        c.presupuesto = stof(presupuesto);
        lista.push_back(c);
    }
    archivo.close();
    return lista;
}

vector<Venta> leerVentas()
{
    vector<Venta> lista;
    ifstream archivo(ARCHIVO_VENTAS);
    if (!archivo.is_open())
        return lista;

    string id, idC, idV, fecha, monto;
    while (getline(archivo, id, ','))
    {
        Venta vt;
        vt.id = stoi(id);
        getline(archivo, idC, ',');
        vt.idCliente = stoi(idC);
        getline(archivo, idV, ',');
        vt.idVehiculo = stoi(idV);
        getline(archivo, vt.fecha, ',');
        getline(archivo, monto, '\n');
        vt.monto = stof(monto);
        lista.push_back(vt);
    }
    archivo.close();
    return lista;
}

void guardarTodosVehiculos(const vector<Vehiculo> &lista)
{
    ofstream archivo(ARCHIVO_VEHICULOS);
    for (const auto &v : lista)
    {
        archivo << v.id << "," << v.marca << "," << v.modelo << "," << v.tipo << ","
                << v.ano << "," << v.estado << "," << fixed << setprecision(2) << v.precio << ","
                << (v.disponible ? "1" : "0") << endl;
    }
}

void guardarTodosClientes(const vector<Cliente> &lista)
{
    ofstream archivo(ARCHIVO_CLIENTES);
    for (const auto &c : lista)
    {
        archivo << c.id << "," << c.nombre << "," << c.edad << ","
                << fixed << setprecision(2) << c.presupuesto << endl;
    }
}

void buscarVehiculo()
{
    limpiarPantalla();
    vector<Vehiculo> lista = leerVehiculos();
    string criterio;
    bool encontrado = false;

    cout << "=== BUSQUEDA DE VEHICULO ===\n";
    cout << "Ingrese la MARCA: ";
    getline(cin, criterio);

    cout << "\nResultados:\n";
    cout << left << setw(5) << "ID" << setw(15) << "MARCA" << setw(15) << "MODELO" 
         << setw(10) << "TIPO" << setw(8) << "ANO" << setw(12) << "PRECIO" << "ESTADO" << endl;
    cout << "----------------------------------------------------------\n";

    for (const auto &v : lista)
    {
        if (v.marca == criterio)
        {
            cout << left << setw(5) << v.id << setw(15) << v.marca << setw(15) << v.modelo 
                 << setw(10) << v.tipo << setw(8) << v.ano << "$" << setw(11) << v.precio 
                 << (v.disponible ? " [DISPONIBLE]" : " [VENDIDO]") << endl;
            encontrado = true;
        }
    }

    if (!encontrado)
    {
        cout << "\nError: No se encontro ninguna coincidencia exacta para: " << criterio << endl;
    }
    pausar();
}

void gestionarVehiculos()
{
    int op;
    do
    {
        limpiarPantalla();
        cout << "=== GESTION DE VEHICULOS ===\n";
        cout << "1. Agregar vehiculo\n";
        cout << "2. Listar todos los vehiculos\n";
        cout << "3. Buscar por marca\n";
        cout << "4. Volver al menu principal\n";
        
        op = leerEnteroValido("Seleccione una opcion: ", 1, 4);
        
        if (op == 1)
        {
            vector<Vehiculo> lista = leerVehiculos();
            Vehiculo v;
            v.id = lista.empty() ? 1 : lista.back().id + 1;
            
            cout << "\n=== AGREGAR NUEVO VEHICULO ===\n";
            v.marca = leerString("Marca: ");
            v.modelo = leerString("Modelo: ");
            v.tipo = leerString("Tipo: ");
            v.ano = leerEnteroValido("Ano: ", 1900, 2100);
            v.precio = leerFloatValido("Precio: $", 0);
            v.estado = leerString("Estado (Nuevo/Usado): ");
            v.disponible = true;
            
            lista.push_back(v);
            guardarTodosVehiculos(lista);
            cout << "\nVehiculo registrado exitosamente con ID: " << v.id << endl;
            pausar();
        }
        else if (op == 2)
        {
            vector<Vehiculo> lista = leerVehiculos();
            cout << "\n=== LISTA DE VEHICULOS ===\n";
            cout << left << setw(5) << "ID" << setw(15) << "MARCA" << setw(15) << "MODELO" 
                 << setw(10) << "TIPO" << setw(8) << "ANO" << setw(12) << "PRECIO" << "ESTADO" << endl;
            cout << string(70, '-') << endl;
            
            for (const auto &v : lista)
            {
                cout << left << setw(5) << v.id << setw(15) << v.marca << setw(15) << v.modelo 
                     << setw(10) << v.tipo << setw(8) << v.ano << "$" << setw(11) << v.precio 
                     << (v.disponible ? " [DISPONIBLE]" : " [VENDIDO]") << endl;
            }
            cout << "\nTotal de vehiculos: " << lista.size() << endl;
            pausar();
        }
        else if (op == 3)
        {
            buscarVehiculo();
        }
    } while (op != 4);
}

void gestionarClientes()
{
    int op;
    do
    {
        limpiarPantalla();
        cout << "=== GESTION DE CLIENTES ===\n";
        cout << "1. Agregar cliente\n";
        cout << "2. Listar todos los clientes\n";
        cout << "3. Volver al menu principal\n";
        
        op = leerEnteroValido("Seleccione una opcion: ", 1, 3);
        
        if (op == 1)
        {
            vector<Cliente> lista = leerClientes();
            Cliente c;
            c.id = lista.empty() ? 1 : lista.back().id + 1;
            
            cout << "\n=== AGREGAR NUEVO CLIENTE ===\n";
            c.nombre = leerString("Nombre completo: ");
            c.edad = leerEnteroValido("Edad: ", 1, 120);
            c.presupuesto = leerFloatValido("Presupuesto: $", 0);
            
            lista.push_back(c);
            guardarTodosClientes(lista);
            cout << "\nCliente registrado exitosamente con ID: " << c.id << endl;
            pausar();
        }
        else if (op == 2)
        {
            vector<Cliente> lista = leerClientes();
            cout << "\n=== LISTA DE CLIENTES ===\n";
            cout << left << setw(5) << "ID" << setw(25) << "NOMBRE" 
                 << setw(8) << "EDAD" << "PRESUPUESTO" << endl;
            cout << string(50, '-') << endl;
            
            for (const auto &c : lista)
            {
                cout << left << setw(5) << c.id << setw(25) << c.nombre 
                     << setw(8) << c.edad << "$" << c.presupuesto << endl;
            }
            cout << "\nTotal de clientes: " << lista.size() << endl;
            pausar();
        }
    } while (op != 3);
}

void gestionarVentas()
{
    limpiarPantalla();
    vector<Vehiculo> vehiculos = leerVehiculos();
    vector<Cliente> clientes = leerClientes();
    vector<Venta> ventas = leerVentas();

    cout << "=== REGISTRAR VENTA ===\n\n";
    
    cout << "=== VEHICULOS DISPONIBLES ===\n";
    cout << left << setw(5) << "ID" << setw(15) << "MARCA" 
         << setw(15) << "MODELO" << setw(10) << "TIPO" 
         << setw(8) << "ANO" << setw(12) << "PRECIO" << endl;
    cout << string(70, '-') << endl;
    
    bool hayDisponibles = false;
    for (const auto &v : vehiculos)
    {
        if (v.disponible)
        {
            cout << left << setw(5) << v.id << setw(15) << v.marca 
                 << setw(15) << v.modelo << setw(10) << v.tipo 
                 << setw(8) << v.ano << "$" << v.precio << endl;
            hayDisponibles = true;
        }
    }
    
    if (!hayDisponibles)
    {
        cout << "\nNO HAY VEHICULOS DISPONIBLES PARA LA VENTA\n";
        pausar();
        return;
    }
    
    cout << "\n";
    
    cout << "=== CLIENTES REGISTRADOS ===\n";
    cout << left << setw(5) << "ID" << setw(25) << "NOMBRE" 
         << setw(8) << "EDAD" << "PRESUPUESTO" << endl;
    cout << string(50, '-') << endl;
    
    if (clientes.empty())
    {
        cout << "\nNO HAY CLIENTES REGISTRADOS\n";
        cout << "Debe registrar clientes antes de realizar ventas\n";
        pausar();
        return;
    }
    
    for (const auto &c : clientes)
    {
        cout << left << setw(5) << c.id << setw(25) << c.nombre 
             << setw(8) << c.edad << "$" << c.presupuesto << endl;
    }
    
    cout << "\n";
    
    int idC = -1;
    Cliente* clienteSeleccionado = nullptr;
    
    while (true)
    {
        cout << "ID del Cliente (0 para cancelar): ";
        if (cin >> idC)
        {
            if (idC == 0)
            {
                cout << "Operacion cancelada.\n";
                cin.ignore(10000, '\n');
                pausar();
                return;
            }
            
            for (auto &c : clientes)
            {
                if (c.id == idC)
                {
                    clienteSeleccionado = &c;
                    break;
                }
            }
            
            if (clienteSeleccionado != nullptr)
            {
                break;
            }
            else
            {
                cout << "Error: Cliente con ID " << idC << " no encontrado.\n";
                cout << "Por favor, ingrese un ID valido de la lista.\n";
            }
        }
        else
        {
            cout << "Error: Ingrese un numero valido.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    int idV = -1;
    Vehiculo* vehiculoSeleccionado = nullptr;
    
    while (true)
    {
        cout << "ID del Vehiculo (0 para cancelar): ";
        if (cin >> idV)
        {
            if (idV == 0)
            {
                cout << "Operacion cancelada.\n";
                cin.ignore(10000, '\n');
                pausar();
                return;
            }
            
            for (auto &v : vehiculos)
            {
                if (v.id == idV && v.disponible)
                {
                    vehiculoSeleccionado = &v;
                    break;
                }
            }
            
            if (vehiculoSeleccionado != nullptr)
            {
                break;
            }
            else
            {
                cout << "Error: Vehiculo con ID " << idV << " no encontrado o no disponible.\n";
                cout << "Por favor, ingrese un ID valido de la lista de disponibles.\n";
            }
        }
        else
        {
            cout << "Error: Ingrese un numero valido.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    cin.ignore(10000, '\n');
    
    if (clienteSeleccionado->presupuesto < vehiculoSeleccionado->precio)
    {
        cout << "\nERROR: Presupuesto insuficiente\n";
        cout << "Presupuesto del cliente: $" << clienteSeleccionado->presupuesto << endl;
        cout << "Precio del vehiculo: $" << vehiculoSeleccionado->precio << endl;
        cout << "Faltan: $" << (vehiculoSeleccionado->precio - clienteSeleccionado->presupuesto) << endl;
        pausar();
        return;
    }
    
    cout << "\n=== CONFIRMAR VENTA ===\n";
    cout << "Cliente: " << clienteSeleccionado->nombre << " (ID: " << clienteSeleccionado->id << ")\n";
    cout << "Vehiculo: " << vehiculoSeleccionado->marca << " " << vehiculoSeleccionado->modelo 
         << " (ID: " << vehiculoSeleccionado->id << ")\n";
    cout << "Precio: $" << vehiculoSeleccionado->precio << endl;
    
    string fecha = leerString("Fecha de venta (DD/MM/AAAA): ");
    
    char confirmar;
    cout << "\n¿Confirmar venta? (S/N): ";
    cin >> confirmar;
    cin.ignore(10000, '\n');
    
    if (toupper(confirmar) != 'S')
    {
        cout << "Venta cancelada.\n";
        pausar();
        return;
    }
    
    Venta vt;
    vt.id = ventas.empty() ? 1 : ventas.back().id + 1;
    vt.idCliente = idC;
    vt.idVehiculo = idV;
    vt.fecha = fecha;
    vt.monto = vehiculoSeleccionado->precio;
    
    vehiculoSeleccionado->disponible = false;
    clienteSeleccionado->presupuesto -= vehiculoSeleccionado->precio;
    
    guardarTodosVehiculos(vehiculos);
    guardarTodosClientes(clientes);
    
    ofstream archV(ARCHIVO_VENTAS, ios::app);
    archV << vt.id << "," << vt.idCliente << "," << vt.idVehiculo << "," 
          << vt.fecha << "," << vt.monto << endl;
    archV.close();
    
    cout << "\n========================================\n";
    cout << "     VENTA REGISTRADA EXITOSAMENTE!\n";
    cout << "========================================\n";
    cout << "Numero de venta: " << vt.id << endl;
    cout << "Cliente: " << clienteSeleccionado->nombre << endl;
    cout << "Vehiculo: " << vehiculoSeleccionado->marca << " " << vehiculoSeleccionado->modelo << endl;
    cout << "Monto: $" << vt.monto << endl;
    cout << "Fecha: " << vt.fecha << endl;
    cout << "Nuevo presupuesto del cliente: $" << clienteSeleccionado->presupuesto << endl;
    cout << "========================================\n";
    
    pausar();
}

void mostrarReportes()
{
    limpiarPantalla();
    vector<Vehiculo> vehiculos = leerVehiculos();
    vector<Cliente> clientes = leerClientes();
    vector<Venta> ventas = leerVentas();
    
    float totalVentas = 0;
    int vehiculosDisponibles = 0;
    int vehiculosVendidos = 0;
    
    for (const auto &v : vehiculos)
    {
        if (v.disponible)
            vehiculosDisponibles++;
        else
            vehiculosVendidos++;
    }
    
    for (const auto &vt : ventas)
        totalVentas += vt.monto;
    
    cout << "=== REPORTE GENERAL ===\n\n";
    cout << "INVENTARIO DE VEHICULOS:\n";
    cout << "  Total registrados: " << vehiculos.size() << endl;
    cout << "  Disponibles: " << vehiculosDisponibles << endl;
    cout << "  Vendidos: " << vehiculosVendidos << endl;
    
    cout << "\nCLIENTES:\n";
    cout << "  Total registrados: " << clientes.size() << endl;
    
    cout << "\nVENTAS:\n";
    cout << "  Total ventas: " << ventas.size() << endl;
    cout << "  Monto total recaudado: $" << fixed << setprecision(2) << totalVentas << endl;
    
    if (!ventas.empty())
    {
        cout << "\nULTIMAS 5 VENTAS:\n";
        cout << left << setw(8) << "ID VENTA" << setw(10) << "ID CLIENTE" 
             << setw(12) << "ID VEHICULO" << setw(12) << "MONTO" << "FECHA" << endl;
        cout << string(50, '-') << endl;
        
        int inicio = (ventas.size() > 5) ? ventas.size() - 5 : 0;
        for (int i = inicio; i < (int)ventas.size(); i++)
        {
            cout << left << setw(8) << ventas[i].id 
                 << setw(10) << ventas[i].idCliente
                 << setw(12) << ventas[i].idVehiculo
                 << "$" << setw(11) << ventas[i].monto
                 << ventas[i].fecha << endl;
        }
    }
    
    pausar();
}

int main()
{
    int opcion;
    do
    {
        limpiarPantalla();
        cout << "========================================\n"
             << "    SISTEMA DE GESTION RUEDAS DE ORO\n"
             << "========================================\n"
             << "1. Gestionar Vehiculos\n"
             << "2. Gestionar Clientes\n"
             << "3. Registrar Venta\n"
             << "4. Reportes\n"
             << "5. Salir\n";
        
        opcion = leerEnteroValido("Seleccione una opcion: ", 1, 5);
        
        switch (opcion)
        {
        case 1:
            gestionarVehiculos();
            break;
        case 2:
            gestionarClientes();
            break;
        case 3:
            gestionarVentas();
            break;
        case 4:
            mostrarReportes();
            break;
        case 5:
            cout << "\nGracias por usar el sistema. ¡Hasta luego!\n";
            break;
        }
    } while (opcion != 5);
    
    return 0;
}