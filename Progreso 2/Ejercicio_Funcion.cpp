#include <iostream>
using namespace std;

void intercambio(int &num1, int &num2)
{
    int aux;
    aux = num1;
    num1 = num2;
    num2 = aux;

    cout << num1 << "--" << num2 << endl;
}

int main()
{
    int num1 = 6;
    int num2 = 4;
    intercambio(num1, num2);
    return 0;
}