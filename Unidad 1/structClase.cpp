
#include <iostream>
#include <math.h>
using namespace std;

struct Fecha
{
    int dia;
    int mes;
    int anio;
};

Fecha fecha(int d, int m, int a)
{
    Fecha x = {d, m, a};
    return x;
}

struct Direccion
{
    int nro;
    string calle;
};

Direccion direccion(int n, string c)
{
    return {n, c};
}

struct Persona
{
    string nombre;
    Fecha fechaNacimiento;
    Direccion direccion;
};

Persona persona(string n, Fecha fn, Direccion d)
{
    return {n, fn, d};
}

string fechaToString(Fecha f)
{
    return to_string(f.dia) + "/" + to_string(f.mes) + "/" + to_string(f.anio);
}

string direccionToString(Direccion d)
{
    return d.calle + " " + to_string(d.nro);
}

string personaToString(Persona p)
{
    return p.nombre + ", " + fechaToString(p.fechaNacimiento) + ", " + direccionToString(p.direccion);
}

int main()
{
    Persona p = persona("Juan", fecha(2, 1, 1998), direccion(1234, "Fragata Sarmiento"));
    cout << personaToString(p) << endl;
    return 0;
}
