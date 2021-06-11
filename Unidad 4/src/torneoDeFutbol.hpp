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

struct Resultado
{
    int idEq1;
    int idEq2;
    int codRes;
    char estadio[20];
};

struct Equipo
{
    int idEq;
    char nombre[20];
    int puntos;
    char loc[20];
};

struct REstadio
{
    string estadio;
    int contPartJug;
    int contPartEmp;
};

struct REquipo
{
    Equipo e;
    int cont;
};

struct RLoc
{
    string loc;
    int cont;
};

string rLocToString(RLoc x)
{
    char sep = 1;
    string sLoc = x.loc;
    string sCont = to_string(x.cont);
    return sLoc + sep + sCont;
}

RLoc rLocFromString(string s)
{
    char sep = 1;
    RLoc x;
    string t0 = getTokenAt(s, sep, 0);
    x.loc = t0;
    string t1 = getTokenAt(s, sep, 1);
    x.cont = stoi(t1);
    return x;
}

string rLocToDebug(RLoc x)
{
    stringstream sout;
    sout << "[";
    sout << x.loc;
    sout << ",";
    sout << x.cont;
    sout << "]";
    return sout.str();
}

RLoc rLoc(string loc, int cont)
{
    RLoc a;
    a.loc = loc;
    a.cont = cont;
    return a;
}

bool rLocEquals(RLoc a, RLoc b)
{
    if (a.loc != b.loc)
        return false;
    if (a.cont != b.cont)
        return false;
    return true;
}

string rEquipoToString(REquipo x)
{
    char sep = 1;
    string sE = equipoToString(x.e);
    string sCont = to_string(x.cont);
    return sE + sep + sCont;
}

REquipo rEquipoFromString(string s)
{
    char sep = 1;
    REquipo x;
    string t0 = getTokenAt(s, sep, 0);
    x.e = equipoFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.cont = stoi(t1);
    return x;
}

string rEquipoToDebug(REquipo x)
{
    stringstream sout;
    sout << "[";
    sout << equipoToDebug(x.e);
    sout << ",";
    sout << x.cont;
    sout << "]";
    return sout.str();
}

REquipo rEquipo(Equipo e, int cont)
{
    REquipo a;
    a.e = e;
    a.cont = cont;
    return a;
}

bool rEquipoEquals(REquipo a, REquipo b)
{
    if (!equipoEquals(a.e, b.e))
        return false;
    if (a.cont != b.cont)
        return false;
    return true;
}

string resultadoToString(Resultado x)
{
    char sep = 1;
    string sIdEq1 = to_string(x.idEq1);
    string sIdEq2 = to_string(x.idEq2);
    string sCodRes = to_string(x.codRes);
    string sEstadio = x.estadio;
    return sIdEq1 + sep + sIdEq2 + sep + sCodRes + sep + sEstadio;
}

Resultado resultadoFromString(string s)
{
    char sep = 1;
    Resultado x;
    string t0 = getTokenAt(s, sep, 0);
    x.idEq1 = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.idEq2 = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.codRes = stoi(t2);
    string t3 = getTokenAt(s, sep, 3);
    strcpy(x.estadio, t3.c_str());
    return x;
}

string resultadoToDebug(Resultado x)
{
    stringstream sout;
    sout << "[";
    sout << x.idEq1;
    sout << ",";
    sout << x.idEq2;
    sout << ",";
    sout << x.codRes;
    sout << ",";
    sout << x.estadio;
    sout << "]";
    return sout.str();
}

Resultado resultado(int idEq1, int idEq2, int codRes, string estadio)
{
    Resultado a;
    a.idEq1 = idEq1;
    a.idEq2 = idEq2;
    a.codRes = codRes;
    strcpy(a.estadio, estadio.c_str());
    return a;
}

bool resultadoEquals(Resultado a, Resultado b)
{
    if (a.idEq1 != b.idEq1)
        return false;
    if (a.idEq2 != b.idEq2)
        return false;
    if (a.codRes != b.codRes)
        return false;
    return true;
}

string equipoToString(Equipo x)
{
    char sep = 2;
    string sIdEq = to_string(x.idEq);
    string sNombre = x.nombre;
    string sPuntos = to_string(x.puntos);
    return sIdEq + sep + sNombre + sep + sPuntos;
}

Equipo equipoFromString(string s)
{
    char sep = 2;
    Equipo x;
    string t0 = getTokenAt(s, sep, 0);
    x.idEq = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.nombre, t1.c_str());
    string t2 = getTokenAt(s, sep, 2);
    x.puntos = stoi(t2);
    return x;
}

string equipoToDebug(Equipo x)
{
    stringstream sout;
    sout << "[";
    sout << x.idEq;
    sout << ",";
    sout << x.nombre;
    sout << ",";
    sout << x.puntos;
    sout << "]";
    return sout.str();
}

Equipo equipo(int idEq, string nombre, int puntos)
{
    Equipo a;
    a.idEq = idEq;
    strcpy(a.nombre, nombre.c_str());
    a.puntos = puntos;
    return a;
}

bool equipoEquals(Equipo a, Equipo b)
{
    if (a.idEq != b.idEq)
        return false;
    if (a.puntos != b.puntos)
        return false;
    return true;
}

string rEstadioToString(REstadio x)
{
    char sep = 3;
    string sEstadio = x.estadio;
    string sContPartJug = to_string(x.contPartJug);
    string sContPartEmp = to_string(x.contPartEmp);
    return sEstadio + sep + sContPartJug + sep + sContPartEmp;
}

REstadio rEstadioFromString(string s)
{
    char sep = 3;
    REstadio x;
    string t0 = getTokenAt(s, sep, 0);
    x.estadio = t0;
    string t1 = getTokenAt(s, sep, 1);
    x.contPartJug = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.contPartEmp = stoi(t2);
    return x;
}

string rEstadioToDebug(REstadio x)
{
    stringstream sout;
    sout << "[";
    sout << x.estadio;
    sout << ",";
    sout << x.contPartJug;
    sout << ",";
    sout << x.contPartEmp;
    sout << "]";
    return sout.str();
}

REstadio rEstadio(string estadio, int contPartJug, int contPartEmp)
{
    REstadio a;
    a.estadio = estadio;
    a.contPartJug = contPartJug;
    a.contPartEmp = contPartEmp;
    return a;
}

bool rEstadioEquals(REstadio a, REstadio b)
{
    if (a.estadio != b.estadio)
        return false;
    if (a.contPartJug != b.contPartJug)
        return false;
    if (a.contPartEmp != b.contPartEmp)
        return false;
    return true;
}

#endif