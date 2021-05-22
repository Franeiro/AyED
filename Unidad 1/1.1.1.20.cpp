#include <iostream>
using namespace std;

int main()
{

    int a, f1 = 0, f2 = 0, f3 = 0, f4 = 0, total;
    float porcentajeNegativos, porcentajePares, numerador = 0, promedioPositivos = 0;

    a = 1;

    while (a != 0)
    {
        cout << "Ingrese un numero entero. Si quiere finalizar la carga de datos, ingrese  0  : ";
        cin >> a;

        if (a > 0)
        {
            f1++;

            numerador = numerador + a;

            promedioPositivos = numerador / f1;
        }

        if (a < 0)
        {
            f2++;
        }

        if (a % 2 == 0 && a != 0) // El nro es par
        {
            f3++;
        }

        total = f1 + f2;
        porcentajeNegativos = float(f2) / total;

        porcentajePares = float(f3) / total;
    }

    // Porcentaje de negativos = negativos / total nros ingresados

    cout << "La cantidad de valores positivos son : " << f1 << endl;
    cout << "La cantidad de valores negativos: " << f2 << endl;
    cout << "El porcentaje de valores pares entre el total es: " << porcentajePares << endl;
    cout << "El promedio de los valores positivos es " << promedioPositivos << endl;
    cout << "El porcentaje de valores negativos entre el total es: " << porcentajeNegativos << endl
         << endl;

    cout << f1 << endl;
    cout << f2 << endl;
    cout << f3 << endl;

    return 0;
}