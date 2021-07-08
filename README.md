# AyED

#### Archivos de Consulta
- Son relativamente estáticos, sus datos no varian

#### Archivos de Novedades
- El contenido es dinámico, es lo que debemos procesar

### Problemas de Corte de Control

Los registros se encuentran ordenados segun cierto criterio. Se pueden armar subconjuntos con aquellos registros que esten con un mismo identificador

### Problemas de Apareo de Archivos

Se busca intercalar el contenido de dos o mas archivos que estan ordenados por una misma clave

```c++
struct Alumno
{
  int legajo;   <-------
  char nombre[50];
 };
 
 struct Nota
{
  int legajo;  <------
  int nota;
 };
 
 ```
  
  

Se pueden recorrer los dos archivos a la par, leyendo en el primer renglon del primer archivo y comparando con el primer renglon del segundo archivo

### Problemas de Procesamiento Directo

Si no se corresponde con ningun planteo anterior, es procesamiento directo

Recorremos el archivo de novedades y procesamos cada uno de sus registros

## Busqueda sobre Archivos

###  *Subir a Memoria el Archivo*

**Subida del Archivo**

```c++
Coll<Ciudad> subirCiudades()
{
// abrimos el archivo

FILE* f = fopen("CIUDADES.dat","r+b");

// creamos una coleccion vacia
Coll<Ciudad> c = coll<Ciudad>();

// recorremos el archivo
Ciudad r = read<Ciudad>(f);

while( !feof(f) )
{
// agregamos el registro a la coleccion
collAdd<Ciudad>(c,r,ciudadToString);

r = read<Ciudad>(f);
}
// cerramos el archivo y retornamos la coleccion

fclose(f);
return c;
}

```

**Buscar Registro**

```c++

Ciudad buscarCiudad(Coll<Ciudad> c,int id,bool& encontrado)
{
int pos = collFind<Ciudad,int>(c,id ,cmpCiudadId,ciudadFromString);

// asignamos true o false al parametro encontrado
encontrado = pos>=0;
Ciudad ret;
if( encontrado )
{
ret = collGetAt<Ciudad>(c,pos,ciudadFromString);
}
return ret;
}
```

*Busqueda Binaria sobre un archivo*

Cuando el archivo de consulta es extenso, no se puede subir a memoria.
Si se enceuntra ordenado por algun campo, se puede usar Busqueda Binaria

**Buscar Registro**

Suponiendo que ABONADOS.dat esta ordenado por  ``` idAbo```  desarrollamos

```c++
Abonado buscarAbonado(FILE* f,int id,bool& encontrado)
{
encontrado = false;
int i = 0;

// primer registro
int j = fileSize(f)-1; // ultimo registro
Abonado ret;
while( i<=j && !encontrado )
{
// posicion intermedia entre i y j
int k = (i+j)/2;

// accedo al archivo y veo si encuentro lo que busco
seek<Abonado>(f,k);
ret = read<Abonado>(f);

// actualizo los indices
i = id>a.idAbo?k+1:i;
j = id<a.idAbo?k-1:j;
encontrado = i>=j;
}
return ret;
}

```

*Indexar un archivo*

Si el archivo NO esta ordenado y es extenso, lo unico que queda es indexarlo

Se crea un indice para vincular el valor de busqueda de cada regsitro con al posicion que ocupa el registro dentro del archivo


Creamos una coleccion de estructuras que solo tiene 2 campos: Registro Clave y Posicion

Creamos una estructura que vincule una clave con una posicion dentro del archivo. Siguiendo la estrctura anterior de Abonado

```c++
struct AbonadoIdx
{
    int idAbo;      // clave
    int pos;       // posicion
};
```

Indexamos

```c++

Coll<AbonadoIdx> indexarAbonados(FILE* f)
{
Coll<AbonadoIdx> c = coll<AbonadoIdx>();

// nos movemos al inicio del archivo
seek<Abonado>(0);
Abonado a = read<Abonado>(f);
while( !feof(f) )
{
// creo el elemento con el id y la posicion
AbonadoIdx elm = {a.idAbo,filePos<Abonado>(f)-1};

// lo agrego a la coleccion
collAdd<AbonadoIdx>(c,elm,abonadoIdxToString);
a = read<Abonado>(f);
}
return c;
}

```

Y finalmente Buscamos

```c++

Abonado buscarAbonadoIdx(FILE* f ,Coll<AbonadoIdx> c ,int id ,bool encontrado)
{
int pos = collFind<AbonadoIdx,int>(c ,id ,cmpAbonadoIdxId ,abonadoidxFromString);
encontrado = false;
Abonado ret;

if( pos>=0 )
{
encontrado = true;

// obtengo el elemento de la coleccion
AbonadoIdx elm = collGetAt<AbonadoIdx>(c,pos,abonadoIdxFromString);

// accedo al archivo y veo si encuentro lo que busco
seek<Abonado>(f,elm.pos);
ret = read<Abonado>(f);
}
return ret;
}

```
## Ordenar Archivos

No se ordenan directamente, porque estariamos reescribiendolos. Usamos estas técnicas

*Ordenamiento en Memoria*

Si el archivo es chico, lo subimos a memoria y de ahi la ordenamos

```c++
Coll<Ciudad> c = subirCiudades();
collSort<Ciudad>(c, cmpCiudadDescr // criterio de ordenamiento ,ciudadFromString ,ciudadToString);

collReset<Ciudad>(c);
while( collHasNext<Ciudad>(c) )
{

Ciudad ciu = collNext<Ciudad>(c,ciudadFromString);
cout << ciudadToString(ciu) << endl;
}

// FUNCION DE ORDENAMIENTO

int cmpCiudadDescr(Ciudad a,Ciudad b)
{
string aDescr = a.descr;
string bDescr = b.descr;
return aDescr<bDescr?-1:aDescr>bDescr?1:0;
}

```

*Ordenamiento por Indexacion*

Si el archivo es extenso, podemos indexarlo y ordenar su indice

```c++
// abrimos el archivo
FILE* f = fopen("ABONADOS.dat","r+b");

// lo indexamos
Coll<AbonadoIdx> idx = indexarAbonados(f);

// ordenamos el indice
collSort<AbonadoIdx>(idx,cmpAbonadoId // criterio de ordenamiento,abonadoIdxFromString,abonadoIdxToString);

// recorremos el indice y accedemos en orden a los registros del archivo
collReset<AbonadoIdx>(idx);
while( collHasNext<AbonadoIdx>(idx) )
{
AbonadoIdx x=collNext<AbonadoIdx>(idx,abonadoIdxFromString);

// accedo al archivo
seek<Abonado>(f,x.pos);
Abonado a = read<Abonado>(f);

// muestro
cout << abonadoToString(a) << endl;
}
fclose(f);

//FUNCION DE ORDENAMIENTO 

int cmpAbonadoId(Abonado a,Abonado b)
{
return a.idAbo-b.idAbo;
}

```

## CASO TESTIGO

*Una escuela prepara informes estadísticos sobre el rendimiento de sus estudiantes en las diferentes asignaturas. Se dispone del archivo CALIFI-
CACIONES.dat, cuya estructura de registro es la siguiente:*

```c++
struct Calificacion
{
    int idAsig;    // identificador de la asignatura
    int idEst;      // identificador del estudiante
    int calif;         // calificación obtenida durante el bimestre
};
```

### Corte de Control

- El archivo esta ordenado por ```c++   idAsig   ```

```c++

int main()
{
// abrimos el archivo
FILE* f = fopen("CALIFICACIONES.dat","r+b");

// leemos el primer registro del archivo
Calificacion reg = read<Calificacion>(f);

// controlamos que no llegue el fin del archivo
while( !feof(f) )
{
// SECCION DE INICIALIZACION
int cont = 0;
int acum = 0;

// guardamos la asignatura anterior
int idAsigAnt = reg.idAsig;
while( !feof(f) && idAsigAnt == reg.idAsig )
{
// SECCION DE PROCESAMIENTO
cont++;
acum += reg.calif;

// leemos el siguiente registro del archivo
reg = read<Calificacion>(f);
}

// SECCION DE RESULTADOS

// mostramos la calificacion promedio obtenida
// para la asignatura cuyos registros acabamos
// de procesar


double prom = acum/(double)cont;
cout << idAsigAnt << ": " << prom << endl;


}

// cerramos el archivo
fclose(f);
return 0;
}

```

## Corte de Control con salida bufferizada

*Informar por cada asignatra la lista de estudiante aprobados, ordenada decrecientemente por calificacion*

```c++
struct Calificacion
{
    int idAsig;   // identificador de la asignatura
    int idEst;    // identificador del estudiante
    int calif;    // calificación obtenida durante el bimestre
};

```

```c++

int main()
{
// abrimos el archivo
FILE* f = fopen("CALIFICACIONES.dat","r+b");

// leemos el primer registro del archivo
Calificacion reg = read<Calificacion>(f);

// controlamos que no llegue el fin del archivo
while( !feof(f) )
{
    // SECCION DE INICIALIZACION
    Coll<Calificacion> buff = coll<Calificacion>();
    
    // guardamos la asignatura anterior
    int idAsigAnt = reg.idAsig;
    while( !feof(f) && idAsigAnt == reg.idAsig )
    {
    
    // SECCION DE PROCESAMIENTO
    if( reg.calif>=4 )
    {
    collAdd<Calificacion>(buff
    ,reg
    ,calificacionToString);
    }
    
    // leemos el siguiente registro del archivo
    reg = read<Calificacion>(f);
    }
    
    // SECCION DE RESULTADOS
    mostrarEstudiantesAprobados(idAsigAnt,buff);
}

// cerramos el archivo
fclose(f);
return 0;
}
```

En ```c++   buff   ```  guardamos los datos a medida q van llegando para ordenarlo y mostrarlo

La funcion que ordena y muestra la coleccion: 

```c++
void mostrarEstudiantesAprobados(int idAsig
{
    ,Coll<Calificacion> buff)
    
    // mostramos la asignatura
    cout << "Asignatura: " << idAsig << endl;
    
     // ordenamos la coleccion
    collSort<Calificacion>(buff,cmpCalificacion, calificacionFromString,calificacionToString);
    
    // la iteramos
    collReset<Calificacion>(buff);
    while( collHasNext<Calificacion>(buff) )
    {
    Calificacion elm = collNext<Calificacion>(buff,calificacionFromString);
    
    // mostramos los estudiantes aprobados
    cout << elm.idEst << ", " << elm.calif << endl;
    }
}

//FUNCION DE ORDENAMIENTO

int cmpCalificacion(Calificacion a,Calificacion b)
{
    return b.calif-a.calif;
}


```

## Descubrimiento

*Los archivos no tienen ningun orden*

Necesitamos disponer de  contadores y acumuladores: uno para cada asignatura cuya calificacion debemos procesar

```c++

struct Estad
{
    int id;   // identificador
    int cont;  // contador
    int acum;   // acumulador
};

```

Creamos la coleccion de estructuras ```Estad```

```c++

Coll<Estad> collEstad = coll<Estad>();

```
1- Recorremos el archivo
2- Por cada registrousamos ```idAsig``` para buscarlo en ```collEstad```

  a.Si no existe en ```collEstad```, lo agregamos, iniciandolo con (0,0)
  
3- Incrementamos ```cont``` y acumulamos ```calif``` en ```acum```


```c++

int main()
{
FILE* f = fopen("CALIFICACIONES.dat","r+b");

// coleccion de contadores y acumuladores
Coll<Estad> collEstad = coll<Estad>();

// leemos el primer registro del archivo
Calificacion reg = read<Calificacion>(f);
while( !feof(f) )
{
// buscamos (y eventualmente agragamos) en la coll

int pos = descubrirElemento(collEstad,reg.idAsig);

// procesamos
Estad elm = collGetAt<Estad>(collEstad,pos,estadFromString);

elm.cont++;
elm.acum += reg.calif;

collSetAt<Estad>(collEstad,elm,pos,estadToString);

// leemos el siguiente registro

reg = read<Calificacion>(f);

}
// resultados

mostrarResultados(collEstad);

fclose(f);
return 0;
}

int descubrirElemento(Coll<Estad>& collEstad,int id)
{
// buscamos
int pos = collFind<Estad,int>(collEstad,id,cmpEstadId,estadFromString);

// si no se encontro el elemento, lo agregamos
if( pos<0 )
{
Estad x = estad(id,0,0);
pos = collAdd<Estad>(collEstad,x,estadToString);
}
return pos;
}


int cmpEstadId(Estad e,int id)
{
  return e.id-id;
}

void mostrarResultados(Coll<Estad> c)
{
// iteramos
collReset<Estad>(c);

    while( collHasNext<Estad>(c) )
    {
    Estad e = collNext<Estad>(c,estadFromString);
    double prom = e.acum/(double)e.cont;
    cout << e.id << ": " << prom << endl;
    }
}


```
  
## Archivo de Consultas en Memoria

*Se pide: emitir dos listados, ambos detallando la calificación promedio obte-
nida por los estudiantes de cada asignatura. El primero debe estar ordenado alfabé-
ticamente por asignatura (nomAsig), tal como se muestra a la izquierda. El segundo
listado debe estar ordenado decrecientemente según la calificación promedio, tal
como se ilustra a la derecha.*

```c++
struct Calificacion    //NOVEDADES
{
    int idAsig;
    int idEst;
    int calif;
};

struct Asignatura    //COMPLEMENTA A NOVEDADES
{
  int idAsig;
  char nomAsig[30];
  char maestroACargo[50];

};
´´´

Submos el archivo de consultas a memoria y hacemos que cada uno de sus elementos tenga un contador y un acumulador asociados

```c++
struct RAsignatura
{
  Asignatura asig;
  Estad estad;
};

stuct Estad 
{
  int cont;
  int acum;
 };
 
 
 Coll<RAsignatura> subirAsignaturas()
{
// coleccion que contendra todas las asignaturas

Coll<RAsignatura> ret = coll<RAsignatura>();
FILE* f = fopen("ASIGNATURAS.dat","r+b");


// leemos el primer registro del archivo
Asignatura reg = read<Asignatura>(f);
while( !feof(f) )
{
    // creamos un RAsignatura con las funciones de inic
    RAsignatura ra = rAsignatura(reg,estad(0,0));
    
    // lo agregamos a la coleccion
    collAdd<RAsignatura>(ret,ra,rAsignaturaToString);
    
    // leemos el siguiente registro
    reg = read<Asignatura>(f);
  }
  
fclose(f);

return ret;
}

void mostrarResultados(Coll<RAsignatura> c,int cmpRAsignatura(RAsignatura,RAsignatura))
{
    // ordenamos la coleccion
    collSort<RAsignatura>(c,cmpRAsignatura,rAsignaturaFromString,rAsignaturaToString);
    
    // iteramos
    collReset<RAsignatura>(c);
    while( collHasNext<RAsignatura>(c) )
    {
    RAsignatura ra = collNext<RAsignatura>(c,rAsignaturaFromString);
    
    // calculamos el promedio y mostramos
    double prom = ra.estad.acum/(double)ra.estad.cont;
    string sNomAsig = ra.asig.nomAsig;
    cout << sNomAsig << ": " << prom << endl;
    }
}

// funcion de comparacion, compara alfabeticamente
int cmpRAsigAlfabetico(RAsignatura a,RAsignatura b)
{
    string sA = a.asig.nomAsig;
    string sB = b.asig.nomAsig;
    return sA<sB?-1:sA>sB?1:0;
    }
    
// funcion de comparacion, compara por promedio descendente
int cmpRAsigPromedio(RAsignatura a,RAsignatura b)
{
    double pA = a.estad.acum/(double)a.estad.cont;
    double pB = b.estad.acum/(double)b.estad.cont;
    return pA>pB?-1:pA<pB?1:0;
}

int main()
  {
  // subimos el archivo de consultas a memoria
  Coll<RAsignatura> collAsig = subirAsignaturas();
  FILE* f = fopen("CALIFICACIONES.dat","r+b");
  Calificacion reg = read<Calificacion>(f);
  while( !feof(f) )
  {
  // buscamos la asignatura en la coleccion
  int pos = collFind<RAsignatura,int>(collAsig,reg.idAsig,cmpRAsigId,rAsignaturaFromString);
  
  // obtenemos el elemento encontrado en la posicion pos
  RAsignatura elm = collGetAt<RAsignatura>(collAsig,pos,rAsignaturaFromString);
  
  // procesamos
  elm.estad.cont++;
  elm.estad.acum += reg.calif;
  
  // aplicamos los cambios en la coleccion
  collSetAt<RAsignatura>(collAsig,elm,pos,rAsignaturaToString);
  
  // leemos el siguiente registro
  reg = read<Calificacion>(f);
  }
  
  // mostramos el listado 1 (ordenado alfabeticamente)
  
  mostrarResultados(collAsig,cmpRAsigAlfabetico);
  
  // mostramos el listado 2 (ordenado por prom descend)
  
  mostrarResultados(collAsig,cmpRAsigPromedio);
  
  fclose(f);
  return 0;
}

int cmpRAsigId(RAsignatura ra,int id)
{
  return ra.asig.idAsig-id;
}

```

## Actualizar Registros

*Por cada Asignatura, mostrar el promedio anterior y el nuevo promedio*
*Actualizar el archivo de Asignaturas con los nuevos promedios*

```c++

struct Calificacion
{
    int idAsig;
    int idEst;
    int calif;
};

struct Asigantura
{
  int idAsig;
  char nomAsig[30];
  char maestroACargo[50];
  double califProm;
 };

```

Creamos ```RAsignatura``` y ```Estad```

```c++
struct RAsignatura
{
    Asignatura asig;
    Estad estad;
};

struct Estad
{
  int cont;
  int acum;
```
Para el punto 1, no es necesario ordenar la coleccion

```c++
void mostrarResultados(Coll<RAsignatura> c)
{
  // iteramos
  collReset<RAsignatura>(c);
  while( collHasNext<RAsignatura>(c) )
  {
  RAsignatura ra = collNext<RAsignatura>(c,rAsignaturaFromString);
  
  // promedios anterior y actual
  double promAct = ra.estad.acum/(double)ra.estad.cont;
  double promAnt = ra.asig.califProm;
  string sNomAsig = ra.asig.nomAsig;
  cout<<sNomAsig<<": "<<promAnt<<", "<<promAct << endl;
  }
}
```

Punto 2

```c++
int main()
{
    // subimos el archivo de consultas a memoria
    Coll<RAsignatura> collAsig = subirAsignaturas();
    FILE* f = fopen("CALIFICACIONES.dat","r+b");
    
    // leemos el primer registro del archivo
    Calificacion reg = read<Calificacion>(f);
    while( !feof(f) )
    {
    // buscamos la asignatura en la coleccion
    int pos = collFind<RAsignatura,int>(collAsig,reg.idAsig,cmpRAsigId,rAsignaturaFromString);
    
    // obtenemos el elemento encontrado en la posicion pos
    RAsignatura elm = collGetAt<RAsignatura>(collAsig,pos,rAsignaturaFromString);
    
    // procesamos
    elm.estad.cont++;
    elm.estad.acum += reg.calif;
    
    // aplicamos los cambios en la coleccion
    collSetAt<RAsignatura>(collAsig,elm,pos,rAsignaturaToString);
    // leemos el siguiente registro
    reg = read<Calificacion>(f);
  }
  // mostramos el listado requerido en el punto 1
  
  mostrarResultados(collAsig);
  
  // actualizamos el archivo de consultas
  actualizar(collAsig);
  
  fclose(f);
  return 0;

```
Estrategia para actualizar:
1- Recorrer el archivo de Consultas
2- Por cada registro leido, buscamos por ```idAsig``` en la coleccion```collAsig```
3- Calculamos nuevo promedio
4- Actualizamos el registro


```c++
void actualizar(Coll<RAsignatura> c)
{
  // "r+b" permite modificar registros y agregar al final
  
  FILE* f = fopen("ASIGNATURAS.dat","r+b");
  Asignatura reg = read<Asignatura>(f);
  while( !feof(f) )
  {
  int pos = collFind<RAsignatura,int>(collAsig,reg.idAsig,cmpRAsigId,rAsignaturaFromString);
 
 // obtenemos el elemento encontrado en la posicion pos
  RAsignatura elm = collGetAt<RAsignatura>(collAsig,pos,rAsignaturaFromString);
  double promAnt = elm.asig.califProm;
  double promAct = elm.estad.acum/(double)elm.estad.cont;
  double promNuevo = (promAnt+promAct)/2;
  
  // actualizamos el registro
  reg.califProm = promNuevo;
  
  // grabamos
  seek<Asignatura>(f,filePos<Asignatura>(f)-1);
  write<Asignatura>(f,reg);
  
  // leemos el siguiente registro
  reg = read<Asignatura>(f);
  }
  fclose(f);
  }
```


## Coleccion de Colecciones

*Se pide mostrar un listado indicando, por cada asignatura, el maestro a cargo, y la lista de estudiantes cuya calificación es inferior a 4 (cuatro).*

Crearemos una Estructura de Datos compuesta por una coleccion de escrituras

```c++
struct RAsignatura
{
    Asignatura asig;
    Coll<int> collEst;
};

```
Subimos el archivo de consulta a ```Coll<RAsignatura>```. Recorremos las novedades y por cada registro menor a 4 agregamos el ```idEst``` a la coleccion de estudiantes aplazados de esa asignatura

```c++

int main()
{
  // coleccion de asignaturas
  Coll<RAsignatura> collAsig = subirAsignaturas();
  FILE* f = fopen("CALIFICACIONES.dat", "r+b");
  
  // recorremos el archivo
  Calificacion reg = read<Calificacion>(f);
  while( !feof(f) )
  {
    procesarCalificacion(reg,collAsig);
    reg = read<Calificacion>(f);
  }
  
  // mostramos los resultados
  mostrarResultados(collAsig);
  
  fclose(f);
  return 0;
}
void procesarCalificacion(Calificacion reg
{
  if( reg.calif<4 )
  {
  int pos = collFind<RAsignatura,int>(collAsig,reg.idAsig,cmpRAsignaturaId,rAsignaturaFromString);
  
  // obtenemos el elemento encontrado en la posicion pos
  RAsignatura elm = collGetAt<RAsignatura>(collAsig,pos,rAsignaturaFromString);
  
  // agregamos el estudiante a la coleccion
  collAdd<int>(elm.collEst,reg.idEst,intToString);
  
  // actualizamos la coleccion de asignaturas
  collSetAt<RAsignatura>(collAsig,elm,pos,rAsignaturaToString);
  
  }
}

void mostrarResultados(Coll<RAsignatura> collAsig)
{
  // recorremos la coleccion de asignaturas
  collReset<RAsignatura>(collAsig);
  
  while( collHasNext<RAsignatura>(collAsig) )
  {
      RAsignatura ra = collNext<RAsignatura>(collAsig ,rAsignaturaFromString);
      
      // mostramos la asignatura
      string nomAsig = ra.asig.nomAsig;
      cout << nomAsig << endl;
      
      // recorremos la coleccion de estudiantes aplazados
      Coll<int> collEst = ra.collEst;
      collReset<int>(collEst);
      while( collHasNext<int>(collEst) )
      {
      int idEst = collNext<int>(collEst,stringToInt);
      
      // mostramos los estudiantes aplazados
      cout << idEst << endl;
      }
  }
}

```

La siguiente funcion sube a memoria las asignaturas
```c++
Coll<RAsignatura> subirAsignaturas()
{

  Coll<RAsignatura> ret = coll<RAsignatura>();
  FILE* f = fopen("ASIGNATURAS.dat","r+b");
  
  // leemos el primer registro del archivo
  Asignatura reg = read<Asignatura>(f);
  while( !feof(f) )
  {
  // creamos un RAsignatura
  RAsignatura ra = rAsignatura(reg,coll<int>(','));
  
  // lo agregamos a la coleccion
  collAdd<RAsignatura>(ret,ra,rAsignaturaToString);
  
  // leemos el siguiente registro
  reg = read<Asignatura>(f);
  }
  fclose(f);
  return ret;
}
```

## Coleccion de Colecciones con Descubrimiento

**CALIFICACIONES.dat y ASIGNATURAS.dat  no estan en orden**

```c++
struct Calificacion
{
  int idAsig;
  int idEst;
  int calif;
};

struct Asignatura
{
  int idAsig;
  char nomAsig[30];
  char maestroACargo[50];
};
```
**Asumiendo que un mismo maestro puede tener mas de una materia a cargo, mostrar un listado de estudiantes aplazados por maestro**

Armamos una coleccion de maestros y, por cada uno, una coleccion de estudiantes

```c++
  struct RMaestro
{
  string maestro;
  Coll<int> collEst;
};

```
Como no conocemos los maestros, los vamos descubriendo mientras procesamos las calificaciones


```c++

int main()
{
    // coleccion de asignaturas
  Coll<Asignatura> collAsig = subirAsignaturas();
  
  // coleccion de maestros
  Coll<RMaestro> collMaes = coll<RMaestro>();
  
  FILE* f = fopen("CALIFICACIONES.dat", "r+b");
  
  // recorremos el archivo
  Calificacion reg = read<Calificacion>(f);
  while( !feof(f) )
  {
  // procesamos
  procesarCalificacion(reg,collAsig,collMaes);
  
  // leemos el siguiente registro
  reg = read<Calificacion>(f);
  }
  
  // resultados
  mostrarResultados(collMaes);
  
  fclose(f);
  return 0;
  
  
  
}

```

```procesarCalificacion``` busca la asignatura  ``` reg.idAsig``` en la coleccion ``` collAsig``` para obtener el maestro a cargo.
Luego  busca al maestro en  ```collMaes```. Si no lo encuentra lo agrega


```c++


void procesarCalificacion(Calificacion reg,Coll<Asignatura> collAsig,Coll<RMaestro>& collMaes)
{
    if( reg.calif<4 )
  {
    // obtenemos el elemento de la coleccion
    Asignatura asig = buscarAsignatura(reg.idAsig ,collAsig);

    // buscamos, y si corresponde agregamos al maestro
    string maestro = asig.maestroACargo;
    int pos = buscarMaestro(collMaes,maestro);

    // obtenemos el elemento de la coleccion
    RMaestro rm = collGetAt<RMaestro>(collMaes,pos,rMaestroFromString);

    collAdd<int>(rm.collEst,reg.idEst,intToString);

    collSetAt<RMaestro>(collMaes,rm,pos,rMaestroToString);
  }
  }
  Asignatura buscarAsignatura(int id,Coll<Asignatura> collAsig)
  {
  // buscamos la asignatura
  int pos = collFind<Asignatura,int>(collAsig,id,cmpAsignaturaId,asignaturaFromString);

  // obtenemos el elemento de la coleccion
  Asignatura asig = collGetAt<Asignatura>(collAsig,pos,asignaturaFromString);

  return asig;
}

int buscarMaestro(Coll<RMaestro>& collMaes,string maestro)
{
    int pos = collFind<RMaestro,string>(collMaes,maestro,cmpRMaestroMaestro,rMaestroFromString);

    if( pos<0 )
    {
    RMaestro rm = rMaestro(maestro,coll<int>(','));
    pos = collAdd<RMaestro>(collMaes,rm,rMaestroToString);
    }
    return pos;
}

int cmpRMaestroMaestro(RMaestro rm,string m)
{
  return rm.maestro<m?-1:rm.maestro>m?1:0;
}

void mostrarResultados(Coll<RMaestro> collMaes)
  {
  // recorremos la coleccion de maestros
  collReset<RMaestro>(collMaes);
  while( collHasNext<RMaestro>(collMaes) )
  {
  RMaestro rm = collNext<RMaestro>(collMaes,rMaestroFromString);
  
  // mostramos el nombre del maestro
  string nomMaes = rm.maestro;
  cout << nomMaes << endl;
  
  // recorremos la coleccion de estudiantes aplazados
  Coll<int> collEst = rm.collEst;
  collRest<int>(collEst);
  while( collHasNext<int>(collEst) )
  {
  int idEst = collNext<int>(collEst,stringToInt);
  
  // mostramos los estudiantes aplazados
  cout << idEst << endl;
}
}
}

```
## Apareo de Archivos

**Se dispone de ASIGNATURAS19.dat y ASIGNATURAS20.dat. Los dos archivos estan ordenados por ```idAsig```**

**Mostrar:**
-Materias que se dictaron solo en 2019
-Materias que comenzaron a dictarse en 2020
-Asignaturas que se dictaron en ambos años, pero que estuvieron a cargo de maestros distintos

```c++
struct Asignatura
{
  int idAsig;
  char nomAsig[30];
  char maestroACargo[50];
  double califProm;
  
};```

Comenzamos leyendo la primera fila de A19 y A20 y comparamos los valores.
- Si a1<a2, la asignatura se dicto solo en 2019. Volvemos a leer el archivo del 2019
- Si a1>a2, la asignatura se empezo a dictar en 2020. Volvemos a leer el archivo del 2019
- Si a1===a2, leemos ambos archivos

-Si A2019 finalizo primero, todos los registros de A2020 representan materias que aparecieron en 2020
-Si A2020 finalizo primero, todos los registros de A2019 represtan materias que solo estaban en 2019


Como los listados tienen que aparecer por ```nomAsig```, a medida que detectemos cada caso lo vamos cargando en una coleccion

```c++

int main()
{
  Coll<Asignatura> coll1 = coll<Asignatura>(); // solo 19
  Coll<Asignatura> coll2 = coll<Asignatura>(); // solo 20
  Coll<Asignatura> collA = coll<Asignatura>(); // ambos
  
  FILE* f1 = fopen("ASIGNATURAS19.dat","r+b");
  FILE* f2 = fopen("ASIGNATURAS20.dat","r+b");
  
  Asignatura a1 = read<Asignatura>(f1);
  Asignatura a2 = read<Asignatura>(f2);
  
  while( !feof(f1) && !feof(f2) )
  {
    if( a1.idAsig<a2.idAsig )
    {
      // la asignatura solo se dicto en 2019
      collAdd<Asignatura>(coll1,a1,asignaturaToString);
      a1 = read<Asignatura>(f1);
    }
    else
    {
     if( a1.idAsig>a2.idAsig )
    {
      // la asignatura aparece en 2020
      collAdd<Asignatura>(coll2,a2,asignaturaToString);
      a2 = read<Asignatura>(f2);
    }
  else
  {
    // la asignatura se dicto ambos anios
    procesarPunto3(a1,a2,collA);
    a1 = read<Asignatura>(f1);
    a2 = read<Asignatura>(f2);
    }
  }
  }
  while( !feof(f1) )
  {
    // asignaturas que solo aparecen en 2020
    collAdd<Asignatura>(coll1,a1,asignaturaToString);
    a1 = read<Asignatura>(f1);
  }
  while( !feof(f2) )
  {
    // asignaturas que solo se dictaron en 2019
    collAdd<Asignatura>(coll2,a2,asignaturaToString);
    a2 = read<Asignatura>(f2);
  }
  
  // resultados
  mostrarResultados("Solo en 2019",coll1);
  
  mostrarResultados("Comenzo en 2020",coll2);
  
  mostrarResultados("Ambos anios, dif. maestros",collA);
  
  fclose(f2);
  
  fclose(f1);
  
  return 0;
}

void procesarPunto3(Asignatura a1,Asignatura a2,Coll<Asignatura>& collA)
{
  string maes1 = a1.maestroACargo;
  string maes2 = a2.maestroACargo;
  
  if( maes1 != maes2 )
  {
    collAdd<Asignatura>(collA,a1,asignaturaToString);
  }
}

void mostrarResultados(string msg,Coll<Asignatura> c)
{
  collSort<Asignatura>(c,cmpAsignatura,asignaturaFromString ,asignaturaToString);
  
  cout << msg << endl;
  while( collHasNext<Asignatura>(c) )
  {
    Asignatura a = collNext<Asignatura>(c,asignaturaFromString);
    cout << asignaturaToString(a) << endl;
  }
}


int cmpAsignatura(Asignatura x, Asignatura y)
{
  string m1 = x.maestroACargo;
  string m2 = y.maestroACargo;
  return m1<m2?-1:m1>m2?1:0;
}
```

## Apareo de Archivos con Corte de Control

**Se dispone de RENDI19 y RENDI20 ordenados por ```idAsig```**


``struct Rendi
{
  int idAsig;
  char comision;
  double califProm;
};``

**Se pide:**
-Para asignaturas dictadas solo en 2019, indicar cual fue la mejor y cual la peor calif. prom lograda por una comision
-Para asignaturas dictadas solo en 2020, calif. prom. general
-Para las de ambos años, un listado la calif prom del 2020 y en que proporcion aumento o disminuyo respectyo del 2019

Creamos 3 colecciones, una por cada item

``c++

struct Lst1
{
  int idAsig;
  char comMax;
  double max;
  char comMin;
  double min;
}; 

Coll <Lst1> coll1;

struct Lst2
{
  int idAsig;
  double promGral;
}; 

Coll <Lst2> coll2;

struct LstA
{
  int idAsig;
  double prom2;
  double porc;
}; 

Coll <LstA> coll2;
``

La estrategia es recorrer ambos archivos a la par para ver en cual de los 3 casos estamos

``c++
int main()
{
  Coll<Lst1> coll1 = coll<Lst1>();
  Coll<Lst2> coll2 = coll<Lst2>();
  Coll<LstA> collA = coll<LstA>();
  
  FILE* f1 = fopen("RENDI19.dat","r+b");
  FILE* f2 = fopen("RENDI20.dat","r+b");
  
  Rendi r1 = read<Rendi>(f1);
  Rendi r2 = read<Rendi>(f2);
  while( !feof(f1) && !feof(f2) )
  {
    if( r1.idAsig<r2.idAsig )
  {
    // solo 2019

    procesar1(f1,r1,coll1);
  
  }
  
  else
  {
    // solo 2020
    if( r1.idAsig>r2.idAsig )
      {
        procesar2(f2,r2,coll2);
      }
  else
  {
    // ambos anios
    procesarA(f1,r1,f2,r2,collA);
    }
   }
  }
  
  while( !feof(f1) )
  {
    procesar1(f1,r1,coll1);
  }
  while( !feof(f2) )
  {
   procesar2(f2,r2,coll2);
  }
  
  mostrarListado1(coll1);
  mostrarListado2(coll2);
  mostrarListadoA(collA);
  
  fclose(f2);
  fclose(f1);
  
  return 0;
}

void procesar1(FILE* f,Rendi& r,Coll<Lst1>& coll1)
{
  // el primer registro se maximo y minimo
  char comMax = r.comision;
  double max = r.califProm;
  
  // el primer registro es maximo y minimo
  char comMin = r.comision;
  double min = r.califProm;
  
  int idAsigAnt = r.idAsig;
  
  while( !feof(f) && r.idAsig==idAsigAnt )
  {
    if( r.califProm>max )
    {
    comMax = r.comision;
    max = r.califProm;
    }
    else  
    {
      if( r.califProm<min )
        {
        comMin = r.comision;
        min = r.califProm;
        }
    }
  r = read<Rendi>(f);
  }
  
  // agregamos un elemento tipo Lst1 a la collecion
  
  Lst1 elm = lst1(idAsigAnt,comMax,max,comMin,min);
  
  collAdd<Lst1>(coll1,elm,lst1ToString);
}

void procesar2(FILE* f,Rendi& r,Coll<Lst2>& coll2)
{
  int idAsig = r.idAsig;
  double prom = promCC(f,r);
  
  Lst2 elm = lst2(idAsig,prom);
  
  collAdd<Lst2>(coll2,elm,lst2ToString);
  
}

double promCC(FILE* f,Rendi& r)
{
  int cont = 0;
  double sum = 0;
  int idAsigAnt = r.idAsig;
  
  while( !feof(f) && r.idAsig==idAsigAnt )
  {
    sum+=r.califProm;
    cont++;
    r = read<Rendi>(f);
  }
  
  double prom = sum/cont;
  return prom;
}

void procesarA(FILE* f1,Rendi& r1,FILE* f2,Rendi& r2,Coll<LstA>& collA)

{
  int idAsig = r1.idAsig; // <-- ATENCION
  double prom1 = promCC(f1,r1); // corte de control y prom
  double prom2 = promCC(f2,r2); // corte de control y prom
  
  double porc = 100-prom1/prom2*100;
  
  LstA elm = lstA(idAsig,prom2,porc);
  
  collAdd<LstA>(collA,elm,lstAToString);
}


``


## Busqueda Binaria sobre Archivo de Consulta

**Se dispone de PADRON.dat, ordenado por ``idEst``, e INSCRIPCIONES.dat, sin orden**

``c++
struct Padron
{
  int idEst;
  int dni;
  char nombre[20];
  char telefono[20];
  char direccion[20];
  int codigoPostal;
  int fechaNacimiento;
  int idEscuela;
  int fechaMatriculacion;
  int idSeguroSocial;
};

struct Inscripcion
{
    int idEst;
    int idEscuela;
    int fecha; // fecha de la inscripcion (aaaammdd)
};
``
**Se pide generar el archivo INCONSISTENCIAS.dat con errores, detallando "Tipo de Problema" (1,2,3), "Nombre del estudiante" e "Identificador de la escuela"**

PROBLEMA 1: El estudiante no figura en el padron
PROBLEMA 2: El estudiante figura matriculado en una escuela distina a la que se inscribio
PROBLEMA 3: La fecha de inscripcion es anterior a la de matriculacion


La estrategia es recorrer el archivo de novedades (Inscripciones) y por cada una realizar una consulta al padron.
Aqui el archivo de consulta NO se puede subir a memoria porque es muy extenso. Como esta ordenado por ``idEst``, lo accedemos mediante busqueda binaria

```c++
struct Inconsistencia
{
  int idTipoProblema; // 1, 2 o 3
  char nombreEstudiante[20];
  int idEscuela;
};

#define ERR_ESTINEXIST 1; // error tipo 1
#define ERR_ESCUELADIF 2; // error tipo 2
#define ERR_FECHAANT 3; // error tipo 3
int main()
{
  // abrimos los archivos
  FILE* fIns = fopen("INSCRIPCIONES.dat","r+b");
  FILE* fPad = fopen("PADRON.dat","r+b");
  FILE* fOut = fopen("INCONSISTENCIAS.dat","w+b");
  
  Inscripcion ins = read<Inscripcion>(fIns);
  
  while( !feof(fIns) )
  {
  // buscamos el estudiante y asignamos true o false a enc segun encuentre o no
  
    bool enc;
    Padron pad = buscarEstudiante(ins.idEst,fPad,enc);
    
    // procesamos el registro
    procesarInscripcion(ins,pad,enc,fOut);
    
    // leemos el siguiente registro
    ins = read<Inscripcion>(fIns);
    }
    
// cerramos los archivos

fclose(fOut);
fclose(fPad);
fclose(fIns);
return 0;
}

void procesarInscripcion(Inscripcion ins,Padron pad,bool& enc,FILE* fOut)
{
  Inconsistencia out;
  // asignamos la escuela involucrada
  out.idEscuela = ins.idEscuela;
  if( !enc )
  {
    strcpy(out.nombreEstudiante,"desconocido!!");
    out.idTipoProblema = ERR_ESTINEXIST;
    write<Inconsistencia>(fOut,out);
  }
  else
  {
    // asignamos pad.nombre a out.nombreEstudiante
    strcpy(out.nombreEstudiante,pad.nombre);
    if( pad.idEscuela!=ins.idEscuela )
    {
      out.idTipoProblema = ERR_ESCUELADIF;
      write<Inconsistencia>(fOut,out);
    }
    else
    {
      if( fechaCmp(ins.fecha,pad.fechaMatriculacion)<0 )
      {
        out.idTipoProblema = ERR_FECHAANT;
        write<Inconsistencia>(fOut,out);
      }
    }
   }
}

Padron buscarEstudiante(int id,FILE* f,bool& enc)
{
  Padron ret;
  int i = 0;
  int j = fileSize<Padron>(f)-1;
  enc = false;
  while( i<=j && !enc)
  {
      int k = (i+j)/2;
      // posiciono y leo
      seek<Padron>(f,k);
      ret = read<Padron>(f);
      if( ret.idEst<id )
      {
         i = k+1;
      }
      else
      {
        if( ret.idEst>id )
        {
         j = k-1;
        }
        else
        {
          enc = true;
        }
      }
  }
  return ret;
  }
```
## Indexacion Directa

**Idem anterior, pero PADRON e INSCRIPCIONES estan desordenados**

La técnica de indexación lineal o directa consiste en subir a memoria sólo el campo del registro por el cual queremos buscar. De este modo, la búsqueda la realizaremos dentro de una colección, y la posición que dicha clave ocupa dentro de la colección coincidirá con la posición que el registro completo ocupa dentro del archivo

Es importante observar que ambas funciones reciben abierto el archivo sobre el que van a trabajar. Y no lo deben cerrar, pues será necesario utilizarlo durante el resto del programa.


idxCrear recorre el archivo subiendo el idEst (campo clave) de cada registro a una colección de enteros.

```c++

Coll<int> idxCrear(FILE* f)
{
  Coll<int> idx = coll<int>();
  
  // posicionamos al archivo en el primer registro
  seek<Padron>(f,0);
  Padron p = read<Padron>(f);
  while( !feof(f) )
  {
    collAdd<int>(idx,p.idEst,intToString);
    p = read<Padron>(f);
  
  }

  return idx;
}

Padron idxBuscar(int id, FILE* f,bool& enc,Coll<int> idx)
{
  Padron ret;
  int pos = collFind<int,int>(idx,id,cmpIntId,stringToInt);
  if( pos>=0 )
  {
    seek<Padron>(f,pos);
    ret = read<Padron>(f);
  }
  enc = pos>=0; //true o false
  return ret;
}

Padron buscarEstudiante(int id,FILE* f,bool& enc,Coll<int> idx)
{
  return idxBuscar(id,f,enc,idx);
}

#define ERR_ESTINEXIST 1; // error tipo 1
#define ERR_ESCUELADIF 2; // error tipo 2
#define ERR_FECHAANT 3; // error tipo 3
int main()
{
  // abrimos los archivos
  FILE* fIns = fopen("INSCRIPCIONES.dat","r+b");
  FILE* fPad = fopen("PADRON.dat","r+b");
  FILE* fOut = fopen("INCONSISTENCIAS.dat","w+b");
  
  // creamos el indice
  Coll<int> idx = idxCrear(fPad);
  
  Inscripcion ins = read<Inscripcion>(fIns);
  
  while( !feof(fIns) )
  {
      // buscamos el estudiante, asigna true o false a enc segun encuentre o no lo que busca
      
      bool enc;
      Padron pad = buscarEstudiante(ins.idEst,fPad,enc,idx);
      
      // procesamos el registro
      procesarInscripcion(ins,pad,enc,fOut);
      
      // leemos el siguiente registro
      ins = read<Inscripcion>(fIns);
  }
  // cerramos los archivos
  fclose(fOut);
  fclose(fPad);
  fclose(fIns);
  return 0;
}

```

## Indexacion Indirecta, con corte de Control

**Se pide un listado de los estudiantes empadronados, segun su codigo postal**

La estrategia será: indexar PADRON guardando en el índice la posición de cada registro, tal como lo hicimos previamente en el apartado de ordenamiento. Luego ordenaremos el índice, lo recorreremos con corte de control, y por cada elemento realizaremos un acceso directo al archivo para obtener todos los datos del registro.


```c++
struct Idx
{
  int codigoPostal;
  int pos;
}

Coll<Idx> indexarPadron(FILE* f)
{
  Coll<Idx> ret = coll<Idx>();
  
  // reseteamos el archivo
  seek<Padron>(f,0);
  
  // recorremos el archivo
  Padron p = read<Padron>(f);
  while( !feof(f) )
  {
      Idx i = idx(p.codigoPostal,filePos<Padron>(f)-1);
      collAdd<Idx>(ret,i,idxToString);
      p = read<Padron>(f);
  }
  // ordenamos el indice
  collSort<Idx>(ret,cmpIdx,idxFromString,idxToString);
  return ret;
}

int cmpIdx(Idx a,Idx b)
{
  return a.codigoPostal-b.codigoPostal;
}

int main()
{
  // abrimos el archivo e indexamos
  FILE* f = fopen("PADRON.dat","r+b");
  
  Coll<Idx> cIdx = indexarPadron(f);
  
  collReset<Idx>(cIdx);
  
  // recorremos con corte de control
  bool endOfColl;
  Idx i = collNext<Idx>(cIdx,endOfColl,idxFromString);
  while( !endOfColl )
  {
    // mostramos el codigo postal
    cout << "Codigo postal: " << i.codigoPostal << endl;
    
    // variable de control
    int codigoPostalAnt = i.codigoPostal;
    
    while( !endOfColl && codigoPostalAnt==i.codigoPostal)
    {
      // leemos el registro en la posicion pos
      
      Padron p = leerPadron(f,i.pos);
      // mosotramos los datos del estudiante
      
      cout << padronToString(p) << endl;
      // leemos el siguientes
      
      i = collNext<Idx>(cIdx,endOfColl,idxFromString);
    }
  }
  return 0;
}

Padron leerPadron(FILE* f,int pos)
{
  seek<Padron>(f,pos);
  return read<Padron>(f);
}

```

## Indexacion Indirecta Multiple

**En PADRON.dat, pueden existir estudiantes con el mismo ID**

Se pide:
- Listado de estudiantes empadronados correctamente
-Para los estudiantes con idEst duplicado, emitir un listado ordenador por idEst tal que contenga "ID", "Nombre", "DNI", "Telefono" y "Direccion".


Estrategia: Indexar el archivo en una coleccion cuyos elementos guaradan para cada idEst las posiciones del archivo en que aparece dicho identificador

```c++
struct Idx
{
  int idEst;
  Coll<int> collPos;
};
```
Vamos a recorrer el padron buscando, para cada registro, si existe o no una entrada en el indice. Si no existe, la creamos y agregamos la pos del registro a la collPos
Cuando terminemos de leer el archivo, el indice tendra tantas entradas como idEst diferentes existan.
Aquellas entradas cuya collPos tenga mas de un elemento, son los idEst repetidos.

```c++
int main()
{
  // indice
  Coll<Idx> cIdx = coll<Idx>();
  FILE* f = fopen("PADRON.dat","r+b");
  Padron r = read<Padron>(f);
  
  while( !feof(f) )
  {
    // buscamos por idEst y (si corresponde) agregamos
    int pos = descubrirEnIdx(r.idEst,cIdx);
    Idx x = collGetAt<Idx>(cIdx,pos,idxFromString);
    
    // agregamos la posicion del archivo a la coleccion
    int posArch = filePos<Padron>(f)-1;
    collAdd<int>(x.collPos,posArch,intToString);
    collSetAt<Idx>(cIdx,x,pos,idxToString);
    r = read<Padron>(f);
  }
  // ordenamos el indice
  collSort<Idx>(cIdx,cmpIdx,idxFromString,idxToString);
  
  // resultados
  mostrarListadoPunto1(cIdx,f);
  mostrarListadoPunto2(cIdx,f);
  fclose(f);
  return 0;
}

int cmpIdx(Idx a,Idx b)
{
  return a.idEst-b.idEst;
}

int descubrirEnIdx(int idEst,Coll<Idx>& cIdx)
{
  int pos = collFind<Idx,int>(cIdx,idEst,cmpIdxId,idxFromString);

  if( pos<0 )
  {
    Idx x = idx(idEst,coll<int>(','));
    pos = collAdd<Idx>(cIdx,x,idxToString);
  }
  return pos;
}

int cmpIdxId(Idx x,int id)
{
  return x.idEst-id;
}

void mostrarListadoPunto1(Coll<Idx> cIdx,FILE* f)
{
  cout << "--ESTUDIANTES EMPADRONADOS--" << endl;
  // iteramos la coleccion
  collReset<Idx>(cIdx);
  while( collHasNext<Idx>(cIdx) )
  {
    Idx x = collNext<Idx>(cIdx,idxFromString);
    
    // verificamos que no haya idEst duplicados
    if( collSize<int>(x.collPos)==1 )
    {
      // nos posicionamos y leemos
      int posArch = collGetAt<int>(x.collPos,0,stringToInt);
      seek<Padron>(f,posArch);
      Padron p = read<Padron>(f);
      
      // mostramos
      cout << padronToString(p) << endl;
    }
  }
}


void mostrarListadoPunto2(Coll<Idx> cIdx,FILE* f)
{
  cout << "--ESTUDIANTES CON ERROR--" << endl;
  
  // iteramos la coleccion
  collReset<Idx>(cIdx);
  while( collHasNext<Idx>(cIdx) )
  {
    Idx x = collNext<Idx>(cIdx,idxFromString);
    
    // verificamos que no haya idEst duplicados
    if( collSize<int>(x.collPos)>1 )
    {
      // mostramos
      cout << "Id. Estudiante: " << x.idEst << endl;
      
      // posiciones de registros con error      
      Coll<int> collPos = x.collPos;
      
      // iteramos la coleccion
      collReset<int>(collPos);
      while( collHasNext<int>(collPos) )
      {
        int z = collNext<int>(collPos,stringToInt);
        
        // nos posicionamos y leemos
        seek<Padron>(f,z);
        Padron p = read<Padron>(f);
        
        // mostramos
        cout << padronToString(p) << endl;
      }
    }
  }
}
```

## Ordenar y Depurar un Archivo

**Generar PADRONFIX.dat asignando nuevos idEst a aquellos estudiantes cuyo idEst esté duplicado**

El programa principal es igual al anterior. La diferencia está al final, donde reemplazamos mostrarListadoPunto1 y mostrarListadoPunto2 por la función generarArchivo.

```c++

int main()
{
  // indice
  Coll<Idx> cIdx= coll<Idx>();
  FILE* f = fopen("PADRON.dat","r+b");
  Padron r = read<Padron>(f);
  while( !feof(f) )
  {
    // buscamos por idEst y (si corresponde) agregamos
    int pos = descubrirEnIdx(r.idEst,cIdx);
    Idx x = collGetAt<Idx>(cIdx,pos,idxFromString);
    
    // agregamos la posicion del archivo a la coleccion
    int posArch = filePos<Padron>(f)-1;
    collAdd<int>(x.collPos,posArch,intToString);
    collSetAt<Idx>(cIdx,x,pos,idxToString);
    r = read<Padron>(f);
  }
  // ordenamos y generamos el archivo
  generarArchivo(cIdx,f);
  fclose(f);
  return 0;
}

void generarArchivo(Coll<Idx> cIdx,FILE* f)
{
  FILE* fOut = fopen("PADRONFIX.dat","w+b");
  
  // ordenamos el indice
  collSort<Idx>(cIdx,cmpIdx,idxFromString,idxToString);
  
  // grabamos registros sin error
  collReset<Idx>(cIdx);
  while( collHasNext<Idx>(cIdx) )
  {
    Idx x = collNext<Idx>(cIdx,idxFromString);
    Coll<int> collPos = x.collPos;
    if( collSize<int>(collPos)==1 )
    {
      // grabamos
      int pos = collGetAt<int>(collPos,0,stringToInt);
      Padron p = leerPadron(f,pos);
      write<Padron>(fOut,p);
    }
    // el ultimo idEst de la coleccion + 1 es el proximo
    // idEst a partir del cual asignaremos a los registros
    Idx elm = collGetAt<Idx>(cIdx,collSize<int>(cIdx)-1,idxFromString);
    
    // nuevos idEst para los estudiantes con error
    int idEst = eml.idEst+1
    
    // grabamos registros con error
    collReset<Idx>(cIdx);
    while( collHasNext<Idx>(cIdx) )
    {
      Idx x = collNext<Idx>(cIdx,idxFromString);
      Coll<int> collPos = x.collPos;
      if( collSize<int>(collPos)>1 )
      {
        collReset<int>(collPos);
        while( collHasNext<int>(collPos) )
       {
          int pos = collNext<int>(collPos,stringToInt);
          Padron p = leerPadron(f,pos);
          p.idEst = idEst;
          write<Padron>(fOut,p);
          idEst++;
        }
    }
  }
}

Padron leerPadron(FILE* fPad,int pos)
{
  // posicionamos y leemos
  seek<Padron>(fPad,pos);
  Padron p = read<Padron>(fPad);
  
  return p;
}

struct Idx
{
  int idEst;
  int idEscuela;
  Coll <int> collPos;
};

int descubrirEnIdx(int idEst,int idEscuela,Coll<Idx>& cIdx)
{
  int pos = collFind<Idx,int>(cIdx,idEst,cmpIdxId,idxFromString);
  if( pos<0 )
  {
  Idx x = idx(idEst,idEscuela,coll<int>(','));
  pos = collAdd<Idx>(cIdx,x,idxToString);
  }
  return pos;
}


```






