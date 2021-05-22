#include <iostream>
using namespace std;

int main()
{
    int cant, n, d, es_primo;

    cout << "Ingrese la cantidad de numeros primos que quiere imprimir: ";
    cin >> cant;

    n = 2;
    while (cant > 0)
    {

        es_primo = 1;
        for (d = 2; d < n; ++d)
        {
            if (n % d == 0)
            {
                es_primo = 0;
                break;
            }
        }

        if (es_primo)
        {
            cout << n << endl;
            cant--;
        }
        n++;
    }
}