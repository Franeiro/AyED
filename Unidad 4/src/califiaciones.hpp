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

//V1
struct Califiacion
{
    int idAsig;
    int idESt;
    int calif;

};


//V2
struct Estad // por cada asignatura, crea un Estad.
            // si el id ya existe, le suma la nota. Sino, crea la asignatura.
{
    int id;
    int cont;
    int acum;
};

//V3
struct Asignatura
{
    int idAsign;
    char nomAsig[30];
    char maestroACargo[50];
};



#endif