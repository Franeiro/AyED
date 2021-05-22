#include <iostream>
using namespace std;

int main()
{
    string nombre[3];
    int fechaNacimiento[3];
    int i, j, auxAnio, anio, mes, dia, anioActual, mesActual, diaActual, aniosPersona, masVieja, mesesPersona, diaPersona;

    auxAnio = 0;

    cout << "Ingrese el año actual: " << endl;
    cin >> anioActual;
    cout << "Ingrese el mes actual: " << endl;
    cin >> mesActual;
    cout << "Ingrese el dia actual: " << endl;
    cin >> diaActual;

    for (i = 0; i <= 3; i++)
    {

        cout << "Ingrese Nombre de la persona " << i + 1 << ":" << endl;
        cin >> nombre[i];

        for (j = 0; j <= 3; j++)
        {
            cout << "Ingrese fecha de nacimiento de la persona " << i + 1 << "  en el formato AAAAMMDD:" << endl;
            cin >> fechaNacimiento[i];
        }

        dia = fechaNacimiento[i] % 100;
        mes = (fechaNacimiento[i] / 100) % 100;
        anio = (fechaNacimiento[i] / 100) / 100;

        aniosPersona = anioActual - anio;
        mesesPersona = mesActual - mes;

        if (aniosPersona > auxAnio)
        {
            nombre[i] = masVieja;
        }
    }

    cout << masVieja;
}

/*

CODIGO PABLO 

*/
