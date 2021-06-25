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
#include "calificaciones.hpp"

using namespace std;

void ingresoCalificacion()
{
    FILE *h = fopen("CALIFIACIONES.dat", "w+b");

    Califiacion a;

    a = califiacion(7, 1, 9);
    fwrite(&a, sizeof(Califiacion), 1, h);
    a = califiacion(7, 2, 7);
    fwrite(&a, sizeof(Califiacion), 1, h);
    a = califiacion(7, 3, 5);
    fwrite(&a, sizeof(Califiacion), 1, h);
    a = califiacion(4, 3, 5);
    fwrite(&a, sizeof(Califiacion), 1, h);
    a = califiacion(4, 1, 9);
    fwrite(&a, sizeof(Califiacion), 1, h);
    a = califiacion(4, 2, 8);
    fwrite(&a, sizeof(Califiacion), 1, h);
    a = califiacion(4, 3, 8);
    fwrite(&a, sizeof(Califiacion), 1, h);
    a = califiacion(1, 3, 5);
    fwrite(&a, sizeof(Califiacion), 1, h);

    fclose(h);
}

// VERSION 1. EL arhivo esta ordenado por asignatura.

int main()
{
    ingresoCalificacion();

    FILE *f = fopen("CALIFIACIONES.dat", "r+b");

    //Lee el primer registro del arhivo
    Califiacion reg = read<Califiacion>(f);

    while (!feof(f))
    {
        int cont = 0;
        int acum = 0;

        //guarda la asignatura anterior
        int idAsigAnt = reg.idAsig;

        //se fija si la asignatura leida es la misma que la anterior
        while (idAsigAnt == reg.idAsig)
        {
            cont++;
            acum += reg.calif;

            reg = read<Califiacion>(f);
        }

        double prom = acum / (double)cont;
        cout << "ID de Asignatura: " << idAsigAnt << " Promedio: " << prom << endl;
    }

    fclose(f);

    return 0;
}

//Version 2. EL archivo no se encuentra ordenado y no se saben cuantas asignaturas hay

Coll<Estad> collEstad = coll<Estad>();
int cmpEstadInt(Estad e, int id)
{
    return e.id - id;
}

int buscarElemento(Coll<Estad> &collEstad, int id)
{
    int pos = collFind<Estad, int>(collEstad, id, cmpEstadInt, estadFromString);

    if (pos < 0)
    {
        Estad x = estad(id, 0, 0);
        pos = collAdd<Estad>(collEstad, x, estadToString);
    }

    return pos;
}

void mostrarResultados(Coll<Estad> c)
{
    collReset<Estad>(c);

    while (collHasNext<Estad>(c))
    {
        Estad e = collNext<Estad>(c, estadFromString);

        double prom = e.acum / (double)e.cont;
        cout << e.id << ":" << prom << endl;
    }
}

int main()
{
    ingresoCalificacion();

    FILE *f = fopen("CALIFIACIONES.dat", "r+b");

    Coll<Estad> collEstad = coll<Estad>();

    Califiacion reg = read<Califiacion>(f);

    while (!feof(f))
    {
        int pos = buscarElemento(collEstad, reg.idAsig);

        Estad elm = collGetAt<Estad>(collEstad, pos, estadFromString);

        elm.cont++;
        elm.acum += reg.calif;
        collSetAt<Estad>(collEstad, elm, pos, estadToString);

        reg = read<Califiacion>(f);
    }

    mostrarResultados(collEstad);

    fclose(f);
    return 0;

    return 0;
}

//Version 3.
//Se agrega ASIGNATURAS.dat, que aporta informacion complementaria a las asignaturas
// Se pide emitir dos listas. Una ordenada alfabeticamente por nomAsig. El segundo, decrecientemente por calif. prom.

Coll<RAsignatura> subirAsignaturas()
{
    Coll<RAsignatura> ret = coll<RAsignatura>();

    FILE *f = fopen("ASIGNATURAS.dat", "r+b");

    Asignatura reg = read<Asignatura>(f);

    while (!feof(f))
    {
        RAsignatura ra = rAsignatura(reg, estad(-1, 0, 0));

        collAdd<RAsignatura>(ret, ra, rAsignaturaToString);

        reg = read<Asignatura>(f);
    }

    fclose(f);

    return ret;
}

void mostrarResultados(Coll<RAsignatura> c, int cmpRAsignatura(RAsignatura, RAsignatura))
{
    collSort<RAsignatura>(c, cmpRAsignatura, rAsignaturaFromString, rAsignaturaToString);

    collReset<RAsignatura>(c);

    while (collHasNext<RAsignatura>(c))
    {
        RAsignatura ra = collNext<RAsignatura>(c, rAsignaturaFromString);

        double prom = ra.estad.acum / (double)ra.estad.cont;

        string sNomAsig = ra.asig.nomAsig;

        cout << sNomAsig << ":" << prom << endl;
    }
}

int cmpRAsignaturaAlfabetico(RAsignatura a, RAsignatura b)
{
    string sA = a.asig.nomAsig;
    string sB = b.asig.nomAsig;

    return sA < sB ? -1 : sA > sB ? 1
                                  : 0;
}

int cmpRAsignaturaPromedio(RAsignatura a, RAsignatura b)
{
    double pA = a.estad.acum / (double)a.estad.cont;
    double pB = b.estad.acum / (double)b.estad.cont;

    return pA > pB ? -1 : pA < pB ? 1
                                  : 0;
}

int cmpRAsigId(RAsignatura ra, int id)
{
    return ra.asig.idAsign - id;
}

int main()
{
    ingresoCalificacion();

    Coll<RAsignatura> collAsig = subirAsignaturas();

    FILE *f = fopen("CALIFICACIONES.dat", "r+b");

    Califiacion reg = read<Califiacion>(f);

    while (!feof(f))
    {
        int pos = collFind<RAsignatura, int>(collAsig, reg.idAsig, cmpRAsigId, rAsignaturaFromString);

        RAsignatura elm = collGetAt<RAsignatura>(collAsig, pos, rAsignaturaFromString);

        elm.estad.cont++;
        elm.estad.acum += reg.calif;

        collSetAt<RAsignatura>(collAsig, elm, pos, rAsignaturaToString);

        reg = read<Califiacion>(f);
    }

    mostrarResultados(collAsig, cmpRAsignaturaAlfabetico);

    mostrarResultados(collAsig, cmpRAsignaturaPromedio);

    fclose(f);
    return 0;
}

#endif