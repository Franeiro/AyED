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
#include "facultad.hpp"
using namespace std;

Coll<RegistroCurso> subirCursos()
{
    Coll<RegistroCurso> regCur = coll<RegistroCurso>();

    FILE *f = fopen("CURSOS.dat", "r+b");
    ;

    int tamanio = fileSize<int>(f);

    Curso unCurso = read<Curso>(f);

    if (tamanio > 0)
    {
        while (!feof(f))
        {
            RegistroCurso rc = registroCurso(unCurso);

            collAdd<RegistroCurso>(regCur, rc, registroCursoToString);

            unCurso = read<Curso>(f);
        }
    }
    fclose(f);
    return regCur;
}

int cmpIdCursos(RegistroCurso a, int idCurso)
{
    return a.curso.idCur - idCurso;
}

void reasignacion(int alumno, int curso, Coll<RegistroCurso> &collCursos, Coll<Reasignacion> &collReasignacion, Coll<Revision> &collRevision)
{
    // obtengo la materia a partir del id del curso y busco que curso tiene capacidad de esa misma materia.
    int idCursoNuevo;

    int averiguoPos = collFind<RegistroCurso, int>(collCursos, curso, cmpIdCursos, registroCursoFromString);

    RegistroCurso elCurso = collGetAt<RegistroCurso>(collCursos, averiguoPos, registroCursoFromString);

    string materia = elCurso.curso.materia;

    bool encontro;
    while (collHasNext<RegistroCurso>(collCursos))
    {
        RegistroCurso curso = collNext<RegistroCurso>(collCursos, registroCursoFromString);

        if (curso.curso.materia == materia)
        {
            if (curso.curso.cap > 0)
            {
                idCursoNuevo = curso.curso.idCur;
                encontro = true;
                break;
            }
        }
    }

    if (encontro)
    {
        Reasignacion reasig = reasignacion(alumno, idCursoNuevo);
        collAdd<Reasignacion>(collReasignacion, reasig, reasignacionToString);
    }

    else
    {
        Revision rev = revision(alumno, materia);
        collAdd<Revision>(collRevision, rev, revisionToString);
    }
}

int cmpMaterias(RegistroCurso a, RegistroCurso b)
{
    string sA = a.curso.materia;
    string sB = b.curso.materia;

    return sA < sB ? -1 : sA > sB ? 1
                                  : 0;
}

void mostrarMaterias(Coll<RegistroCurso> &collCursos)
{
    collSort<RegistroCurso>(collCursos, cmpMaterias, registroCursoFromString, registroCursoToString);
    collReset<RegistroCurso>(collCursos);
    while (collHasNext<RegistroCurso>(collCursos))
    {
        RegistroCurso curso = collNext<RegistroCurso>(collCursos, registroCursoFromString);

        if (curso.curso.cap < 0)
        {
            string materia = curso.curso.materia;
            int cursoId = curso.curso.idCur;
            cout << materia << cursoId << endl;
        }
    }
}

int cmpIdAlumnos(Revision a, Revision b)
{
    return a.idAlu - b.idAlu;
}

void mostrarRevision(Coll<Revision> collRevision)
{
    collSort<Revision>(collRevision, cmpIdAlumnos, revisionFromString, revisionToString);
    collReset<Revision>(collRevision);
    while (collHasNext<Revision>(collRevision))
    {
        Revision revision = collNext<Revision>(collRevision, revisionFromString);

        cout << revision.idAlu << " todavia sigue sin inscribirse a " << revision.materia << endl;
    }
}

int cmpIdAlumnos2(Reasignacion a, Reasignacion b)
{
    return a.idAlu - b.idAlu;
}

void mostrarReasignacion(Coll<Reasignacion> collReasignacion)
{
    collSort<Reasignacion>(collReasignacion, cmpIdAlumnos2, reasignacionFromString, reasignacionToString);
    collReset<Reasignacion>(collReasignacion);
    while (collHasNext<Reasignacion>(collReasignacion))
    {
        Reasignacion revision = collNext<Reasignacion>(collReasignacion, reasignacionFromString);

        cout << revision.idAlu << " ha sido inscrito a " << revision.idCurReasig << endl;
    }
}

void procesarInscripcion(int alumno, int curso, Coll<RegistroCurso> &collCursos, Coll<Reasignacion> collReasignacion, Coll<Revision> collRevision)
{
    int posicionCurso = collFind<RegistroCurso, int>(collCursos, curso, cmpIdCursos, registroCursoFromString);

    RegistroCurso elCurso = collGetAt<RegistroCurso>(collCursos, posicionCurso, registroCursoFromString);

    if (elCurso.curso.cap > 0)
    {
        elCurso.curso.cap--;
    }
    else
    {

        reasignacion(alumno, curso, collCursos, collReasignacion, collRevision);
    }

    collSetAt<RegistroCurso>(collCursos, elCurso, posicionCurso, registroCursoToString);
}

int main()
{

    Coll<RegistroCurso> collCursos = subirCursos();

    Coll<Reasignacion> collReasignacion;

    Coll<Revision> collRevision;

    FILE *c = fopen("INSCRIPCIONES.DAT", "r+b");

    Inscripcion unaInscripcion = read<Inscripcion>(c);

    while (!feof(c))
    {
        int alumno = unaInscripcion.idAlu;
        int curso = unaInscripcion.idCur;

        procesarInscripcion(alumno, curso, collCursos, collReasignacion, collRevision);
    }

    // FALTA HACER EL PUNTO 1 :((((((

    mostrarMaterias(collCursos);

    mostrarReasignacion(collReasignacion);

    mostrarRevision(collRevision);
}

#endif