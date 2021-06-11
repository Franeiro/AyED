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
#include "torneoDeFutbol.hpp"
using namespace std;

Coll<REquipo> subirEquipos()
{
    Coll<REquipo> ret = coll<REquipo>();

    FILE *f = fopen("EQUIPOS.dat", "r+b");

    Equipo eq = read<Equipo>(f);
    while (!feof(f))
    {
        REquipo re = rEquipo(eq, 0);
        collAdd<REquipo>(ret, re, rEquipoToString);
        eq = read<Equipo>(f);
    }

    fclose(f);
    return ret;
}

int cmpREquipoId(REquipo e, int id)
{
    return e.e.idEq - id;
}

void sumarPuntosEquipo(int idEq, int ptos, Coll<REquipo> &c)
{
    int pos = collFind<REquipo, int>(c, idEq, cmpREquipoId, rEquipoFromString);
    REquipo re = collGetAt<REquipo>(c, pos, rEquipoFromString);
    re.cont += ptos;
    collSetAt<REquipo>(c, re, pos, rEquipoToString);
}

int cmpREstadioEst(REstadio r, string e)
{
    return r.estadio < e ? -1 : r.estadio > e ? 1
                                              : 0;
}

void procesarEstadio(string estadio, int empate, Coll<REstadio> &c)
{
    int pos = collFind<REstadio, string>(c, estadio, cmpREstadioEst, rEstadioFromString);

    if (pos < 0)
    {
        REstadio re = rEstadio(estadio, 0, 0);
        pos = collAdd<REstadio>(c, re, rEstadioToString);
    }

    REstadio re = collGetAt<REstadio>(c, pos, rEstadioFromString);
    re.contPartJug++;
    re.contPartEmp += empate;
    collSetAt<REstadio>(c, re, pos, rEstadioToString);
}

int cmpRLocLoc(RLoc rl, string loc)
{
    return rl.loc < loc ? -1 : rl.loc > loc ? -1
                                            : 0;
}

void procesarLocalidad(Resultado res, Coll<RLoc> &cl, Coll<REquipo> ce)
{
    bool hayGanador = res.codRes != 0;
    if (hayGanador)
    {
        int idEqGan = res.codRes < 0 ? res.idEq1 : res.idEq2;

        // busco en equipos para obtener localidad
        int pos = collFind<REquipo, int>(ce, idEqGan, cmpREquipoId, rEquipoFromString);
        REquipo re = collGetAt<REquipo>(ce, pos, rEquipoFromString);

        // busco en localidades (si existe)
        string loc = re.e.loc;
        pos = collFind<RLoc, string>(cl, loc, cmpRLocLoc, rLocFromString);

        if (pos < 0)
        {
            RLoc x = rLoc(loc, 0);
            pos = collAdd<RLoc>(cl, x, rLocToString);
        }

        RLoc rl = collGetAt<RLoc>(cl, pos, rLocFromString);
        rl.cont++;
        collSetAt<RLoc>(cl, rl, pos, rLocToString);
    }
}

int cmpPtos(REquipo a, REquipo b)
{
    int pa = a.e.puntos + a.cont;
    int pb = b.e.puntos + b.cont;
    return pb - pa;
}

void mostrarTablaPosiciones(Coll<REquipo> c)
{
    collSort<REquipo>(c, cmpPtos, rEquipoFromString, rEquipoToString);
    collReset<REquipo>(c);
    while (collHasNext<REquipo>(c))
    {
        REquipo e = collNext<REquipo>(c, rEquipoFromString);

        string nom = e.e.nombre;
        int p = e.e.puntos + e.cont;
        cout << nom << p << endl;
    }
}

void mostrarEstadios(Coll<REstadio> c)
{
    collReset<REstadio>(c);
    while (collHasNext<REstadio>(c))
    {
        REstadio e = collNext<REstadio>(c, rEstadioFromString);
        cout << e.estadio << ", " << e.contPartJug << ", " << e.contPartEmp << endl;
    }
}

void actualizarEquipos(Coll<REquipo> c)
{
    FILE *f = fopen("EQUIPOS.dat", "r+b");

    int i = 0;
    Equipo e = read<Equipo>(f);
    while (!feof(f))
    {
        REquipo x = collGetAt<REquipo>(c, i, rEquipoFromString);
        e.puntos = x.e.puntos + x.cont;

        seek<Equipo>(f, filePos<Equipo>(f) - 1);
        write<Equipo>(f, e);

        e = read<Equipo>(f);
    }
}

void mostrarRankingLocalidades(Coll<RLoc> c)
{
}

int main()
{
    // subo los equipos
    Coll<REquipo> collEq = subirEquipos();

    // coleccion de estadios
    Coll<REstadio> collEst = coll<REstadio>();

    // localidades
    Coll<RLoc> collLoc = coll<RLoc>();

    FILE *f = fopen("RESULTADOS.dat", "r+b");

    // barro el archivo de novedades
    Resultado res = read<Resultado>(f);
    while (!feof(f))
    {
        // proceso punto 1
        int pEq1 = res.codRes < 0 ? 3 : res.codRes == 0 ? 1
                                                        : 0;
        int pEq2 = res.codRes > 0 ? 3 : res.codRes == 0 ? 1
                                                        : 0;
        sumarPuntosEquipo(res.idEq1, pEq1, collEq);
        sumarPuntosEquipo(res.idEq2, pEq2, collEq);

        // proceso punto 2
        string est = res.estadio;
        int empate = res.codRes == 0 ? 1 : 0;
        procesarEstadio(est, empate, collEst);

        // procesar
        procesarLocalidad(res, collLoc, collEq);

        res = read<Resultado>(f);
    }

    // muestro resultados 1
    mostrarTablaPosiciones(collEq);

    // muestro resultados 2
    mostrarEstadios(collEst);

    // actualizo archivo pto 3
    actualizarEquipos(collEq);

    // actualizo archivo pto 3
    mostrarRankingLocalidades(collLoc);

    fclose(f);
    return 0;
}

#endif