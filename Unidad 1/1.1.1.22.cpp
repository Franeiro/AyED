#include <iostream>
using namespace std;

int main()
{
    int n, valor, i;

    cout << "Indique cuantos multiplos de 5 pero no de 3 quiere imprimir: ";
    cin >> n;

    for (i = 1; i <= n; i++)
    {
        valor = 5 * i;

        if (valor % 3 == 0)
        {
            n = n + 1;
        }

        else
        {
            cout << valor << endl;
        }
    }
}