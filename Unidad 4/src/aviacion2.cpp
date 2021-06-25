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
#include "aviacion2.hpp"

Coll<RegistroVuelo> subirVuelo()
{

    Coll<RegistroVuelo> registro = coll<RegistroVuelo>();

    FILE *f = fopen("VUELOS.dat", "r+b");

    Vuelo v = read<Vuelo>(f);
    while (!feof(f))
    {
        RegistroVuelo rv = registroVuelo(v, 0);
        collAdd<RegistroVuelo>(registro, rv, registroVueloToString);
        v = read<Vuelo>(f);
    }

    fclose(f);
    return registro;
}

Coll<RegistroCiudad> subirCiudad()
{
    Coll<RegistroCiudad> registro = coll<RegistroCiudad>();

    FILE *f = fopen("VUELOS.dat", "r+b");

    Ciudad v = read<Ciudad>(f);
    while (!feof(f))
    {
        RegistroCiudad rv = registroCiudad(v, 0);
        collAdd<RegistroCiudad>(registro, rv, registroCiudadToString);
        v = read<Ciudad>(f);
    }

    fclose(f);
    return registro;
}

int cmpRegistroVueloIdVuelo(RegistroVuelo regVue, int idVuelo)
{
    return regVue.unVuelo.idVue - idVuelo;
}

int cmpRegistroClienteId(RegistroCliente regCli, int idCli)
{
    return regCli.idCliente - idCli;
}

int cmpRegistroCiudadIdCiudad(RegistroCiudad regCiu, int idCiu)
{
    return regCiu.unaCiudad.idCiu - idCiu;
}

void procesarCliente(Coll<RegistroCliente> &collClientes, int idCliente, int millas)
{
    RegistroCliente unCliente{idCliente, 0};

    int posicionCliente = collFind<RegistroCliente, int>(collClientes, idCliente, cmpRegistroClienteId, registroClienteFromString);

    if (posicionCliente < 0)
    {
        posicionCliente = collAdd<RegistroCliente>(collClientes, unCliente, registroClienteToString);
    }

    RegistroCliente agregoCliente = collGetAt<RegistroCliente>(collClientes, posicionCliente, registroClienteFromString);

    agregoCliente.millasAcumuladas += millas;

    collSetAt<RegistroCliente>(collClientes, agregoCliente, posicionCliente, registroClienteToString);
}

Coll<RegistroVuelo> collVuelos = subirVuelo();

Coll<RegistroCiudad> collCiudades = subirCiudad();

Coll<RegistroCliente> collClientes = coll<RegistroCliente>();

void mostrarEstadoVuelo(Coll<RegistroVuelo> collVuelos)
{
    while (collHasNext<RegistroVuelo>(collVuelos))
    {
        RegistroVuelo x = collNext<RegistroVuelo>(collVuelos, registroVueloFromString);

        bool saleCompleto = (x.unVuelo.cap == 0);

        cout << "Plazas Rechazadas: " << x.acumulador << " Sale Completo: " << saleCompleto << endl;
    }
}

void mostrarMillasPorCliente(Coll<RegistroCliente> collClientes)
{
    while (collHasNext<RegistroCliente>(collClientes))
    {
        RegistroCliente c = collNext<RegistroCliente>(collClientes, registroClienteFromString);

        cout << "El cliente " << c.idCliente << " cuenta con " << c.millasAcumuladas << " Millas acumuladas" << endl;
    }
}

void mostrarDemandaPorCiudad(Coll<RegistroCiudad> collCiudades)
{
    while (collHasNext<RegistroCiudad>(collCiudades))
    {
        RegistroCiudad v = collNext<RegistroCiudad>(collCiudades, registroCiudadFromString);

        cout << v.unaCiudad.descr << "fue elegido por " << v.contador << " familias" << endl;
    }
}

Reservas unaReserva;

int main()
{
    while (unaReserva.idCli >= 0)
    {
        int posicionVuelo = collFind<RegistroVuelo, int>(collVuelos, unaReserva.idVue, cmpRegistroVueloIdVuelo, registroVueloFromString);

        RegistroVuelo elVuelo = collGetAt<RegistroVuelo>(collVuelos, posicionVuelo, registroVueloFromString);

        int posicionOrigen = collFind<RegistroCiudad, int>(collCiudades, elVuelo.unVuelo.idOri, cmpRegistroCiudadIdCiudad, registroCiudadFromString);

        RegistroCiudad ciudadDeOrigen = collGetAt<RegistroCiudad>(collCiudades, posicionOrigen, registroCiudadFromString);

        int posicionDestino = collFind<RegistroCiudad, int>(collCiudades, elVuelo.unVuelo.idDes, cmpRegistroCiudadIdCiudad, registroCiudadFromString);

        RegistroCiudad ciudadDeDestino = collGetAt<RegistroCiudad>(collCiudades, posicionDestino, registroCiudadFromString);

        int millas = abs(ciudadDeOrigen.unaCiudad.millas - ciudadDeDestino.unaCiudad.millas);

        if (unaReserva.cant <= elVuelo.unVuelo.cap)
        {
            procesarCliente(collClientes, unaReserva.idCli, millas);

            elVuelo.unVuelo.cap -= unaReserva.cant;

            collSetAt<RegistroVuelo>(collVuelos, elVuelo, posicionVuelo, registroVueloToString);
        }

        else
        {
            elVuelo.acumulador += unaReserva.cant;
            collSetAt<RegistroVuelo>(collVuelos, elVuelo, posicionVuelo, registroVueloToString);
        }

        ciudadDeDestino.contador++;

        collSetAt<RegistroCiudad>(collCiudades, ciudadDeDestino, posicionDestino, registroCiudadToString);
    }

    mostrarMillasPorCliente(collClientes);

    mostrarDemandaPorCiudad(collCiudades);

    mostrarEstadoVuelo(collVuelos);
}

#endif