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

struct Caract
{
    int idCaract; // 1,2,4,8,16,32
    char descr[100];
};

struct Casa
{
    int idCasa;
    char direcc[50];
    int idDueno;
    int caractMask; // poner en binario. X ej 100101 --> 1,4,32.   0100010011= 1,2,16, 256
    int idUsr;
};

struct Busqueda
{
    int idUsr;
    int caractMask; // poner en binario. X ej 100101 --> 1,4,32.   0100010011= 1,2,16, 256
    int dias;
    double tolerancia;

    //un usuario pasa: (1122, 1011, 15, 0.7)---> El ususario 1122 busca una casa con 1,2,8 por 15 dias y con una tolerancia del 0.7
};

struct RegistroCaracteristicas
{
    Caract caracteristicas;
};

struct RegistroCasas
{
    Casa casa;
    int coinicidencias;
};

struct RegistroBusqueda
{
    Busqueda busqueda;
    int peticiones;
};

string caractToString(Caract x)
{
    char sep = 1;
    string sIdCaract = to_string(x.idCaract);
    string sDescr = x.descr;
    return sIdCaract + sep + sDescr;
}

Caract caractFromString(string s)
{
    char sep = 1;
    Caract x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCaract = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.descr, t1.c_str());
    return x;
}

string caractToDebug(Caract x)
{
    stringstream sout;
    sout << "[";
    sout << x.idCaract;
    sout << ",";
    sout << x.descr;
    sout << "]";
    return sout.str();
}

Caract caract(int idCaract, string descr)
{
    Caract a;
    a.idCaract = idCaract;
    strcpy(a.descr, descr.c_str());
    return a;
}

bool caractEquals(Caract a, Caract b)
{
    if (a.idCaract != b.idCaract)
        return false;
    return true;
}

string casaToString(Casa x)
{
    char sep = 2;
    string sIdCasa = to_string(x.idCasa);
    string sDirecc = x.direcc;
    string sIdDueno = to_string(x.idDueno);
    string sCaractMask = to_string(x.caractMask);
    string sIdUsr = to_string(x.idUsr);
    return sIdCasa + sep + sDirecc + sep + sIdDueno + sep + sCaractMask + sep + sIdUsr;
}

Casa casaFromString(string s)
{
    char sep = 2;
    Casa x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCasa = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.direcc, t1.c_str());
    string t2 = getTokenAt(s, sep, 2);
    x.idDueno = stoi(t2);
    string t3 = getTokenAt(s, sep, 3);
    x.caractMask = stoi(t3);
    string t4 = getTokenAt(s, sep, 4);
    x.idUsr = stoi(t4);
    return x;
}

string casaToDebug(Casa x)
{
    stringstream sout;
    sout << "[";
    sout << x.idCasa;
    sout << ",";
    sout << x.direcc;
    sout << ",";
    sout << x.idDueno;
    sout << ",";
    sout << x.caractMask;
    sout << ",";
    sout << x.idUsr;
    sout << "]";
    return sout.str();
}

Casa casa(int idCasa, string direcc, int idDueno, int caractMask, int idUsr)
{
    Casa a;
    a.idCasa = idCasa;
    strcpy(a.direcc, direcc.c_str());
    a.idDueno = idDueno;
    a.caractMask = caractMask;
    a.idUsr = idUsr;
    return a;
}

bool casaEquals(Casa a, Casa b)
{
    if (a.idCasa != b.idCasa)
        return false;
    if (a.idDueno != b.idDueno)
        return false;
    if (a.caractMask != b.caractMask)
        return false;
    if (a.idUsr != b.idUsr)
        return false;
    return true;
}

string busquedaToString(Busqueda x)
{
    char sep = 3;
    string sIdUsr = to_string(x.idUsr);
    string sCaractMask = to_string(x.caractMask);
    string sDias = to_string(x.dias);
    string sTolerancia = to_string(x.tolerancia);
    return sIdUsr + sep + sCaractMask + sep + sDias + sep + sTolerancia;
}

Busqueda busquedaFromString(string s)
{
    char sep = 3;
    Busqueda x;
    string t0 = getTokenAt(s, sep, 0);
    x.idUsr = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.caractMask = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.dias = stoi(t2);
    string t3 = getTokenAt(s, sep, 3);
    x.tolerancia = stod(t3);
    return x;
}

string busquedaToDebug(Busqueda x)
{
    stringstream sout;
    sout << "[";
    sout << x.idUsr;
    sout << ",";
    sout << x.caractMask;
    sout << ",";
    sout << x.dias;
    sout << ",";
    sout << x.tolerancia;
    sout << "]";
    return sout.str();
}

Busqueda busqueda(int idUsr, int caractMask, int dias, double tolerancia)
{
    Busqueda a;
    a.idUsr = idUsr;
    a.caractMask = caractMask;
    a.dias = dias;
    a.tolerancia = tolerancia;
    return a;
}

bool busquedaEquals(Busqueda a, Busqueda b)
{
    if (a.idUsr != b.idUsr)
        return false;
    if (a.caractMask != b.caractMask)
        return false;
    if (a.dias != b.dias)
        return false;
    if (a.tolerancia != b.tolerancia)
        return false;
    return true;
}

string registroCaracteristicasToString(RegistroCaracteristicas x)
{
    char sep = 4;
    string sCaracteristicas = caractToString(x.caracteristicas);
    return sCaracteristicas;
}

RegistroCaracteristicas registroCaracteristicasFromString(string s)
{
    char sep = 4;
    RegistroCaracteristicas x;
    string t0 = getTokenAt(s, sep, 0);
    x.caracteristicas = caractFromString(t0);
    return x;
}

string registroCaracteristicasToDebug(RegistroCaracteristicas x)
{
    stringstream sout;
    sout << "[";
    sout << caractToDebug(x.caracteristicas);
    sout << "]";
    return sout.str();
}

RegistroCaracteristicas registroCaracteristicas(Caract caracteristicas)
{
    RegistroCaracteristicas a;
    a.caracteristicas = caracteristicas;
    return a;
}

bool registroCaracteristicasEquals(RegistroCaracteristicas a, RegistroCaracteristicas b)
{
    if (!caractEquals(a.caracteristicas, b.caracteristicas))
        return false;
    return true;
}

string registroCasasToString(RegistroCasas x)
{
    char sep = 5;
    string sCasa = casaToString(x.casa);
    string sCoinicidencias = to_string(x.coinicidencias);
    return sCasa + sep + sCoinicidencias;
}

RegistroCasas registroCasasFromString(string s)
{
    char sep = 5;
    RegistroCasas x;
    string t0 = getTokenAt(s, sep, 0);
    x.casa = casaFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.coinicidencias = stoi(t1);
    return x;
}

string registroCasasToDebug(RegistroCasas x)
{
    stringstream sout;
    sout << "[";
    sout << casaToDebug(x.casa);
    sout << ",";
    sout << x.coinicidencias;
    sout << "]";
    return sout.str();
}

RegistroCasas registroCasas(Casa casa, int coinicidencias)
{
    RegistroCasas a;
    a.casa = casa;
    a.coinicidencias = coinicidencias;
    return a;
}

bool registroCasasEquals(RegistroCasas a, RegistroCasas b)
{
    if (!casaEquals(a.casa, b.casa))
        return false;
    if (a.coinicidencias != b.coinicidencias)
        return false;
    return true;
}

string registroBusquedaToString(RegistroBusqueda x)
{
    char sep = 6;
    string sBusqueda = busquedaToString(x.busqueda);
    string sPeticiones = to_string(x.peticiones);
    return sBusqueda + sep + sPeticiones;
}

RegistroBusqueda registroBusquedaFromString(string s)
{
    char sep = 6;
    RegistroBusqueda x;
    string t0 = getTokenAt(s, sep, 0);
    x.busqueda = busquedaFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.peticiones = stoi(t1);
    return x;
}

string registroBusquedaToDebug(RegistroBusqueda x)
{
    stringstream sout;
    sout << "[";
    sout << busquedaToDebug(x.busqueda);
    sout << ",";
    sout << x.peticiones;
    sout << "]";
    return sout.str();
}

RegistroBusqueda registroBusqueda(Busqueda busqueda, int peticiones)
{
    RegistroBusqueda a;
    a.busqueda = busqueda;
    a.peticiones = peticiones;
    return a;
}

bool registroBusquedaEquals(RegistroBusqueda a, RegistroBusqueda b)
{
    if (!busquedaEquals(a.busqueda, b.busqueda))
        return false;
    if (a.peticiones != b.peticiones)
        return false;
    return true;
}

#endif