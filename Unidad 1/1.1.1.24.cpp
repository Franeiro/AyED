#include <iostream>
using namespace std;

int main()
{
    int cero, i, a, aux;

    cout << "Presione  0  para generar 100 numeros aleatorios positivos (0 - 523). " << endl;
    cout << "Presione  1  para generar 100 numeros aleatorios mayores a -10 (-10 - 523). " << endl;
    cout << "Presione  2  para generar 100 numeros aleatorios. (-250 - 523) " << endl
         << endl;
    cout << "Ingrese el numero de operacion que quiere realizar:  " << endl;

    cin >> cero;

    aux = 0;

    if (cero == 0)
    {
        for (i = 1; i <= 100; i++)
        {
            a = rand() % 523; // genero un valor aleatorio entre 0 y 99

            if (a > aux) // comparo con aux
            {
                aux = a;
            }

            cout << a << endl;
        }

        cout << " El valor mas alto generado fue el numero " << aux << endl;
    }

    if (cero == 1)
    {
        for (i = 1; i <= 100; i++)
        {
            a = rand() % (523) + -10; // genero un valor aleatorio entre 0 y 99

            if (a > aux) // comparo con aux
            {
                aux = a;
            }

            cout << a << endl;
        }

        cout << " El valor mas alto generado fue el numero " << aux << endl;
    }

    if (cero == 2)
    {
        for (i = 1; i <= 100; i++)
        {
            a = rand() % (523) + -250; // genero un valor aleatorio entre 0 y 99

            if (a > aux) // comparo con aux
            {
                aux = a;
            }

            cout << a << endl;
        }

        cout << " El valor mas alto generado fue el numero " << aux << endl;
    }

    else
    {
        cout << " Usted ha ingresado un valor no permitido. Se finalizara el programa.";
    }
}