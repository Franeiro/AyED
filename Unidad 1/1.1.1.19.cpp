#include <iostream>
using namespace std;

int main()
{

    int a, f1 = 0, f2 = 0, f3 = 0, f4 = 0;

    a = 1;

    while (a >= 0)
    {
        cout << "Ingrese un numero entero. Si quiere finalizar la carga de datos, ignrese un valor negativo: ";
        cin >> a;

        if (a <= 12 && a != 0)
        {
            f1++;
        }

        if (a > 12 && a <= 24)
        {
            f2++;
        }

        if (a > 24 && a <= 36)
        {
            f3++;
        }

        if (a == 0)
        {
            f4++;
        }
    }

    cout << "La cantidad de valores ingresados iguales a 0 son: " << f4 << endl;
    cout << "La cantidad de valores ingresados menores a 12 son: " << f1 << endl;
    cout << "La cantidad de valores ingresados entre 12 y 24 son: " << f2 << endl;
    cout << "La cantidad de valores ingresados entre 24 y 36 son: " << f3 << endl;

    return 0;
}