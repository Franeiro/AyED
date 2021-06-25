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
#include "hospedaje.hpp"
using namespace std;

/*

------------------FLUJO DE TRABAJO------------------------

- Tomo los archivos de caracteristicas y Casas y los subo a memoria
-Creo un registro de busquedas con todas las busquedas
-Del archivo de busquedas, a cada busqueda le asigno un numero de peticiones, que sale de averiguoPeticiones();
    - averiguoPeticiones() toma el id mask de casa busqueda y cuenta si, por posicion, hay o no una peticion y acumula.

-Mediante averiguoCoincidencias(), tomo el id mask de las caracteristicas de cada casa y lo comparo con la busqueda. Me fijo caracter a caracter si casa[x]==busqueda[y] y si ese valor es 1, retorno una coincidencia.
- Despues, le asigno un valor de coincidencia a cada casa
- Mediante concordancia() tomo el id de una casa, el idmask de una peticion y realizo las operatorias de arriba y retorno coincidencias/peticiones




--------------------------------------------------------



*/

//SUBO LAS CASAS Y LAS CARACTERISTICAS A MEMORIA

Coll<RegistroCaracteristicas> subirCaracteristicas()
{
    Coll<RegistroCaracteristicas> collCaracteristicas = coll<RegistroCaracteristicas>();

    FILE *caracteristicas = fopen("CARACTERISTICAS.dat", "rb");

    Caract unaCaracteristica = read<Caract>(caracteristicas);

    while (!feof(caracteristicas))
    {
        RegistroCaracteristicas rc = registroCaracteristicas(unaCaracteristica);
        collAdd<RegistroCaracteristicas>(collCaracteristicas, rc, registroCaracteristicasToString);
        unaCaracteristica = read<Caract>(caracteristicas);
    }

    fclose(caracteristicas);
    return collCaracteristicas;
}

Coll<RegistroCasas> subirCasas()
{
    Coll<RegistroCasas> collCasas = coll<RegistroCasas>();

    FILE *casas = fopen("CASAS.dat", "rb");

    Casa unaCasa = read<Casa>(casas);

    while (!feof(casas))
    {
        RegistroCasas rCasas = registroCasas(unaCasa, 0);
        collAdd<RegistroCasas>(collCasas, rCasas, registroCasasToString);
        unaCasa = read<Casa>(casas);
    }

    fclose(casas);
    return collCasas;
}

Coll<RegistroBusqueda> collBusqueda = coll<RegistroBusqueda>();

int cmpRegistroBusquedaCaract(RegistroBusqueda b, int caract)
{
    return b.busqueda.caractMask - caract;
}

void averiguoPeticiones(Coll<RegistroBusqueda> unaBusqueda, RegistroBusqueda regBus, Casa casa)
{

    int posicion = collFind<RegistroBusqueda, int>(unaBusqueda, regBus.busqueda.caractMask, cmpRegistroBusquedaCaract, registroBusquedaFromString);

    RegistroBusqueda rb = collGetAt<RegistroBusqueda>(unaBusqueda, posicion, registroBusquedaFromString);

    int caracteristicasBusqueda = rb.busqueda.caractMask;
    int peticiones = 0;

    for (int i = 0; i <= digitCount(caracteristicasBusqueda); i++)
    {
        int digito = i;
        int d = getDigit(caracteristicasBusqueda, i);

        if (d == 1)
        {
            peticiones++;
        }
    }

    rb.peticiones = peticiones;

    collSetAt<RegistroBusqueda>(unaBusqueda, rb, posicion, registroBusquedaToString);
}

int cmpRegistroCasaIdCasa(RegistroCasas c, int id)
{
    return c.casa.idCasa - id;
}

void averiguoCoincidencias(Coll<RegistroCasas> &unaCasa, Coll<RegistroBusqueda> unaBusqueda, RegistroBusqueda regBus, Casa casa)
{

    int posicionCasas = collFind<RegistroCasas, int>(unaCasa, casa.caractMask, cmpRegistroCasaIdCasa, registroCasasFromString);

    RegistroCasas rc = collGetAt<RegistroCasas>(unaCasa, posicionCasas, registroCasasFromString);

    int posicion = collFind<RegistroBusqueda, int>(unaBusqueda, regBus.busqueda.caractMask, cmpRegistroBusquedaCaract, registroBusquedaFromString);

    RegistroBusqueda rb = collGetAt<RegistroBusqueda>(unaBusqueda, posicion, registroBusquedaFromString);

    int peticiones = rb.peticiones;

    int maskCasa = rc.casa.caractMask;
    int maskBusqueda = regBus.busqueda.caractMask;
    int coincidencia = 0;

    if (digitCount(maskCasa) > digitCount(maskBusqueda))
    {
        for (int i = 0; i <= digitCount(maskBusqueda); i++)
        {
            int a = getDigit(maskBusqueda, i);
            int b = getDigit(maskCasa, i);
            if (a == b && a == 1)
            {
                coincidencia++;
            }
        }
    }
    if (digitCount(maskCasa) <= digitCount(maskBusqueda))
    {
        for (int i = 0; i <= digitCount(maskCasa); i++)
        {
            int a = getDigit(maskBusqueda, i);
            int b = getDigit(maskCasa, i);
            if (a == b && a == 1)
            {
                coincidencia++;
            }
        }
    }

    rc.coinicidencias = coincidencia;

    collSetAt<RegistroCasas>(unaCasa, rc, posicionCasas, registroCasasToString);
}

int coinidenciasCasa(int idCasa, Coll<RegistroCasas> unaCasa)
{
    int posicionCasas = collFind<RegistroCasas, int>(unaCasa, idCasa, cmpRegistroCasaIdCasa, registroCasasFromString);

    RegistroCasas rc = collGetAt<RegistroCasas>(unaCasa, posicionCasas, registroCasasFromString);

    return rc.coinicidencias;
}

int cmpRegistroBusquedaId(RegistroBusqueda b, int id)
{
    return b.busqueda.idUsr - id;
}

int peticionesBusqueda(int mask, Coll<RegistroBusqueda> unaBusqueda)
{
    int posicionBusqueda = collFind<RegistroBusqueda, int>(unaBusqueda, mask, cmpRegistroBusquedaId, registroBusquedaFromString);

    RegistroBusqueda rb = collGetAt<RegistroBusqueda>(unaBusqueda, posicionBusqueda, registroBusquedaFromString);

    return rb.peticiones;
}

double concordancia(int idCasa, int mask, Coll<RegistroBusqueda> unaBusqueda, Coll<RegistroCasas> unaCasa)
{
    int peticiones = peticionesBusqueda(mask, unaBusqueda);
    int coincidencias = coinidenciasCasa(idCasa, unaCasa);

    return coincidencias / peticiones;
}

int main()
{
    Coll<RegistroCasas> collCasas = subirCasas();
    Coll<RegistroCaracteristicas> collCaracteristicas = subirCaracteristicas();
    Coll<RegistroBusqueda> collBusqueda = coll<RegistroBusqueda>();

    FILE *f = fopen("BUSQUEDA.dat", "rb");

    Busqueda unaBusqueda = read<Busqueda>(f);

    while (!feof(f))
    {

        leerBusqueda(unaBusqueda);
        concordancia(collCasas, unaBusqueda);
        unaBusqueda = read<Busqueda>(f);
    }
}

#endif