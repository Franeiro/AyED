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
#include "aviacion.hpp"

using namespace std;

void mostrarCantDeVuelosPorCiudad();
int vuelosParaCiudad(int);
void mostrarPlazasRechazadas();
int capacidadMenosCantidad(int, int);

int main()
{
    FILE *prueba = fopen("CIUDADES.dat", "wb");

    Coll<Rechazadas> collRechazadas = coll<Rechazadas>();

    Ciudad f;
    f = ciudad(1, "A", 15);
    fwrite(&f, sizeof(Ciudad), 1, prueba);
    f = ciudad(2, "B", 20);
    fwrite(&f, sizeof(Ciudad), 1, prueba);
    f = ciudad(3, "C", 25);
    fwrite(&f, sizeof(Ciudad), 1, prueba);
    f = ciudad(4, "D", 30);
    fwrite(&f, sizeof(Ciudad), 1, prueba);

    fclose(prueba);

    FILE *pruebita = fopen("VUELOS.dat", "wb");

    Vuelo s;
    s = vuelo(1, 200, 2, 1);
    fwrite(&s, sizeof(Vuelo), 1, pruebita);
    s = vuelo(2, 100, 3, 1);
    fwrite(&s, sizeof(Vuelo), 1, pruebita);
    s = vuelo(3, 50, 2, 3);
    fwrite(&s, sizeof(Vuelo), 1, pruebita);
    s = vuelo(4, 800, 2, 1);
    fwrite(&s, sizeof(Vuelo), 1, pruebita);

    fclose(pruebita);

    FILE *pruebita2 = fopen("RESERVAS.dat", "wb");

    Reserva r;
    r = reserva(3, 2, 150);
    fwrite(&r, sizeof(Reserva), 1, pruebita2);
    r = reserva(1, 1, 2000);
    fwrite(&r, sizeof(Reserva), 1, pruebita2);
    r = reserva(2, 1, 50);
    fwrite(&r, sizeof(Reserva), 1, pruebita2);
    r = reserva(4, 3, 51);
    fwrite(&r, sizeof(Reserva), 1, pruebita2);

    fclose(pruebita2);

    mostrarCantDeVuelosPorCiudad();

    mostrarPlazasRechazadas();

    return 0;
}

void mostrarCantDeVuelosPorCiudad()
{
    FILE *ciudades = fopen("CIUDADES.dat", "r+b");

    Ciudad unaCiudad = read<Ciudad>(ciudades);

    while (!feof(ciudades))
    {
        int idCiudad = unaCiudad.idCiu;

        int cantidadDeVuelos = vuelosParaCiudad(idCiudad);

        cout << "Vuelos para ciudad " << idCiudad << ": " << cantidadDeVuelos << endl;

        unaCiudad = read<Ciudad>(ciudades);
    }
    cout << "-------------------------" << endl;
    fclose(ciudades);
}

int vuelosParaCiudad(int idCiudad)
{
    FILE *vuelos = fopen("VUELOS.dat", "r+b");

    Vuelo unVuelo = read<Vuelo>(vuelos);
    int contadorVuelos = 0;

    while (!feof(vuelos))
    {
        int idDestino = unVuelo.idDes;

        if (idDestino == idCiudad)
        {
            contadorVuelos++;
        }

        unVuelo = read<Vuelo>(vuelos);
    }

    return contadorVuelos;
}
/*
int cmpRechazadasId(Rechazadas r, int id)
{
    return r.idReservas - id;
}

int buscarReserva(Coll<Rechazadas> &collRechazadas, int id)
{
    int posicion = collFind<Rechazadas, int>(collRechazadas, id, cmpRechazadasId, rechazadasFromString);

    if (posicion < 0)
    {
        Rechazadas x = rechazadas(id, 0, 0);
        posicion = collAdd<Rechazadas>(collRechazadas, x, rechazadasToString);
    }

    return posicion;
}

void mostrarPlazasRechazadas(Coll<Rechazadas> &collRechazadas)
{
    FILE *reservas = fopen("RESERVAS.dat", "rb");

    Reserva unaReserva = read<Reserva>(reservas);

    while (!feof(reservas))
    {

        int pos = buscarReserva(collRechazadas, unaReserva.idVue);

        Rechazadas rechazadas = collGetAt<Rechazadas>(collRechazadas, pos, rechazadasFromString);

        rechazadas.cantidad += unaReserva.cant;

        collSetAt<Rechazadas>(collRechazadas, rechazadas, pos, rechazadasToString);

        int plazasRechazadas = capacidadMenosCantidad(rechazadas.cantidad, unaReserva.idVue);

        unaReserva = read<Reserva>(reservas);
    }

    fclose(reservas);
}

int capacidadMenosCantidad(int cantidadDeReserva, int idReserva)
{
    FILE *vuelos = fopen("VUELOS.dat", "rb");

    Vuelo unVuelo = read<Vuelo>(vuelos);

    int idVuelo = unVuelo.idVue;
    int capacidad = unVuelo.cap;

    while (!feof(vuelos))
    {
        if (idVuelo == idReserva)
        {
            return capacidad - cantidadDeReserva >= 0 ? 0 : abs(capacidad - cantidadDeReserva);
        }

        unVuelo = read<Vuelo>(vuelos);
    }

    return 0;

    fclose(vuelos);
}
*/

#endif