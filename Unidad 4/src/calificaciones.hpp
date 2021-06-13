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

//V1

struct Califiacion
{
    int idAsig;
    int idESt;
    int calif;
};

string califiacionToString(Califiacion x)
{
    char sep = 1;
    string sIdAsig = to_string(x.idAsig);
    string sIdESt = to_string(x.idESt);
    string sCalif = to_string(x.calif);
    return sIdAsig + sep + sIdESt + sep + sCalif;
}

Califiacion califiacionFromString(string s)
{
    char sep = 1;
    Califiacion x;
    string t0 = getTokenAt(s, sep, 0);
    x.idAsig = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.idESt = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.calif = stoi(t2);
    return x;
}

string califiacionToDebug(Califiacion x)
{
    stringstream sout;
    sout << "[";
    sout << x.idAsig;
    sout << ",";
    sout << x.idESt;
    sout << ",";
    sout << x.calif;
    sout << "]";
    return sout.str();
}

Califiacion califiacion(int idAsig, int idESt, int calif)
{
    Califiacion a;
    a.idAsig = idAsig;
    a.idESt = idESt;
    a.calif = calif;
    return a;
}

bool califiacionEquals(Califiacion a, Califiacion b)
{
    if (a.idAsig != b.idAsig)
        return false;
    if (a.idESt != b.idESt)
        return false;
    if (a.calif != b.calif)
        return false;
    return true;
}

//V2
;

struct Estad // por cada asignatura, crea un Estad.
             // si el id ya existe, le suma la nota. Sino, crea la asignatura.
{
    int id;
    int cont;
    int acum;
};

string estadToString(Estad x)
{
    char sep = 1;
    string sId = to_string(x.id);
    string sCont = to_string(x.cont);
    string sAcum = to_string(x.acum);
    return sId + sep + sCont + sep + sAcum;
}

Estad estadFromString(string s)
{
    char sep = 1;
    Estad x;
    string t0 = getTokenAt(s, sep, 0);
    x.id = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.cont = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.acum = stoi(t2);
    return x;
}

string estadToDebug(Estad x)
{
    stringstream sout;
    sout << "[";
    sout << x.id;
    sout << ",";
    sout << x.cont;
    sout << ",";
    sout << x.acum;
    sout << "]";
    return sout.str();
}

Estad estad(int id, int cont, int acum)
{
    Estad b;
    b.id = id;
    b.cont = cont;
    b.acum = acum;
    return b;
}

bool estadEquals(Estad a, Estad b)
{
    if (a.id != b.id)
        return false;
    if (a.cont != b.cont)
        return false;
    if (a.acum != b.acum)
        return false;
    return true;
}

//V3

struct Asignatura
{
    int idAsign;
    char nomAsig[30];
    char maestroACargo[50];
};

string asignaturaToString(Asignatura x)
{
    char sep = 1;
    string sIdAsign = to_string(x.idAsign);
    string sNomAsig = x.nomAsig;
    string sMaestroACargo = x.maestroACargo;
    return sIdAsign + sep + sNomAsig + sep + sMaestroACargo;
}

Asignatura asignaturaFromString(string s)
{
    char sep = 1;
    Asignatura x;
    string t0 = getTokenAt(s, sep, 0);
    x.idAsign = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.nomAsig, t1.c_str());
    string t2 = getTokenAt(s, sep, 2);
    strcpy(x.maestroACargo, t2.c_str());
    return x;
}

string asignaturaToDebug(Asignatura x)
{
    stringstream sout;
    sout << "[";
    sout << x.idAsign;
    sout << ",";
    sout << x.nomAsig;
    sout << ",";
    sout << x.maestroACargo;
    sout << "]";
    return sout.str();
}

Asignatura asignatura(int idAsign, string nomAsig, string maestroACargo)
{
    Asignatura a;
    a.idAsign = idAsign;
    strcpy(a.nomAsig, nomAsig.c_str());
    strcpy(a.maestroACargo, maestroACargo.c_str());
    return a;
}

bool asignaturaEquals(Asignatura a, Asignatura b)
{
    if (a.idAsign != b.idAsign)
        return false;
    return true;
}

struct RAsignatura
{
    Asignatura asig;
    Estad estad;
};

string rAsignaturaToString(RAsignatura x)
{
    char sep = 1;
    string sAsig = asignaturaToString(x.asig);
    string sEstad = estadToString(x.estad);
    return sAsig + sep + sEstad;
}

RAsignatura rAsignaturaFromString(string s)
{
    char sep = 1;
    RAsignatura x;
    string t0 = getTokenAt(s, sep, 0);
    x.asig = asignaturaFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.estad = estadFromString(t1);
    return x;
}

string rAsignaturaToDebug(RAsignatura x)
{
    stringstream sout;
    sout << "[";
    sout << asignaturaToDebug(x.asig);
    sout << ",";
    sout << estadToDebug(x.estad);
    sout << "]";
    return sout.str();
}

RAsignatura rAsignatura(Asignatura asig, Estad estad)
{
    RAsignatura b;
    b.asig = asig;
    b.estad = estad;
    return b;
}

bool rAsignaturaEquals(RAsignatura a, RAsignatura b)
{
    if (!asignaturaEquals(a.asig, b.asig))
        return false;
    if (!estadEquals(a.estad, b.estad))
        return false;
    return true;
}

#endif