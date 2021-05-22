#include <iostream>
using namespace std;

int main()
{
    int sueldo, resto, a, b, c, d, e, f, g;

    cout << "Ingese su sueldo: ";
    cin >> sueldo;

    a = sueldo / 100;
    resto = sueldo % 100;
    b = resto / 50;
    resto = resto % 50;
    c = resto / 20;
    resto = resto % 20;
    d = resto / 10;
    resto = resto % 10;
    e = resto / 5;
    resto = resto % 5;
    f = resto / 2;
    resto = resto % 2;
    g = resto / 1;
    resto = resto % 1;

    cout << " Se le abonaran " << a << " billetes de 100 pesos" << endl;
    cout << " Se le abonaran " << b << " billetes de 50 pesos" << endl;
    cout << " Se le abonaran " << c << " billetes de 20 pesos" << endl;
    cout << " Se le abonaran " << d << " billetes de 10 pesos" << endl;
    cout << " Se le abonaran " << e << " billetes de 5 pesos" << endl;
    cout << " Se le abonaran " << f << " billetes de 2 pesos" << endl;
    cout << " Se le abonaran " << g << " billetes de 1 pesos" << endl;
}