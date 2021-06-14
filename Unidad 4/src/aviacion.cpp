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
int  capacidadDelVuelo(int, int);
void hacerReserva();

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
    r = reserva(1, 1, 2000);
    fwrite(&r, sizeof(Reserva), 1, pruebita2);
    r = reserva(3, 2, 150);
    fwrite(&r, sizeof(Reserva), 1, pruebita2);
    r = reserva(2, 1, 50);
    fwrite(&r, sizeof(Reserva), 1, pruebita2);
    r = reserva(4, 3, 51);
    fwrite(&r, sizeof(Reserva), 1, pruebita2);

    fclose(pruebita2);

    mostrarCantDeVuelosPorCiudad();

    hacerReserva();


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
-agarro una reserva.
-le paso el id de vuelo y la cantidad de pasajeros a la estruct VUELOS
-le resto la cantidad de reservas y actualizo si tiene capacidad para seguir haciendo reservas
- devuelvo, para cada vuelo, las plazas rechazadas y si el vuelo sale o no completo


*/

/*

FALTA QUE SE ACTUALICE SOLO LA CAPACIDAD DE LOS VUELOS Y MOSTAR UNA SOLA VEZ X VUELO.
FALTA HACERLO TODO DENTRO DE UNA MISMA APERTURA DE ARCHIVO

*/


void hacerReserva()
{
    FILE* reservas = fopen("RESERVAS.dat", "rb");

    Reserva unaReserva = read<Reserva>(reservas);

    while (!feof(reservas))
    {
        int idVuelo = unaReserva.idVue;
        int capacidad = unaReserva.cant;

        int capacidadFinal = capacidadDelVuelo(idVuelo, capacidad);
        
            if(capacidadFinal==0)
            {
                cout<<"El vuelo " <<idVuelo<<" sale completo"<<endl;
            }

            if(capacidadFinal>0)
            {
                cout<<"El vuelo " <<idVuelo<<" sale incompleto"<<endl;
                cout<<"Capacidad final: "<<capacidadFinal<<endl;
            }

            if(capacidadFinal<0)
            {
                cout <<"Plazas Rechazadas del vuelo " <<idVuelo<<" : "<<abs(capacidadFinal)<<"  El vuelo sale completo"<<endl;
            }

        unaReserva = read<Reserva>(reservas);
    }
    fclose(reservas);
    
}

int capacidadDelVuelo(int idVuelo, int capacidad)
{
    FILE* vuelos = fopen("VUELOS.dat", "rb");

    Vuelo unVuelo = read<Vuelo>(vuelos);
     int capacidadVuelo = unVuelo.cap;

    while(!feof(vuelos))
    {
        int idQueBusco=unVuelo.idVue;
        

        if(idQueBusco==idVuelo)
        {
            capacidadVuelo = unVuelo.cap;
            capacidadVuelo-=capacidad;
           
        }

        unVuelo = read<Vuelo>(vuelos);
        
    }




    return  capacidadVuelo;
 

}


#endif