#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
using namespace std;

using namespace std;

struct Producto
{
	int idPro;
	char descr[8];
	double precio;
	int idRub;
};

struct Rubro
{
	int idRub;
	char descr[20];
	double dto;
};

void writePRODUCTOS()
{
	mkdir("EmisionDeTickets");
	FILE* f = fopen("EmisionDeTickets/PRODUCTOS.dat","w+b");
	Producto r;

	r.idPro=1;
	strcpy(r.descr,"Manteca");
	r.precio=100.0;
	r.idRub=1;
	fwrite(&r,sizeof(Producto),1,f);

	r.idPro=2;
	strcpy(r.descr,"Leche  ");
	r.precio=80.0;
	r.idRub=1;
	fwrite(&r,sizeof(Producto),1,f);

	r.idPro=3;
	strcpy(r.descr,"Yogurt ");
	r.precio=80.0;
	r.idRub=1;
	fwrite(&r,sizeof(Producto),1,f);

	r.idPro=4;
	strcpy(r.descr,"Escoba ");
	r.precio=250.0;
	r.idRub=2;
	fwrite(&r,sizeof(Producto),1,f);

	r.idPro=5;
	strcpy(r.descr,"Deterge");
	r.precio=180.0;
	r.idRub=2;
	fwrite(&r,sizeof(Producto),1,f);

	r.idPro=6;
	strcpy(r.descr,"Trapo d");
	r.precio=50.0;
	r.idRub=2;
	fwrite(&r,sizeof(Producto),1,f);

	r.idPro=7;
	strcpy(r.descr,"Galleti");
	r.precio=100.0;
	r.idRub=3;
	fwrite(&r,sizeof(Producto),1,f);

	r.idPro=8;
	strcpy(r.descr,"Aceite ");
	r.precio=180.0;
	r.idRub=3;
	fwrite(&r,sizeof(Producto),1,f);

	r.idPro=9;
	strcpy(r.descr,"Vinagre");
	r.precio=100.0;
	r.idRub=3;
	fwrite(&r,sizeof(Producto),1,f);

	r.idPro=10;
	strcpy(r.descr,"Sal    ");
	r.precio=50.0;
	r.idRub=3;
	fwrite(&r,sizeof(Producto),1,f);

	fclose(f);
}

void writeRUBROS()
{
	mkdir("EmisionDeTickets");
	FILE* f = fopen("EmisionDeTickets/RUBROS.dat","w+b");
	Rubro r;

	r.idRub=1;
	strcpy(r.descr,"Lacteo             ");
	r.dto=1.0;
	fwrite(&r,sizeof(Rubro),1,f);

	r.idRub=2;
	strcpy(r.descr,"Limpieza           ");
	r.dto=0.95;
	fwrite(&r,sizeof(Rubro),1,f);

	r.idRub=3;
	strcpy(r.descr,"Almacen            ");
	r.dto=1.0;
	fwrite(&r,sizeof(Rubro),1,f);

	fclose(f);
}

string productoToDebug(Producto x)
{
	stringstream sout;
	sout<< "[";
	sout << x.idPro;
	sout << ",";
	sout << x.descr;
	sout << ",";
	sout << x.precio;
	sout << ",";
	sout << x.idRub;
	sout<< "]";
	return sout.str();
}

void readPRODUCTOS()
{
	FILE* f = fopen("EmisionDeTickets/PRODUCTOS.dat","r+b");
	Producto r;

	fread(&r,sizeof(Producto),1,f);
	while(!feof(f))
	{
		cout << productoToDebug(r) << endl;
		fread(&r,sizeof(Producto),1,f);
	}

	fclose(f);
}

string rubroToDebug(Rubro x)
{
	stringstream sout;
	sout<< "[";
	sout << x.idRub;
	sout << ",";
	sout << x.descr;
	sout << ",";
	sout << x.dto;
	sout<< "]";
	return sout.str();
}

void readRUBROS()
{
	FILE* f = fopen("EmisionDeTickets/RUBROS.dat","r+b");
	Rubro r;

	fread(&r,sizeof(Rubro),1,f);
	while(!feof(f))
	{
		cout << rubroToDebug(r) << endl;
		fread(&r,sizeof(Rubro),1,f);
	}

	fclose(f);
}

int main()
{
	cout << "--" << "PRODUCTOS.dat" << "--" << endl;
	writePRODUCTOS();
	readPRODUCTOS();

	cout << "--" << "RUBROS.dat" << "--" << endl;
	writeRUBROS();
	readRUBROS();

	return 0;
}
