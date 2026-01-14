#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Función para calcular y guardar el factorial
void calcularFactorial(int numero) {
    ofstream archivoFactorial("factorial.txt", ios::out);
    
    if (!archivoFactorial.is_open()) {
        cout << "Error al abrir el archivo factorial.txt" << endl;
        return;
    }
    
    archivoFactorial << "Factorial de " << numero << ":" << endl;
    archivoFactorial << "==============================" << endl;
    
    long long factorial = 1;
    archivoFactorial << numero << "! = ";
    
    // Mostrar y calcular el factorial paso a paso
    for (int i = numero; i >= 1; i--) {
        archivoFactorial << i;
        factorial *= i;
        
        if (i > 1) {
            archivoFactorial << " × ";
        }
    }
    
    archivoFactorial << " = " << factorial << endl;
    
    archivoFactorial.close();
    
    cout << "Factorial calculado y guardado en factorial.txt" << endl;
}

// Función para calcular y guardar la tabla de multiplicar
void calcularTablaMultiplicar(int numero) {
    ofstream archivoTabla("tabla_multiplicar.txt");
    
    if (!archivoTabla.is_open()) {
        cout << "Error al abrir el archivo tabla_multiplicar.txt" << endl;
        return;
    }
    
    archivoTabla << "Tabla de multiplicar del " << numero << ":" << endl;
    archivoTabla << "==============================" << endl;
    
    // Calcular y mostrar la tabla de multiplicar
    for (int i = 1; i <= 10; i++) {
        archivoTabla << numero << " × " << i << " = " << numero * i << endl;
    }
    
    archivoTabla.close();
    
    cout << "Tabla de multiplicar guardada en tabla_multiplicar.txt" << endl;
}

int main() {
    int numero;
    
    cout << "PROGRAMA PARA CALCULAR FACTORIAL Y TABLA DE MULTIPLICAR" << endl;
    cout << "======================================================" << endl;
    
    cout << "\nIngrese un número entero positivo: ";
    cin >> numero;
    
    if (numero < 0) {
        cout << "Error: El número debe ser positivo." << endl;
        return 1;
    }
    
    // Advertencia para factoriales grandes
    if (numero > 20) {
        cout << "Advertencia: Factoriales mayores a 20 pueden causar desbordamiento." << endl;
    }
    
    // Calcular y guardar los resultados
    calcularFactorial(numero);
    calcularTablaMultiplicar(numero);
    
    cout << "\n======================================================" << endl;
    cout << "Resultados guardados exitosamente en los archivos:" << endl;
    cout << "- factorial.txt" << endl;
    cout << "- tabla_multiplicar.txt" << endl;
    cout << "======================================================" << endl;
    
    return 0;
}