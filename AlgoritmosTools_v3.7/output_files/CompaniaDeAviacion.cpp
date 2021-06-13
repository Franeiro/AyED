#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
using namespace std;

using namespace std;

struct Reserva
{
	int idCli;
	int idVue;
	int cant;
};

struct Vuelo
{
	int idVue;
	int cap;
	int idOri;
	int idDes;
};

struct Ciudad
{
	int idCiu;
	char descr[20];
	int millas;
};

void writeRESERVAS()
{
	mkdir("CompaniaDeAviacion");
	FILE* f = fopen("CompaniaDeAviacion/RESERVAS.dat","w+b");
	Reserva r;

	r.idCli=1;
	r.idVue=2;
	r.cant=1;
	fwrite(&r,sizeof(Reserva),1,f);

	r.idCli=3;
	r.idVue=2;
	r.cant=2;
	fwrite(&r,sizeof(Reserva),1,f);

	r.idCli=5;
	r.idVue=1;
	r.cant=3;
	fwrite(&r,sizeof(Reserva),1,f);

	r.idCli=2;
	r.idVue=2;
	r.cant=1;
	fwrite(&r,sizeof(Reserva),1,f);

	r.idCli=1;
	r.idVue=3;
	r.cant=5;
	fwrite(&r,sizeof(Reserva),1,f);

	r.idCli=3;
	r.idVue=1;
	r.cant=3;
	fwrite(&r,sizeof(Reserva),1,f);

	r.idCli=6;
	r.idVue=1;
	r.cant=2;
	fwrite(&r,sizeof(Reserva),1,f);

	r.idCli=2;
	r.idVue=2;
	r.cant=2;
	fwrite(&r,sizeof(Reserva),1,f);

	r.idCli=3;
	r.idVue=3;
	r.cant=6;
	fwrite(&r,sizeof(Reserva),1,f);

	r.idCli=1;
	r.idVue=1;
	r.cant=1;
	fwrite(&r,sizeof(Reserva),1,f);

	r.idCli=2;
	r.idVue=1;
	r.cant=1;
	fwrite(&r,sizeof(Reserva),1,f);

	fclose(f);
}

void writeVUELOS()
{
	mkdir("CompaniaDeAviacion");
	FILE* f = fopen("CompaniaDeAviacion/VUELOS.dat","w+b");
	Vuelo r;

	r.idVue=1;
	r.cap=10;
	r.idOri=1;
	r.idDes=4;
	fwrite(&r,sizeof(Vuelo),1,f);

	r.idVue=2;
	r.cap=15;
	r.idOri=2;
	r.idDes=1;
	fwrite(&r,sizeof(Vuelo),1,f);

	r.idVue=3;
	r.cap=12;
	r.idOri=4;
	r.idDes=3;
	fwrite(&r,sizeof(Vuelo),1,f);

	fclose(f);
}

void writeCIUDADES()
{
	mkdir("CompaniaDeAviacion");
	FILE* f = fopen("CompaniaDeAviacion/CIUDADES.dat","w+b");
	Ciudad r;

	r.idCiu=1;
	strcpy(r.descr,"Miami              ");
	r.millas=800;
	fwrite(&r,sizeof(Ciudad),1,f);

	r.idCiu=2;
	strcpy(r.descr,"Madrid             ");
	r.millas=2000;
	fwrite(&r,sizeof(Ciudad),1,f);

	r.idCiu=3;
	strcpy(r.descr,"Londres            ");
	r.millas=1500;
	fwrite(&r,sizeof(Ciudad),1,f);

	r.idCiu=4;
	strcpy(r.descr,"Paris              ");
	r.millas=700;
	fwrite(&r,sizeof(Ciudad),1,f);

	fclose(f);
}

string reservaToDebug(Reserva x)
{
	stringstream sout;
	sout<< "[";
	sout << x.idCli;
	sout << ",";
	sout << x.idVue;
	sout << ",";
	sout << x.cant;
	sout<< "]";
	return sout.str();
}

void readRESERVAS()
{
	FILE* f = fopen("CompaniaDeAviacion/RESERVAS.dat","r+b");
	Reserva r;

	fread(&r,sizeof(Reserva),1,f);
	while(!feof(f))
	{
		cout << reservaToDebug(r) << endl;
		fread(&r,sizeof(Reserva),1,f);
	}

	fclose(f);
}

string vueloToDebug(Vuelo x)
{
	stringstream sout;
	sout<< "[";
	sout << x.idVue;
	sout << ",";
	sout << x.cap;
	sout << ",";
	sout << x.idOri;
	sout << ",";
	sout << x.idDes;
	sout<< "]";
	return sout.str();
}

void readVUELOS()
{
	FILE* f = fopen("CompaniaDeAviacion/VUELOS.dat","r+b");
	Vuelo r;

	fread(&r,sizeof(Vuelo),1,f);
	while(!feof(f))
	{
		cout << vueloToDebug(r) << endl;
		fread(&r,sizeof(Vuelo),1,f);
	}

	fclose(f);
}

string ciudadToDebug(Ciudad x)
{
	stringstream sout;
	sout<< "[";
	sout << x.idCiu;
	sout << ",";
	sout << x.descr;
	sout << ",";
	sout << x.millas;
	sout<< "]";
	return sout.str();
}

void readCIUDADES()
{
	FILE* f = fopen("CompaniaDeAviacion/CIUDADES.dat","r+b");
	Ciudad r;

	fread(&r,sizeof(Ciudad),1,f);
	while(!feof(f))
	{
		cout << ciudadToDebug(r) << endl;
		fread(&r,sizeof(Ciudad),1,f);
	}

	fclose(f);
}

int main()
{
	cout << "--" << "RESERVAS.dat" << "--" << endl;
	writeRESERVAS();
	readRESERVAS();

	cout << "--" << "VUELOS.dat" << "--" << endl;
	writeVUELOS();
	readVUELOS();

	cout << "--" << "CIUDADES.dat" << "--" << endl;
	writeCIUDADES();
	readCIUDADES();

	return 0;
}
