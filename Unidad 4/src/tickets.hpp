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

struct Producto
{
    int idProd;
    char descr[20];
    double precio;
    int idRub;
};

struct Rubro
{
    int idRub;
    char descr[20];
    double promo;
};

struct Ventas
{
    Producto productoComprado;
    int cantidad;
};

struct Item
{
    string descripcion;
    double precio;
    double precioConDescuento;
    int cantidad;
};

struct RegistroProductos
{
    Producto prod;
    int contador;
};

struct RegistroRubro
{
    Rubro rubro;
    double ahorro;
};

string productoToString(Producto x)
{
    char sep = 1;
    string sIdProd = to_string(x.idProd);
    string sDescr = x.descr;
    string sPrecio = to_string(x.precio);
    string sIdRub = to_string(x.idRub);
    return sIdProd + sep + sDescr + sep + sPrecio + sep + sIdRub;
}

Producto productoFromString(string s)
{
    char sep = 1;
    Producto x;
    string t0 = getTokenAt(s, sep, 0);
    x.idProd = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.descr, t1.c_str());
    string t2 = getTokenAt(s, sep, 2);
    x.precio = stod(t2);
    string t3 = getTokenAt(s, sep, 3);
    x.idRub = stoi(t3);
    return x;
}

string productoToDebug(Producto x)
{
    stringstream sout;
    sout << "[";
    sout << x.idProd;
    sout << ",";
    sout << x.descr;
    sout << ",";
    sout << x.precio;
    sout << ",";
    sout << x.idRub;
    sout << "]";
    return sout.str();
}

Producto producto(int idProd, string descr, double precio, int idRub)
{
    Producto a;
    a.idProd = idProd;
    strcpy(a.descr, descr.c_str());
    a.precio = precio;
    a.idRub = idRub;
    return a;
}

bool productoEquals(Producto a, Producto b)
{
    if (a.idProd != b.idProd)
        return false;
    if (a.precio != b.precio)
        return false;
    if (a.idRub != b.idRub)
        return false;
    return true;
}

string rubroToString(Rubro x)
{
    char sep = 2;
    string sIdRub = to_string(x.idRub);
    string sDescr = x.descr;
    string sPromo = to_string(x.promo);
    return sIdRub + sep + sDescr + sep + sPromo;
}

Rubro rubroFromString(string s)
{
    char sep = 2;
    Rubro x;
    string t0 = getTokenAt(s, sep, 0);
    x.idRub = stoi(t0);
    string t1 = getTokenAt(s, sep, 1);
    strcpy(x.descr, t1.c_str());
    string t2 = getTokenAt(s, sep, 2);
    x.promo = stod(t2);
    return x;
}

string rubroToDebug(Rubro x)
{
    stringstream sout;
    sout << "[";
    sout << x.idRub;
    sout << ",";
    sout << x.descr;
    sout << ",";
    sout << x.promo;
    sout << "]";
    return sout.str();
}

Rubro rubro(int idRub, string descr, double promo)
{
    Rubro a;
    a.idRub = idRub;
    strcpy(a.descr, descr.c_str());
    a.promo = promo;
    return a;
}

bool rubroEquals(Rubro a, Rubro b)
{
    if (a.idRub != b.idRub)
        return false;
    if (a.promo != b.promo)
        return false;
    return true;
}

string ventasToString(Ventas x)
{
    char sep = 3;
    string sProductoComprado = productoToString(x.productoComprado);
    string sCantidad = to_string(x.cantidad);
    return sProductoComprado + sep + sCantidad;
}

Ventas ventasFromString(string s)
{
    char sep = 3;
    Ventas x;
    string t0 = getTokenAt(s, sep, 0);
    x.productoComprado = productoFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.cantidad = stoi(t1);
    return x;
}

string ventasToDebug(Ventas x)
{
    stringstream sout;
    sout << "[";
    sout << productoToDebug(x.productoComprado);
    sout << ",";
    sout << x.cantidad;
    sout << "]";
    return sout.str();
}

Ventas ventas(Producto productoComprado, int cantidad)
{
    Ventas a;
    a.productoComprado = productoComprado;
    a.cantidad = cantidad;
    return a;
}

bool ventasEquals(Ventas a, Ventas b)
{
    if (!productoEquals(a.productoComprado, b.productoComprado))
        return false;
    if (a.cantidad != b.cantidad)
        return false;
    return true;
}

string itemToString(Item x)
{
    char sep = 4;
    string sDescripcion = x.descripcion;
    string sPrecio = to_string(x.precio);
    string sPrecioConDescuento = to_string(x.precioConDescuento);
    string sCantidad = to_string(x.cantidad);
    return sDescripcion + sep + sPrecio + sep + sPrecioConDescuento + sep + sCantidad;
}

Item itemFromString(string s)
{
    char sep = 4;
    Item x;
    string t0 = getTokenAt(s, sep, 0);
    x.descripcion = t0;
    string t1 = getTokenAt(s, sep, 1);
    x.precio = stod(t1);
    string t2 = getTokenAt(s, sep, 2);
    x.precioConDescuento = stod(t2);
    string t3 = getTokenAt(s, sep, 3);
    x.cantidad = stoi(t3);
    return x;
}

string itemToDebug(Item x)
{
    stringstream sout;
    sout << "[";
    sout << x.descripcion;
    sout << ",";
    sout << x.precio;
    sout << ",";
    sout << x.precioConDescuento;
    sout << ",";
    sout << x.cantidad;
    sout << "]";
    return sout.str();
}

Item item(string descripcion, double precio, double precioConDescuento, int cantidad)
{
    Item a;
    a.descripcion = descripcion;
    a.precio = precio;
    a.precioConDescuento = precioConDescuento;
    a.cantidad = cantidad;
    return a;
}

bool itemEquals(Item a, Item b)
{
    if (a.descripcion != b.descripcion)
        return false;
    if (a.precio != b.precio)
        return false;
    if (a.precioConDescuento != b.precioConDescuento)
        return false;
    if (a.cantidad != b.cantidad)
        return false;
    return true;
}

string registroProductosToString(RegistroProductos x)
{
    char sep = 5;
    string sProd = productoToString(x.prod);
    string sContador = to_string(x.contador);
    return sProd + sep + sContador;
}

RegistroProductos registroProductosFromString(string s)
{
    char sep = 5;
    RegistroProductos x;
    string t0 = getTokenAt(s, sep, 0);
    x.prod = productoFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.contador = stoi(t1);
    return x;
}

string registroProductosToDebug(RegistroProductos x)
{
    stringstream sout;
    sout << "[";
    sout << productoToDebug(x.prod);
    sout << ",";
    sout << x.contador;
    sout << "]";
    return sout.str();
}

RegistroProductos registroProductos(Producto prod, int contador)
{
    RegistroProductos a;
    a.prod = prod;
    a.contador = contador;
    return a;
}

bool registroProductosEquals(RegistroProductos a, RegistroProductos b)
{
    if (!productoEquals(a.prod, b.prod))
        return false;
    if (a.contador != b.contador)
        return false;
    return true;
}

string registroRubroToString(RegistroRubro x)
{
    char sep = 6;
    string sRubro = rubroToString(x.rubro);
    string sAhorro = to_string(x.ahorro);
    return sRubro + sep + sAhorro;
}

RegistroRubro registroRubroFromString(string s)
{
    char sep = 6;
    RegistroRubro x;
    string t0 = getTokenAt(s, sep, 0);
    x.rubro = rubroFromString(t0);
    string t1 = getTokenAt(s, sep, 1);
    x.ahorro = stod(t1);
    return x;
}

string registroRubroToDebug(RegistroRubro x)
{
    stringstream sout;
    sout << "[";
    sout << rubroToDebug(x.rubro);
    sout << ",";
    sout << x.ahorro;
    sout << "]";
    return sout.str();
}

RegistroRubro registroRubro(Rubro rubro, double ahorro)
{
    RegistroRubro b;
    b.rubro = rubro;
    b.ahorro = ahorro;
    return b;
}

bool registroRubroEquals(RegistroRubro a, RegistroRubro b)
{
    if (!rubroEquals(a.rubro, b.rubro))
        return false;
    if (a.ahorro != b.ahorro)
        return false;
    return true;
}

#endif
