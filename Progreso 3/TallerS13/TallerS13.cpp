#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// Constantes de archivos
const string ARCHIVO_VEHICULOS = "vehiculos.txt";
const string ARCHIVO_CLIENTES = "clientes.txt";
const string ARCHIVO_VENTAS = "ventas.txt";

// Estructuras usando string para facilitar manejo
struct Vehiculo {
    int id;
    string marca;
    string modelo;
    string tipo;
    int ano;
    string estado;
    float precio;
    bool disponible;
};

struct Cliente {
    int id;
    string nombre;
    int edad;
    float presupuesto;
};

struct Venta {
    int id;
    int idCliente;
    int idVehiculo;
    string fecha;
    float monto;
};

// --- UTILIDADES ---

void limpiarBuffer() {
    cin.ignore(10000, '\n');
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}

// --- LECTURA MANUAL DE ARCHIVOS (Sin sstream) ---

vector<Vehiculo> leerVehiculos() {
    vector<Vehiculo> lista;
    ifstream archivo(ARCHIVO_VEHICULOS);
    if (!archivo.is_open()) return lista;

    string id, marca, modelo, tipo, ano, estado, precio, disponible;
    while (getline(archivo, id, ',')) {
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

vector<Cliente> leerClientes() {
    vector<Cliente> lista;
    ifstream archivo(ARCHIVO_CLIENTES);
    if (!archivo.is_open()) return lista;

    string id, nombre, edad, presupuesto;
    while (getline(archivo, id, ',')) {
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

vector<Venta> leerVentas() {
    vector<Venta> lista;
    ifstream archivo(ARCHIVO_VENTAS);
    if (!archivo.is_open()) return lista;

    string id, idC, idV, fecha, monto;
    while (getline(archivo, id, ',')) {
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

// --- FUNCIONES DE ESCRITURA ---

void guardarTodosVehiculos(const vector<Vehiculo>& lista) {
    ofstream archivo(ARCHIVO_VEHICULOS);
    for (const auto& v : lista) {
        archivo << v.id << "," << v.marca << "," << v.modelo << "," << v.tipo << ","
                << v.ano << "," << v.estado << "," << fixed << setprecision(2) << v.precio << ","
                << (v.disponible ? "1" : "0") << endl;
    }
}

void guardarTodosClientes(const vector<Cliente>& lista) {
    ofstream archivo(ARCHIVO_CLIENTES);
    for (const auto& c : lista) {
        archivo << c.id << "," << c.nombre << "," << c.edad << "," 
                << fixed << setprecision(2) << c.presupuesto << endl;
    }
}

// --- GESTIÓN DE VEHÍCULOS ---

void gestionarVehiculos() {
    int op;
    do {
        limpiarPantalla();
        cout << "=== GESTION DE VEHICULOS ===\n1. Agregar\n2. Listar\n3. Volver\nOpcion: ";
        cin >> op; limpiarBuffer();
        if (op == 1) {
            vector<Vehiculo> lista = leerVehiculos();
            Vehiculo v;
            v.id = lista.empty() ? 1 : lista.back().id + 1;
            cout << "Marca: "; getline(cin, v.marca);
            cout << "Modelo: "; getline(cin, v.modelo);
            cout << "Tipo: "; getline(cin, v.tipo);
            cout << "Año: "; cin >> v.ano;
            cout << "Precio: "; cin >> v.precio; limpiarBuffer();
            cout << "Estado (Nuevo/Usado): "; getline(cin, v.estado);
            v.disponible = true;
            lista.push_back(v);
            guardarTodosVehiculos(lista);
            cout << "\nVehiculo registrado."; pausar();
        } else if (op == 2) {
            vector<Vehiculo> lista = leerVehiculos();
            cout << left << setw(5) << "ID" << setw(15) << "MARCA" << setw(15) << "MODELO" << "PRECIO" << endl;
            for (const auto& v : lista) {
                cout << left << setw(5) << v.id << setw(15) << v.marca << setw(15) << v.modelo << v.precio << (v.disponible ? " [D]" : " [V]") << endl;
            }
            pausar();
        }
    } while (op != 3);
}

// --- GESTIÓN DE CLIENTES ---

void gestionarClientes() {
    int op;
    do {
        limpiarPantalla();
        cout << "=== GESTION DE CLIENTES ===\n1. Agregar\n2. Listar\n3. Volver\nOpcion: ";
        cin >> op; limpiarBuffer();
        if (op == 1) {
            vector<Cliente> lista = leerClientes();
            Cliente c;
            c.id = lista.empty() ? 1 : lista.back().id + 1;
            cout << "Nombre: "; getline(cin, c.nombre);
            cout << "Edad: "; cin >> c.edad;
            cout << "Presupuesto: "; cin >> c.presupuesto; limpiarBuffer();
            lista.push_back(c);
            guardarTodosClientes(lista);
            cout << "\nCliente registrado."; pausar();
        } else if (op == 2) {
            vector<Cliente> lista = leerClientes();
            for (const auto& c : lista) cout << "ID: " << c.id << " | " << c.nombre << " | $" << c.presupuesto << endl;
            pausar();
        }
    } while (op != 3);
}

// --- GESTIÓN DE VENTAS ---

void gestionarVentas() {
    limpiarPantalla();
    vector<Vehiculo> vehiculos = leerVehiculos();
    vector<Cliente> clientes = leerClientes();
    vector<Venta> ventas = leerVentas();

    cout << "=== REGISTRAR VENTA ===\n";
    int idC, idV;
    cout << "ID Cliente: "; cin >> idC;
    cout << "ID Vehiculo: "; cin >> idV; limpiarBuffer();

    int idxV = -1;
    for(int i=0; i < vehiculos.size(); i++) {
        if(vehiculos[i].id == idV && vehiculos[i].disponible) idxV = i;
    }

    if (idxV != -1) {
        Venta vt;
        vt.id = ventas.empty() ? 1 : ventas.back().id + 1;
        vt.idCliente = idC;
        vt.idVehiculo = idV;
        vt.monto = vehiculos[idxV].precio;
        cout << "Fecha (DD/MM/AAAA): "; getline(cin, vt.fecha);

        vehiculos[idxV].disponible = false; // Modificar dato
        ventas.push_back(vt);

        guardarTodosVehiculos(vehiculos); // Sobrescribe porque hubo modificación
        ofstream archV(ARCHIVO_VENTAS, ios::app); // Agrega al final
        archV << vt.id << "," << vt.idCliente << "," << vt.idVehiculo << "," << vt.fecha << "," << vt.monto << endl;
        archV.close();

        cout << "\nVENTA REALIZADA CON EXITO.";
    } else {
        cout << "\nError: Vehiculo no encontrado o ya vendido.";
    }
    pausar();
}

// --- REPORTES ---

void mostrarReportes() {
    limpiarPantalla();
    vector<Vehiculo> v = leerVehiculos();
    vector<Venta> vt = leerVentas();
    float total = 0;
    for(const auto& s : vt) total += s.monto;

    cout << "=== REPORTE GENERAL ===\n";
    cout << "Total Vehiculos: " << v.size() << endl;
    cout << "Ventas Totales: " << vt.size() << endl;
    cout << "Monto Recaudado: $" << fixed << setprecision(2) << total << endl;
    pausar();
}

// --- MENU PRINCIPAL ---

int main() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "========================================\n"
             << "    SISTEMA DE GESTION RUEDAS DE ORO\n"
             << "========================================\n"
             << "1. Gestionar Vehiculos\n2. Gestionar Clientes\n3. Registrar Venta\n4. Reportes\n5. Salir\nOpcion: ";
        cin >> opcion; limpiarBuffer();

        switch (opcion) {
            case 1: gestionarVehiculos(); break;
            case 2: gestionarClientes(); break;
            case 3: gestionarVentas(); break;
            case 4: mostrarReportes(); break;
        }
    } while (opcion != 5);
    return 0;
}