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
#include "hospedaje2.hpp"
using namespace std;

//SUBO LAS COLECCIONES A MEMORIA PARA ACCEDERLAS

Coll<RegistroCasas> subirCasas()
{

    Coll<RegistroCasas> regCasas = coll<RegistroCasas>();

    FILE *f = fopen("CASAS.dat", "rb");

    Casa unaCasa = read<Casa>(f);

    while (!feof(f))
    {
        RegistroCasas rc = registroCasas(unaCasa);

        collAdd<RegistroCasas>(regCasas, rc, registroCasasToString);

        unaCasa = read<Casa>(f);
    }

    fclose(f);
    return regCasas;
}

Coll<RegistroCaracteristicas> subirCaracteristicas()
{

    Coll<RegistroCaracteristicas> regCaracteristicas = coll<RegistroCaracteristicas>();

    FILE *f = fopen("Caracteristicas.dat", "rb");

    Caracteristicas unaCaracteristica = read<Caracteristicas>(f);

    while (!feof(f))
    {
        RegistroCaracteristicas rcar = registroCaracteristicas(unaCaracteristica);

        collAdd<RegistroCaracteristicas>(regCaracteristicas, rcar, registroCaracteristicasToString);

        unaCaracteristica = read<Caracteristicas>(f);
    }
    fclose(f);
    return regCaracteristicas;
}

Busqueda leerBusqueda(Coll<Busqueda> collBusqueda, int posicionBusqueda)
{
    Busqueda buscada = collGetAt<Busqueda>(collBusqueda, posicionBusqueda, busquedaFromString);

    return buscada;
}

RegistroCasas buscarCasa(Coll<RegistroCasas> collCasas, int posicionCasas)
{
    RegistroCasas unaCasa = collGetAt<RegistroCasas>(collCasas, posicionCasas, registroCasasFromString);

    return unaCasa;
}

int cmpRegistroCasasId(RegistroCasas a, int b)
{
    return a.casa.idCasa - b;
}

double concordancia(int idCasa, int mask)
{
    Coll<RegistroCasas> collCasas;
    int posCasa = collFind<RegistroCasas, int>(collCasas, idCasa, cmpRegistroCasasId, registroCasasFromString);

    RegistroCasas laCasa = collGetAt<RegistroCasas>(collCasas, posCasa, registroCasasFromString);

    int maskCasa = laCasa.casa.caractMask;

    int peticiones = 0;

    int coincidencias = 0;

    for (int i = 0; i <= digitCount(mask); i++)
    {

        int d = getDigit(mask, i);

        if (d == 1)
        {
            peticiones++;
        }
    }

    if (digitCount(maskCasa) > digitCount(mask))
    {
        for (int i = 0; i <= digitCount(mask); i++)
        {
            int a = getDigit(mask, i);
            int b = getDigit(maskCasa, i);
            if (a == b && a == 1)
            {
                coincidencias++;
            }
        }
    }
    if (digitCount(maskCasa) <= digitCount(mask))
    {
        for (int i = 0; i <= digitCount(maskCasa); i++)
        {
            int a = getDigit(mask, i);
            int b = getDigit(maskCasa, i);
            if (a == b && a == 1)
            {
                coincidencias++;
            }
        }
    }

    return coincidencias / peticiones;
}

bool seguirOperando(int idCasa)
{
    if (idCasa == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int cmpPromedio(GuardoYMuestro a, GuardoYMuestro b)
{
    double pa = a.concordancia;
    double pb = b.concordancia;
    return double(pb - pa);
}

void procesarBusqueda(Coll<Busqueda> collBusqueda, Coll<RegistroCasas> collCasas, int posicionBusqueda, Coll<GuardoYMuestro> collGYM)
{

    Busqueda busq = leerBusqueda(collBusqueda, posicionBusqueda);

    int posicionCasa = 0;

    double afinidad = 0;
    bool seguir;

    int mask = busq.caractMask;

    cout << "BUSQUEDA del usuario " << busq.idUsr << endl;

    for (int i = 0; i <= collSize(collCasas); i++)
    {
        RegistroCasas casa = buscarCasa(collCasas, posicionCasa);
        int idCasa = casa.casa.idCasa;
        seguir = seguirOperando(idCasa);

        if (seguir)
        {
            afinidad = concordancia(idCasa, mask);

            GuardoYMuestro resultado = collGetAt<GuardoYMuestro>(collGYM, i, guardoYMuestroFromString);

            resultado.concordancia = afinidad;
            resultado.idCasa = idCasa;

            collSetAt<GuardoYMuestro>(collGYM, resultado, i, guardoYMuestroToString);
        }

        posicionCasa++;
    }

    collSort<GuardoYMuestro>(collGYM, cmpPromedio, guardoYMuestroFromString, guardoYMuestroToString); // tengo que pasarlo como int pero es double

    collReset<GuardoYMuestro>(collGYM);
    while (collHasNext<GuardoYMuestro>(collGYM))
    {
        GuardoYMuestro i = collNext<GuardoYMuestro>(collGYM, guardoYMuestroFromString);

        if (i.concordancia > busq.tolerancia)
        {
            cout << " Nivel de coinicidencia: " << i.concordancia << endl;
        }
    }
}

int main()
{
    Coll<RegistroCaracteristicas> collCaracteristicas = subirCaracteristicas();
    Coll<RegistroCasas> collCasas = subirCasas();

    Coll<Busqueda> collBusqueda = coll<Busqueda>();
    Coll<GuardoYMuestro> collGYM = coll<GuardoYMuestro>();

    FILE *f = fopen("BUSQUEDAS.dat", "rb");

    Busqueda unaBusqueda = read<Busqueda>(f);
    int posicionBusqueda = 0;

    while (!feof(f))
    {
        procesarBusqueda(collBusqueda, collCasas, posicionBusqueda, collGYM);

        posicionBusqueda++;
    }
}

#endif;