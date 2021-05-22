#include <iostream>
using namespace std;

int main()
{
    int num, i, a, fact;

    cout << "Ingrese el numero al que le quiera calcular el factorial: ";
    cin >> num;

    fact = 1;

    for (i = 1; i <= num; i++)
    {

        a = i;

        fact = i * fact;
    }

    cout << fact;

    return 0;
}
