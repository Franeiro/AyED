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

struct Caracteristicas
{
    int idCaract;
    char descr[100];
};

struct Casa
{
    int idCasa;
    char direcc[50];
    int idDueno;
    int caractMask;
    int idUsr;
};

struct Busqueda
{
    int idUsr;
    int caractMask;
    int dias;
    double tolerancia;
};

struct RegistroCasas
{
    Casa casa;
};

struct RegistroCaracteristicas
{
    Caracteristicas caract;
};

struct GuardoYMuestro
{
    int idCasa;
    double concordancia;
};

string
caracteristicasToString(Caracteristicas x)
{
    char sep = 1;
    string sIdCaract = to_string(x.idCaract);
    string sDescr = x.descr;
    return sIdCaract + sep + sDescr;
}

Caracteristicas caracteristicasFromString(string s)
{
    char sep = 1;
    Caracteristicas x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCaract = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.descr, t1.c_str());
    return x;
}

string caracteristicasToDebug(Caracteristicas x)
{
    stringstream sout;
    sout << "[";
    sout << x.idCaract;
    sout << ",";
    sout << x.descr;
    sout << "]";
    return sout.str();
}

Caracteristicas caracteristicas(int idCaract, string descr)
{
    Caracteristicas a;
    a.idCaract = idCaract;
    strcpy(a.descr, descr.c_str());
    return a;
}

bool caracteristicasEquals(Caracteristicas a, Caracteristicas b)
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

string registroCasasToString(RegistroCasas x)
{
    char sep = 4;
    string sCasa = casaToString(x.casa);
    return sCasa;
}

RegistroCasas registroCasasFromString(string s)
{
    char sep = 4;
    RegistroCasas x;
    string t0 = getTokenAt(s, sep, 0);
    x.casa = casaFromString(t0);
    return x;
}

string registroCasasToDebug(RegistroCasas x)
{
    stringstream sout;
    sout << "[";
    sout << casaToDebug(x.casa);
    sout << "]";
    return sout.str();
}

RegistroCasas registroCasas(Casa casa)
{
    RegistroCasas a;
    a.casa = casa;
    return a;
}

bool registroCasasEquals(RegistroCasas a, RegistroCasas b)
{
    if (!casaEquals(a.casa, b.casa))
        return false;
    return true;
}

string registroCaracteristicasToString(RegistroCaracteristicas x)
{
    char sep = 5;
    string sCaract = caracteristicasToString(x.caract);
    return sCaract;
}

RegistroCaracteristicas registroCaracteristicasFromString(string s)
{
    char sep = 5;
    RegistroCaracteristicas x;
    string t0 = getTokenAt(s, sep, 0);
    x.caract = caracteristicasFromString(t0);
    return x;
}

string registroCaracteristicasToDebug(RegistroCaracteristicas x)
{
    stringstream sout;
    sout << "[";
    sout << caracteristicasToDebug(x.caract);
    sout << "]";
    return sout.str();
}

RegistroCaracteristicas registroCaracteristicas(Caracteristicas caract)
{
    RegistroCaracteristicas a;
    a.caract = caract;
    return a;
}

bool registroCaracteristicasEquals(RegistroCaracteristicas a, RegistroCaracteristicas b)
{
    if (!caracteristicasEquals(a.caract, b.caract))
        return false;
    return true;
}

string guardoYMuestroToString(GuardoYMuestro x)
{
    char sep = 1;
    string sIdCasa = to_string(x.idCasa);
    string sConcordancia = to_string(x.concordancia);
    return sIdCasa + sep + sConcordancia;
}

GuardoYMuestro guardoYMuestroFromString(string s)
{
    char sep = 1;
    GuardoYMuestro x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCasa = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.concordancia = stod(t1);
    return x;
}

string guardoYMuestroToDebug(GuardoYMuestro x)
{
    stringstream sout;
    sout << "[";
    sout << x.idCasa;
    sout << ",";
    sout << x.concordancia;
    sout << "]";
    return sout.str();
}

GuardoYMuestro guardoYMuestro(int idCasa, double concordancia)
{
    GuardoYMuestro a;
    a.idCasa = idCasa;
    a.concordancia = concordancia;
    return a;
}

bool guardoYMuestroEquals(GuardoYMuestro a, GuardoYMuestro b)
{
    if (a.idCasa != b.idCasa)
        return false;
    if (a.concordancia != b.concordancia)
        return false;
    return true;
}

#endif