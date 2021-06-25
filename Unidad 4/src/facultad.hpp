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

struct Fecha
{
    int dia;
    int mes;
    int anio;
};

struct Inscripcion
{
    int idAlu;
    int idCur;
    Fecha fecha;
};

struct Curso
{
    int idCur;
    char turno;
    int cap;
    char materia[20];
};

struct Reasignacion
{
    int idAlu;
    int idCurReasig;
};

struct Revision
{
    int idAlu;
    char materia[20];
};

struct RegistroCurso
{
    Curso curso;
};

string inscripcionToString(Inscripcion x)
{
    char sep = 1;
    string sIdAlu = to_string(x.idAlu);
    string sIdCur = to_string(x.idCur);

    return sIdAlu + sep + sIdCur + sep;
}

Inscripcion inscripcionFromString(string s)
{
    char sep = 1;
    Inscripcion x;
    string t0 = getTokenAt(s, sep, 0);
    x.idAlu = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.idCur = stoi(t1);
    string t2 = getTokenAt(s, sep, 2);

    return x;
}

string inscripcionToDebug(Inscripcion x)
{
    stringstream sout;
    sout << "[";
    sout << x.idAlu;
    sout << ",";
    sout << x.idCur;

    sout << "]";
    return sout.str();
}

Inscripcion inscripcion(int idAlu, int idCur, Fecha fecha)
{
    Inscripcion a;
    a.idAlu = idAlu;
    a.idCur = idCur;
    a.fecha = fecha;
    return a;
}

bool inscripcionEquals(Inscripcion a, Inscripcion b)
{
    if (a.idAlu != b.idAlu)
        return false;
    if (a.idCur != b.idCur)
        return false;

    return true;
}

string cursoToString(Curso x)
{
    char sep = 3;
    string sIdCur = to_string(x.idCur);
    string sTurno = string(1, x.turno);
    string sCap = to_string(x.cap);
    string sMateria = x.materia;
    return sIdCur + sep + sTurno + sep + sCap + sep + sMateria;
}

Curso cursoFromString(string s)
{
    char sep = 3;
    Curso x;
    string t0 = getTokenAt(s, sep, 0);
    x.idCur = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.turno = (char)t1[0];
    string t2 = getTokenAt(s, sep, 2);
    x.cap = stoi(t2);
    string t3 = getTokenAt(s, sep, 3);
    strcpy(x.materia, t3.c_str());
    return x;
}

string cursoToDebug(Curso x)
{
    stringstream sout;
    sout << "[";
    sout << x.idCur;
    sout << ",";
    sout << x.turno;
    sout << ",";
    sout << x.cap;
    sout << ",";
    sout << x.materia;
    sout << "]";
    return sout.str();
}

Curso curso(int idCur, char turno, int cap, string materia)
{
    Curso a;
    a.idCur = idCur;
    a.turno = turno;
    a.cap = cap;
    strcpy(a.materia, materia.c_str());
    return a;
}

bool cursoEquals(Curso a, Curso b)
{
    if (a.idCur != b.idCur)
        return false;
    if (a.turno != b.turno)
        return false;
    if (a.cap != b.cap)
        return false;
    return true;
}

string reasignacionToString(Reasignacion x)
{
    char sep = 4;
    string sIdAlu = to_string(x.idAlu);
    string sIdCurReasig = to_string(x.idCurReasig);
    return sIdAlu + sep + sIdCurReasig;
}

Reasignacion reasignacionFromString(string s)
{
    char sep = 4;
    Reasignacion x;
    string t0 = getTokenAt(s, sep, 0);
    x.idAlu = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.idCurReasig = stoi(t1);
    return x;
}

string reasignacionToDebug(Reasignacion x)
{
    stringstream sout;
    sout << "[";
    sout << x.idAlu;
    sout << ",";
    sout << x.idCurReasig;
    sout << "]";
    return sout.str();
}

Reasignacion reasignacion(int idAlu, int idCurReasig)
{
    Reasignacion a;
    a.idAlu = idAlu;
    a.idCurReasig = idCurReasig;
    return a;
}

bool reasignacionEquals(Reasignacion a, Reasignacion b)
{
    if (a.idAlu != b.idAlu)
        return false;
    if (a.idCurReasig != b.idCurReasig)
        return false;
    return true;
}

string revisionToString(Revision x)
{
    char sep = 5;
    string sIdAlu = to_string(x.idAlu);
    string sMateria = x.materia;
    return sIdAlu + sep + sMateria;
}

Revision revisionFromString(string s)
{
    char sep = 5;
    Revision x;
    string t0 = getTokenAt(s, sep, 0);
    x.idAlu = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.materia, t1.c_str());
    return x;
}

string revisionToDebug(Revision x)
{
    stringstream sout;
    sout << "[";
    sout << x.idAlu;
    sout << ",";
    sout << x.materia;
    sout << "]";
    return sout.str();
}

Revision revision(int idAlu, string materia)
{
    Revision a;
    a.idAlu = idAlu;
    strcpy(a.materia, materia.c_str());
    return a;
}

bool revisionEquals(Revision a, Revision b)
{
    if (a.idAlu != b.idAlu)
        return false;
    return true;
}

string registroCursoToString(RegistroCurso x)
{
    char sep = 6;
    string sElCurso = cursoToString(x.curso);
    return sElCurso;
}

RegistroCurso registroCursoFromString(string s)
{
    char sep = 6;
    RegistroCurso x;
    string t0 = getTokenAt(s, sep, 0);
    x.curso = cursoFromString(t0);
    return x;
}

string registroCursoToDebug(RegistroCurso x)
{
    stringstream sout;
    sout << "[";
    sout << cursoToDebug(x.curso);
    sout << "]";
    return sout.str();
}

RegistroCurso registroCurso(Curso curso)
{
    RegistroCurso a;
    a.curso = curso;
    return a;
}

bool registroCursoEquals(RegistroCurso a, RegistroCurso b)
{
    if (!cursoEquals(a.curso, b.curso))
        return false;
    return true;
}

#endif
