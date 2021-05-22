#include <iostream>
using namespace std;

int main()
{
    int a, i, fib, fib_1;

    cout << "Ingrese el n-esimo termino de la sucesion de Fibonnacci que quiere imprimir: ";
    cin >> a;

    /* fib_1 = 1;

    cout << fib_1 << endl; */

    a = a - 1;
    fib = 1;
    fib_1 = 1;

    for (i = 2; i <= a; i++)
    {
        fib = fib + fib_1;
        fib_1 = fib - fib_1;
    }

    cout << fib << endl;
}

/*
    1  ---  1 
    2 ---- 1+0  1
    3 ---- 1+1  2
    4 ---- 2+1  3
    5 ---- 3+2  5
    6 ---- 5+3  8
*/

/*

typedef unsigned long long Millies

struct Timer
{

}

Timer timer ()
{
    return {};
}

void timerStart(timer& t)
{

}

void timerStop(timer& t)
{
    
}

unsigned long long timerElapsedTime(timer& t)
{
    
}




*/