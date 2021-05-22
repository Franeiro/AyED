
#ifndef _MAIN
#define _MAIN

#include <iostream>
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/funciones/tokens.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/Array.hpp"
#include "biblioteca/tads/Map.hpp"
#include "biblioteca/tads/List.hpp"
#include "biblioteca/tads/Stack.hpp"
#include "biblioteca/tads/Queue.hpp"
#include "biblioteca/tads/Coll.hpp"
using namespace std;

struct Fraccion
{
    int n, d;
};

Fraccion fraccion(int n, int d)
{
    Fraccion f = {n, d};

    return f;

    /*
    es lo mismo poner solamente return {n,d};
    */
}

Fraccion fraccionSumar(Fraccion a, Fraccion b)
{
    Fraccion x;

    x.d = (a.d * b.d);
    int aN = (a.n * b.d);
    int bN = (a.n * b.d);

    x.n = aN + bN;

    return x;
}

int _maximo(int a, int b) // el  _   establece que es una funcion privada no manipulable x el usuario
{
    return a > b ? a : b; // es un If. Si es true, returnea a. Sino, returnea b;
}

int _minimo(int a, int b)
{
    return a < b ? a : b; // es un If. Si es true, returnea a. Sino, returnea b;
}

Fraccion fraccionSimplificar(Fraccion f)
{
    /*Fraccion x = f;

     int min = minimo(x.n, x.d);
    int max = maximo(x.n, x.d);

    for (int i = min; i > 1; i--)
    {
        if (max % i == 0)
        {
            x.n = (x.n) / i;
            x.d = (x.d) / i;
        }
    }

    return x;*/
    bool fin = false;
    int i = 2;

    while (!fin)
    {
        if (f.n % i == 0 && f.d % i == 0)
        {
            f.n = f.n / i;
            f.d = f.d / i;
        }

        else
        {
            i++;
        }

        fin = i >= _minimo(f.n, f.d);
    }

    return f;
}

string fraccionToString(Fraccion f)
{
    return intToString(f.n) + "/" + intToString(f.d);
}

////// TAD  Fecha //////

struct Fecha
{
    int d, m, a;
};

Fecha fecha(int dia, int mes, int anio)
{
    Fecha x = {dia, mes, anio};

    return x;
}
bool chequearFecha(Fecha x)
{
    if (x.m > 12 || x.m < 1)
    {
        return false;
    }
    if (x.m == 4 || x.m == 6 || x.m == 9 || x.m == 11)
    {
        if (x.d > 30)
        {
            return false;
        }
    }
    if (x.m == 2)
    {
        if ((x.a % 4 == 0 && x.a % 100 != 0) || x.a % 400 == 0)
        {
            if (x.d > 29)
            {
                return false;
            }
        }
        else
        {
            if (x.d > 28)
            {
                return false;
            }
        }
    }
    else
    {
        if (x.d > 31)
        {
            return false;
        }
    }

    return true;
}

string fechaToString(Fecha x)
{
    bool condicion = chequearFecha(x);
    if (condicion)
    {
        return to_string(x.d) + "-" + to_string(x.m) + "-" + to_string(x.a);
    }
    else
    {
        return "La fecha ingresada es incorrecta";
    }
}

////// TAD  Hora //////

struct Hora
{
    int h, m, s;
};

Hora hora(int segundos, int minutos, int hora)
{
    Hora x = {segundos, minutos, hora};

    return x;
}

bool chequearHora(Hora x)
{
    if (x.h > 23 || x.m > 59 || x.s > 59 || x.h < 0 || x.m < 0 || x.s < 0)
    {
        return false;
    }
    if (digitCount(x.s) > 2 || digitCount(x.h) > 2 || digitCount(x.m) > 2)
    {
        return false;
    }

    else
    {
        return true;
    }
}

string appendUno(Hora x)
{
    if (digitCount(x.s) == 1)
    {
        return to_string(x.h) + ':' + to_string(x.m) + ':' + '0' + to_string(x.s);
    }
    if (digitCount(x.m) == 1)
    {
        return to_string(x.h) + ':' + '0' + to_string(x.m) + ':' + to_string(x.s);
    }
    if (digitCount(x.h) == 1)
    {
        return '0' + to_string(x.h) + ':' + to_string(x.m) + ':' + to_string(x.s);
    }
}

string horaToString(Hora x)
{
    bool fechaCorrecta = chequearHora(x);
    if (fechaCorrecta)
    {

        return to_string(x.h) + ':' + to_string(x.m) + ':' + to_string(x.s);
    }
    else
    {
        return "Horario ingresado incorrecto";
    }
}
int main()
{
    Hora x = hora(9, 40, 52);

    cout << horaToString(x) << endl;

    return 0;
}

#endif