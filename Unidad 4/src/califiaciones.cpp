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
#include "califiaciones.hpp"

using namespace std;


// VERSION 1. EL arhivo esta ordenado por asignatura.

int main ()
{

    FILE* f = fopen("CALIFIACIONES.dat", "r+b");

    //Lee el primer registro del arhivo
    Califiacion reg = read <Califiacion>(f);


    while(!feof(f))
    {
        int cont =0;
        int acum =0;

        //guarda la asignatura anterior
        int idAsigAnt = reg.idAsig;


        //se fija si la asignatura leida es la misma que la anterior
        while (idAsigAnt == reg.idAsig)
        {
            cont ++;
            acum += reg.calif;

            reg = read<Califiacion>(f);
        }
        
        double prom = acum/(double) cont;
        cout <<idAsigAnt << ":"<<prom <<endl;


    }


    fclose(f);
    


    return 0;
}


//Version 2. EL archivo no se encuentra ordenado y no se saben cuantas asignaturas hay

Coll <Estad> collEstad = coll <Estad>();

int buscarElemento (Coll<Estad>& collEstad, int id)
{
    int pos = collFind<Estad, int> (collEstad,id,cmpEstadId,estadFromString);

    if (pos<0)
    {
        Estad x = estad(id,0,0);
        pos = collAdd<Estad>(collEstad,x,estadToString);
    }

    return pos;
}

int cmpEstadInt (Estad e, int id)
{
    return e.id - id;
}

void mostrarResultados (Coll<Estad>c)
{
    collReset<Estad>(c);

    while (collHasNext<Estad>(c))
    {
        Estad e = collNext<Estad>(c, estadFromString);

        double prom = e.acum/(double) e.cont;
        cout <<e.id<<":"<<prom<<endl;
    }
}


int main ()
{
    FILE* f = fopen("CALIFIACIONES.dat", "r+b");

    Coll<Estad> collEstad = coll<Estad>();

    Califiacion reg = read <Califiacion> (f);

    while (!feof(f))
    {
        int pos = buscarElemento(collEstad, reg.idAsig);

        Estad elm = collGetAt<Estad>(collEstad,pos,estadFromString);

        elm.cont ++;
        elm.acum+= reg.calif;
        collSetAt<Estad> (collEstad,elm,pos,estadToString);

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

int main ()
{
    
}


#endif
