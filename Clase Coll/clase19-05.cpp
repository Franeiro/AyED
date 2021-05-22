#include <stdlib.h>

struct Fraccion
{
    int d, n;
};

Fraccion fraccion(int n, int d)
{
    Fraccion f = {n, d};

    return f;

    /*
    es lo mismo poner solamente return {n,d};
    */
}

string fraccionToString(Fraccion f)
{
    return intToString(f.n) + "/" + intToString(f.d);
}

int main()
{
    Fraccion p = fraccion(2, 5);

    cout << fraccionToString(p) << endl;

    return 0;
}