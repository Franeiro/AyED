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
#include "compañiaDeAviacionClase.hpp"
using namespace std;

Coll<RVuelo> subirVuelos()
{
    Coll<RVuelo> collVuelo = coll<RVuelo>();

    FILE *vuelos = fopen("VUELOS.dat", "rb");

    Vuelo unVuelo = read<Vuelo>(vuelos);

    while (!feof(vuelos))
    {
        RVuelo rv = rVuelo(unVuelo, 0, 0);
        collAdd<RVuelo>(collVuelo, rv, rVueloToString);
        unVuelo = read<Vuelo>(vuelos);
    }

    fclose(vuelos);
    return collVuelo;
}

Coll<RCiudad> subirCiudades()
{
    Coll<RCiudad> collCiudad = coll<RCiudad>();

    FILE *ciudades = fopen("CIUDADES.dat", "rb");

    Ciudad unaCiudad = read<Ciudad>(ciudades);

    while (!feof(ciudades))
    {
        RCiudad rc = rCiudad(unaCiudad, 0);
        collAdd<RCiudad>(collCiudad, rc, rCiudadToString);
        unaCiudad = read<Ciudad>(ciudades);
    }

    fclose(ciudades);
    return collCiudad;
}

Coll<RCliente> collCliente = coll<RCliente>();

/*
    int cmpRVueId(RVuelo r, int i)
    {
        return r.vue.idVue - i;
    }
*/
/*
    Procesar punto 1 profe

    int pos = collFind<RVuelo,int>(cvue, r.idVue,cmpRVueId, rVueloFromString);

    RVuelo rvue = collGetAt<RVuelo>(cvue,pos,rVueloFromString);

    int idCiudadDestino = rVue.vue.idDes;

    pos = collFind<RCiudad, int>(cciu,idCiudadDestino, rCiduadFromString);

    RCiudad rCiuDes = collGetAt<RCiudad>(cciu,pos,rCiudadFromString);

    rCiuDes.cont++;

    collSetAt<RCiudad>(cciu,rCiuDes, pos, rCiudadToString);






*/

int cmpRVueloIdVuelo(RVuelo regVue, int idVuelo)
{
    return regVue.vue.idVue - idVuelo;
}

int cmpRClienteId(RCliente rCli, int idCli)
{
    return rCli.idCli - idCli;
}

int cmpRCiudadIdCiudad(RCiudad regCiu, int idCiu)
{
    return regCiu.ciu.idCiu - idCiu;
}

void creoCliente(Coll<RCliente> &collCliente, int idCliente, int millas, int cantidad)
{
    RCliente unCliente{idCliente, millas};

    int posicionCliente = collFind<RCliente, int>(collCliente, idCliente, cmpRClienteId, rClienteFromString);

    if (posicionCliente < 0)
    {
        posicionCliente = collAdd<RCliente>(collCliente, unCliente, rClienteToString);
    }

    RCliente agregoCliente = collGetAt<RCliente>(collCliente, posicionCliente, rClienteFromString);

    agregoCliente.acum += (millas * cantidad);

    collSetAt<RCliente>(collCliente, agregoCliente, posicionCliente, rClienteToString);
}

void procesarPunto1(Reserva r, Coll<RVuelo> cvue, Coll<RCiudad> &cciu)
{ /*
    int posicionVuelo = collFind<RVuelo, int>(cvue, r.idVue, cmpRVueloIdVuelo, rVueloFromString);

    RVuelo elVuelo = collGetAt<RVuelo>(cvue, posicionVuelo, rVueloFromString);

    int posicionOrigen = collFind<RCiudad, int>(cciu, elVuelo.vue.idOri, cmpRCiudadIdCiudad, rCiudadFromString);

    RCiudad ciudadDeOrigen = collGetAt<RCiudad>(cciu, posicionOrigen, rCiudadFromString);

    int posicionDestino = collFind<RCiudad, int>(cciu, elVuelo.vue.idDes, cmpRCiudadIdCiudad, rCiudadFromString);

    RCiudad ciudadDeDestino = collGetAt<RCiudad>(cciu, posicionDestino, rCiudadFromString);

    int diferenciaDeMillas = (abs(ciudadDeDestino.ciu.millas - ciudadDeOrigen.ciu.millas));

    if (r.cant <= elVuelo.vue.cap)
    {
        elVuelo.vue.cap -= r.cant;

        creoCliente(collCliente, r.idCli, diferenciaDeMillas);

        collSetAt<RVuelo>(cvue, elVuelo, posicionVuelo, rVueloToString);
        
    }*/

    int pos = collFind<RVuelo, int>(cvue, r.idVue, cmpRVueloIdVuelo, rVueloFromString);

    RVuelo rvue = collGetAt<RVuelo>(cvue, pos, rVueloFromString);

    int idCiudadDestino = rvue.vue.idDes;

    pos = collFind<RCiudad, int>(cciu, idCiudadDestino, cmpRCiudadIdCiudad, rCiudadFromString);

    RCiudad rCiuDes = collGetAt<RCiudad>(cciu, pos, rCiudadFromString);

    rCiuDes.cont++;

    collSetAt<RCiudad>(cciu, rCiuDes, pos, rCiudadToString);
}

void procesarPunto2(Reserva r, Coll<RVuelo> &cvue)
{
    int pos = collFind<RVuelo, int>(cvue, r.idVue, cmpRVueloIdVuelo, rVueloFromString);

    RVuelo rvue = collGetAt<RVuelo>(cvue, pos, rVueloFromString);

    if (r.cant <= rvue.vue.cap)
    {
        rvue.vue.cap -= r.cant;

        collSetAt<RVuelo>(cvue, rvue, pos, rVueloToString);
    }

    else
    {
        rvue.contRe += r.cant;
        collSetAt<RVuelo>(cvue, rvue, pos, rVueloToString);
    }
}

void procesarPunto3(Reserva r, Coll<RVuelo> cvue, Coll<RCiudad> cciu, Coll<RCliente> &ccli)
{
    int posicionVuelo = collFind<RVuelo, int>(cvue, r.idVue, cmpRVueloIdVuelo, rVueloFromString);

    RVuelo elVuelo = collGetAt<RVuelo>(cvue, posicionVuelo, rVueloFromString);

    int posicionOrigen = collFind<RCiudad, int>(cciu, elVuelo.vue.idOri, cmpRCiudadIdCiudad, rCiudadFromString);

    RCiudad ciudadDeOrigen = collGetAt<RCiudad>(cciu, posicionOrigen, rCiudadFromString);

    int posicionDestino = collFind<RCiudad, int>(cciu, elVuelo.vue.idDes, cmpRCiudadIdCiudad, rCiudadFromString);

    RCiudad ciudadDeDestino = collGetAt<RCiudad>(cciu, posicionDestino, rCiudadFromString);

    int diferenciaDeMillas = (abs(ciudadDeDestino.ciu.millas - ciudadDeOrigen.ciu.millas));

    creoCliente(collCliente, r.idCli, diferenciaDeMillas, r.cant);
}

void mostrarPunto1(Coll<RCiudad> cciu)
{
    while (collHasNext<RCiudad>(cciu))
    {
        RCiudad x = collNext<RCiudad>(cciu, rCiudadFromString);

        cout << x.ciu.descr << "fue elegido por " << x.cont << " familias" << endl;
    }

    cout << "------------------------ " << endl;
}

void mostrarPunto2(Coll<RVuelo> cvue)
{
    while (collHasNext<RVuelo>(cvue))
    {
        RVuelo v = collNext<RVuelo>(cvue, rVueloFromString);

        bool estaCompleto = (v.vue.cap == 0);

        cout << "El vuelo " << v.vue.idVue << " tiene " << v.contRe << " plazas rechazadas. Sale completo: " << estaCompleto << endl;
    }

    cout << "------------------------ " << endl;
}

void mostrarPunto3(Coll<RCliente> ccli)
{
    while (collHasNext<RCliente>(collCliente))
    {
        RCliente c = collNext<RCliente>(collCliente, rClienteFromString);

        cout << "El cliente " << c.idCli << " cuenta con " << c.acum << " millas acumuladas." << endl;
    }
}

int main()
{
    // estructura de datos
    Coll<RVuelo> cvue = subirVuelos();
    Coll<RCiudad> cciu = subirCiudades();
    Coll<RCliente> ccli = coll<RCliente>();

    FILE *f = fopen("RESERVAS.dat", "r+b");
    Reserva r = read<Reserva>(f);
    while (!feof(f))
    {
        procesarPunto1(r, cvue, cciu);
        procesarPunto2(r, cvue);
        procesarPunto3(r, cvue, cciu, ccli);
        r = read<Reserva>(f);
    }

    mostrarPunto1(cciu);
    mostrarPunto2(cvue);
    mostrarPunto3(ccli);

    fclose(f);

    return 0;
}
#endif
