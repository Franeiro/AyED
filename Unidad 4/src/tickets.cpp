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
#include "tickets.hpp"
using namespace std;

Coll<RegistroProductos> subirProductos()
{

    Coll<RegistroProductos> regProd = coll<RegistroProductos>();

    FILE *f = fopen("PRODUCTOS.dat", "r+b");
    ;

    int tamanio = fileSize<int>(f);

    //  cout << "Tamanio 1 = " << tamanio << endl;

    Producto unProducto = read<Producto>(f);
    //  cout << "7" << endl;
    if (tamanio > 0)
    {
        while (!feof(f))
        {
            RegistroProductos rp = registroProductos(unProducto, 0);
            //  cout << "8" << endl;

            collAdd<RegistroProductos>(regProd, rp, registroProductosToString);
            //  cout << "9" << endl;

            unProducto = read<Producto>(f);
            //  cout << "10" << endl;
        }
        //cout << "11" << endl;

        //cout << "12" << endl;
    }
    fclose(f);
    return regProd;
}

Coll<RegistroRubro> subirRubro()
{
    //  cout << "Entro a Rubros" << endl;
    Coll<RegistroRubro> regRub = coll<RegistroRubro>();

    FILE *r = fopen("RUBROS.dat", "r+b");
    int tamanio = fileSize<int>(r);

    Rubro unRubro = read<Rubro>(r);

    if (tamanio > 0)
    {

        while (!feof(r))
        {

            RegistroRubro rr = registroRubro(unRubro, 0);
            collAdd<RegistroRubro>(regRub, rr, registroRubroToString);

            unRubro = read<Rubro>(r);
        }
    }

    fclose(r);
    return regRub;
}

int cmpRegistroProductosId(RegistroProductos rp, int idProd)
{
    return rp.prod.idProd - idProd;
}

int cmpRegistroRubroId(RegistroRubro rr, int idRub)
{
    return rr.rubro.idRub - idRub;
}

void procesarItem(int idProducto, int cantidad, Coll<RegistroRubro> &regRub, Coll<RegistroProductos> &regProd, Coll<Item> &collItem, double &totalDescuento, double &total)
{
    int productoBuscado = collFind<RegistroProductos, int>(regProd, idProducto, cmpRegistroProductosId, registroProductosFromString);

    RegistroProductos elProducto = collGetAt<RegistroProductos>(regProd, productoBuscado, registroProductosFromString);

    int rubroDelProducto = elProducto.prod.idRub;

    int rubroBuscado = collFind<RegistroRubro, int>(regRub, rubroDelProducto, cmpRegistroRubroId, registroRubroFromString);

    RegistroRubro elRubro = collGetAt<RegistroRubro>(regRub, rubroBuscado, registroRubroFromString);

    Item unItem;

    unItem.descripcion = elProducto.prod.descr;
    unItem.precio = elProducto.prod.precio;
    unItem.cantidad = cantidad;

    elProducto.contador += cantidad;

    double descuento = (elProducto.prod.precio * elRubro.rubro.promo * cantidad);

    elRubro.ahorro += descuento;

    total += elProducto.prod.precio * cantidad;

    totalDescuento += total;

    collAdd<Item>(collItem, unItem, itemToString);

    collSetAt<RegistroProductos>(regProd, elProducto, productoBuscado, registroProductosToString);

    collSetAt<RegistroRubro>(regRub, elRubro, rubroBuscado, registroRubroToString);
}

int cmpItems(Item a, Item b)
{
    string sA = a.descripcion;
    string sB = b.descripcion;

    return sA < sB ? -1 : sA > sB ? 1
                                  : 0;
}

void mostrarTicket(Coll<Item> collItem, double total, double totalDescuento, int nroTicket, Coll<RegistroRubro> collRubros)
{
    collSort<Item>(collItem, cmpItems, itemFromString, itemToString);

    cout << "Numero de ticket:  " << nroTicket;

    while (collHasNext<Item>(collItem))
    {
        Item item = collNext<Item>(collItem, itemFromString);
        cout << item.descripcion << "   " << item.precio << "   " << total << "   " << item.cantidad << "   " << totalDescuento << endl;
    }

    while (collHasNext<RegistroRubro>(collRubros))
    {
        RegistroRubro elRubro = collNext<RegistroRubro>(collRubros, registroRubroFromString);

        cout << elRubro.rubro.descr << "    " << elRubro.ahorro << endl;
    }
}

int cmpDemanda(RegistroProductos a, RegistroProductos b)
{
    return a.contador - b.contador;
}

void mostrarDemanda(Coll<RegistroProductos> &collProductos)
{
    collSort<RegistroProductos>(collProductos, cmpDemanda, registroProductosFromString, registroProductosToString);

    while (collHasNext<RegistroProductos>(collProductos))
    {
        RegistroProductos elProducto = collNext<RegistroProductos>(collProductos, registroProductosFromString);

        cout << elProducto.prod.descr << " : " << elProducto.contador << endl;
    }
}

int main()
{

    FILE *prueba = fopen("PRODUCTOS.dat", "wb");

    Producto f;
    f = producto(1, "Leche", 15, 1);
    fwrite(&f, sizeof(Producto), 1, prueba);
    f = producto(2, "Salsa", 20, 2);
    fwrite(&f, sizeof(Producto), 1, prueba);
    f = producto(3, "Crema", 25, 1);
    fwrite(&f, sizeof(Producto), 1, prueba);
    f = producto(4, "Maiz", 30, 4);
    fwrite(&f, sizeof(Producto), 1, prueba);

    fclose(prueba);

    FILE *pruebita = fopen("RUBROS.dat", "wb");

    Rubro s;
    s = rubro(1, "Lacteos", 0.2);
    fwrite(&s, sizeof(Rubro), 1, pruebita);
    s = rubro(2, "Pastas", 1);
    fwrite(&s, sizeof(Rubro), 1, pruebita);
    s = rubro(3, "Chocolate", 0.5);
    fwrite(&s, sizeof(Rubro), 1, pruebita);
    s = rubro(4, "Maiz y Harina", 0.4);
    fwrite(&s, sizeof(Rubro), 1, pruebita);

    fclose(pruebita);

    Coll<RegistroProductos> collProductos = subirProductos();

    Coll<RegistroRubro> collRubros = subirRubro();

    int idCliente, nroTicket;
    double totalDescuento = 0, total = 0;

    cout << "Ingrese Numero de Cliente: " << endl;
    cin >> idCliente;

    while (idCliente >= 0)
    {
        int idProducto, cantidad;
        Coll<Item> collItem = coll<Item>();

        while (idProducto >= 0)
        {
            cout << "Ingrese el ID del Producto a comprar: ";
            cin >> idProducto;
            cout << "Ingrese la cantidad a comprar: ";
            cin >> cantidad;

            procesarItem(idProducto, cantidad, collRubros, collProductos, collItem, totalDescuento, total);
        }

        mostrarTicket(collItem, total, totalDescuento, nroTicket, collRubros);
        nroTicket++;

        mostrarDemanda(collProductos);
    }

    return 0;
}

#endif