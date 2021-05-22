#include <iostream>
using namespace std;

int main()
{
    int a, i, fact, num;

    cout << "Ingrese la cantidad de numeros factoriales que quiere imprimir: ";
    cin >> num;

    fact = 1;

    for (i = 1; i <= num; i++)
    {

        a = i;

        fact = i * fact;

        cout << fact << endl;
    }

    return 0;
}