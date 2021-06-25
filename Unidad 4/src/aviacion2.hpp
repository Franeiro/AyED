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
    string descr;
    int millas;
};

struct Vuelo
{
    int idVue;
    int cap;
    int idOri;
    int idDes;
};

struct Reservas
{
    int idCli;
    int idVue;
    int cant;
};

struct RegistroCliente
{
    int idCliente;
    int millasAcumuladas;
};

struct RegistroCiudad
{
    Ciudad unaCiudad;
    int contador;
};

struct RegistroVuelo
{
    Vuelo unVuelo;
    int acumulador;
};

// --------------------------------------

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
    x.descr = t1;
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
    a.descr = descr;
    a.millas = millas;
    return a;
}

bool ciudadEquals(Ciudad a, Ciudad b)
{
    if (a.idCiu != b.idCiu)
        return false;
    if (a.descr != b.descr)
        return false;
    if (a.millas != b.millas)
        return false;
    return true;
}

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

string reservasToString(Reservas x)
{
    char sep = 1;
    string sIdCli = to_string(x.idCli);
    string sIdVue = to_string(x.idVue);
    string sCant = to_string(x.cant);
    return sIdCli + sep + sIdVue + sep + sCant;
}

Reservas reservasFromString(string s)
{
    char sep = 1;
    Reservas x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCli = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.idVue = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.cant = stoi(t2);
    return x;
}

string reservasToDebug(Reservas x)
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

Reservas reservas(int idCli, int idVue, int cant)
{
    Reservas a;
    a.idCli = idCli;
    a.idVue = idVue;
    a.cant = cant;
    return a;
}

bool reservasEquals(Reservas a, Reservas b)
{
    if (a.idCli != b.idCli)
        return false;
    if (a.idVue != b.idVue)
        return false;
    if (a.cant != b.cant)
        return false;
    return true;
}

string registroClienteToString(RegistroCliente x)
{
    char sep = 1;
    string sIdCliente = to_string(x.idCliente);
    string sMillasAcumuladas = to_string(x.millasAcumuladas);
    return sIdCliente + sep + sMillasAcumuladas;
}

RegistroCliente registroClienteFromString(string s)
{
    char sep = 1;
    RegistroCliente x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCliente = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.millasAcumuladas = stoi(t1);
    return x;
}

string registroClienteToDebug(RegistroCliente x)
{
    stringstream sout;
    sout << "[";
    sout << x.idCliente;
    sout << ",";
    sout << x.millasAcumuladas;
    sout << "]";
    return sout.str();
}

RegistroCliente registroCliente(int idCliente, int millasAcumuladas)
{
    RegistroCliente a;
    a.idCliente = idCliente;
    a.millasAcumuladas = millasAcumuladas;
    return a;
}

bool registroClienteEquals(RegistroCliente a, RegistroCliente b)
{
    if (a.idCliente != b.idCliente)
        return false;
    if (a.millasAcumuladas != b.millasAcumuladas)
        return false;
    return true;
}

string registroCiudadToString(RegistroCiudad x)
{
    char sep = 1;
    string sUnaCiudad = ciudadToString(x.unaCiudad);
    string sContador = to_string(x.contador);
    return sUnaCiudad + sep + sContador;
}

RegistroCiudad registroCiudadFromString(string s)
{
    char sep = 1;
    RegistroCiudad x;
    string t0 = getTokenAt(s, sep, 0);
    x.unaCiudad = ciudadFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.contador = stoi(t1);
    return x;
}

string registroCiudadToDebug(RegistroCiudad x)
{
    stringstream sout;
    sout << "[";
    sout << ciudadToDebug(x.unaCiudad);
    sout << ",";
    sout << x.contador;
    sout << "]";
    return sout.str();
}

RegistroCiudad registroCiudad(Ciudad unaCiudad, int contador)
{
    RegistroCiudad a;
    a.unaCiudad = unaCiudad;
    a.contador = contador;
    return a;
}

bool registroCiudadEquals(RegistroCiudad a, RegistroCiudad b)
{
    if (!ciudadEquals(a.unaCiudad, b.unaCiudad))
        return false;
    if (a.contador != b.contador)
        return false;
    return true;
}

string registroVueloToString(RegistroVuelo x)
{
    char sep = 2;
    string sUnVuelo = vueloToString(x.unVuelo);
    string sAcumulador = to_string(x.acumulador);
    return sUnVuelo + sep + sAcumulador;
}

RegistroVuelo registroVueloFromString(string s)
{
    char sep = 2;
    RegistroVuelo x;
    string t0 = getTokenAt(s, sep, 0);
    x.unVuelo = vueloFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.acumulador = stoi(t1);
    return x;
}

string registroVueloToDebug(RegistroVuelo x)
{
    stringstream sout;
    sout << "[";
    sout << vueloToDebug(x.unVuelo);
    sout << ",";
    sout << x.acumulador;
    sout << "]";
    return sout.str();
}

RegistroVuelo registroVuelo(Vuelo unVuelo, int acumulador)
{
    RegistroVuelo b;
    b.unVuelo = unVuelo;
    b.acumulador = acumulador;
    return b;
}

bool registroVueloEquals(RegistroVuelo a, RegistroVuelo b)
{
    if (!vueloEquals(a.unVuelo, b.unVuelo))
        return false;
    if (a.acumulador != b.acumulador)
        return false;
    return true;
}

#endif