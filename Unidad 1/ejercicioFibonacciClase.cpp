
#include <iostream>
#include "timerEjercicioClase.cpp"

using namespace std;

// 1 2 3 4 5 6  7  8  9
// 1 1 2 3 5 8 13 21 34...
double fibIter(int n)
{
    double t1 = 1;
    double t2 = 1;
    double t3 = 1;

    int i = 2;
    while (i < n)
    {
        t3 = t1 + t2;
        t1 = t2;
        t2 = t3;

        i = i + 1;
    }

    return t3;
}

// 1 2 3 4 5 6  7  8  9    10  11
// 1 1 2 3 5 8 13 21 34    55  89
double fibRecur(int n)
{
    double f = 1;
    if (n > 2)
    {
        f = fibRecur(n - 1) + fibRecur(n - 2);
    }

    return f;
}

int main()
{
    cout << "Ingrese un valor: " << endl;
    int n;
    cin >> n;

    Timer t = timer();

    timerStart(t);
    double f = fibRecur(n);
    timerStop(t);

    cout << f << endl;

    double et = timerElapsedTime(t);
    cout << "Demora: " << et << endl;

    return 0;
}

/*

int main()
{
    Timer t = timer();

    int i =40;

    while(i<=50)
    {
        timerStar(t);
        fibRecurs(i);
        timerStop(t);

        cout << i << ""; << timerElapsedTime(t)<< endl;
    }
}

*/