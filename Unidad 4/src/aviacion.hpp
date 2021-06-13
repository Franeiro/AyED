#ifndef _MAINHPP
#define _MAINHPP
#include <iostream>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/funciones/tokens.hpp"
#include "biblioteca/tads/Coll.hpp"
using namespace std;

struct Ciudad
{
    int idCiu;
    char descr[20];
    int millas;
};

string ciudadToString(Ciudad x)
{
    char sep = 1;
    string sIdCiu = to_string(x.idCiu);
    string sDescr = x.descr;
    string sMillas = to_string(x.millas);
    return sIdCiu + sep + sDescr + sep + sMillas;
}

Ciudad ciudadFromString(string s)
{
    char sep = 1;
    Ciudad x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCiu = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.descr, t1.c_str());
    string t2 = getTokenAt(s, sep, 2);
    x.millas = stoi(t2);
    return x;
}

string ciudadToDebug(Ciudad x)
{
    stringstream sout;
    sout << "[";
    sout << x.idCiu;
    sout << ",";
    sout << x.descr;
    sout << ",";
    sout << x.millas;
    sout << "]";
    return sout.str();
}

Ciudad ciudad(int idCiu, string descr, int millas)
{
    Ciudad a;
    a.idCiu = idCiu;
    strcpy(a.descr, descr.c_str());
    a.millas = millas;
    return a;
}

bool ciudadEquals(Ciudad a, Ciudad b)
{
    if (a.idCiu != b.idCiu)
        return false;
    if (a.millas != b.millas)
        return false;
    return true;
}

struct Vuelo
{
    int idVue;
    int cap;
    int idOri;
    int idDes;
};

string vueloToString(Vuelo x)
{
    char sep = 1;
    string sIdVue = to_string(x.idVue);
    string sCap = to_string(x.cap);
    string sIdOri = to_string(x.idOri);
    string sIdDes = to_string(x.idDes);
    return sIdVue + sep + sCap + sep + sIdOri + sep + sIdDes;
}

Vuelo vueloFromString(string s)
{
    char sep = 1;
    Vuelo x;
    string t0 = getTokenAt(s, sep, 0);
    x.idVue = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.cap = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.idOri = stoi(t2);
    string t3 = getTokenAt(s, sep, 3);
    x.idDes = stoi(t3);
    return x;
}

string vueloToDebug(Vuelo x)
{
    stringstream sout;
    sout << "[";
    sout << x.idVue;
    sout << ",";
    sout << x.cap;
    sout << ",";
    sout << x.idOri;
    sout << ",";
    sout << x.idDes;
    sout << "]";
    return sout.str();
}

Vuelo vuelo(int idVue, int cap, int idOri, int idDes)
{
    Vuelo a;
    a.idVue = idVue;
    a.cap = cap;
    a.idOri = idOri;
    a.idDes = idDes;
    return a;
}

bool vueloEquals(Vuelo a, Vuelo b)
{
    if (a.idVue != b.idVue)
        return false;
    if (a.cap != b.cap)
        return false;
    if (a.idOri != b.idOri)
        return false;
    if (a.idDes != b.idDes)
        return false;
    return true;
}

struct Reserva
{
    int idCli;
    int idVue;
    int cant;
};

string reservaToString(Reserva x)
{
    char sep = 1;
    string sIdCli = to_string(x.idCli);
    string sIdVue = to_string(x.idVue);
    string sCant = to_string(x.cant);
    return sIdCli + sep + sIdVue + sep + sCant;
}

Reserva reservaFromString(string s)
{
    char sep = 1;
    Reserva x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCli = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.idVue = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.cant = stoi(t2);
    return x;
}

string reservaToDebug(Reserva x)
{
    stringstream sout;
    sout << "[";
    sout << x.idCli;
    sout << ",";
    sout << x.idVue;
    sout << ",";
    sout << x.cant;
    sout << "]";
    return sout.str();
}

Reserva reserva(int idCli, int idVue, int cant)
{
    Reserva a;
    a.idCli = idCli;
    a.idVue = idVue;
    a.cant = cant;
    return a;
}

bool reservaEquals(Reserva a, Reserva b)
{
    if (a.idCli != b.idCli)
        return false;
    if (a.idVue != b.idVue)
        return false;
    if (a.cant != b.cant)
        return false;
    return true;
}

struct Rechazadas
{
    int idReservas;
    int cantidad;
    int idCliente;
};

string rechazadasToString(Rechazadas x)
{
    char sep = 1;
    string sIdReservas = to_string(x.idReservas);
    string sCantidad = to_string(x.cantidad);
    string sIdCliente = to_string(x.idCliente);
    return sIdReservas + sep + sCantidad + sep + sIdCliente;
}

Rechazadas rechazadasFromString(string s)
{
    char sep = 1;
    Rechazadas x;
    string t0 = getTokenAt(s, sep, 0);
    x.idReservas = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.cantidad = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.idCliente = stoi(t2);
    return x;
}

string rechazadasToDebug(Rechazadas x)
{
    stringstream sout;
    sout << "[";
    sout << x.idReservas;
    sout << ",";
    sout << x.cantidad;
    sout << ",";
    sout << x.idCliente;
    sout << "]";
    return sout.str();
}

Rechazadas rechazadas(int idReservas, int cantidad, int idCliente)
{
    Rechazadas a;
    a.idReservas = idReservas;
    a.cantidad = cantidad;
    a.idCliente = idCliente;
    return a;
}

bool rechazadasEquals(Rechazadas a, Rechazadas b)
{
    if (a.idReservas != b.idReservas)
        return false;
    if (a.cantidad != b.cantidad)
        return false;
    if (a.idCliente != b.idCliente)
        return false;
    return true;
}

#endif
