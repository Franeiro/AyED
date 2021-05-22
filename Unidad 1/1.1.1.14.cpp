#include <iostream>
using namespace std;

int main()
{
    int a, i, b;

    b = 0;

    cout << "Ingrese un valor entero: ";
    cin >> a;

    for (i = 1; i <= a; i++)
    {
        if (a % i == 0)
            b++;
    }

    if (b == 2)
    {
        printf("El numero es primo");
    }

    else
    {
        printf("El numero no es primo");
    }
}
