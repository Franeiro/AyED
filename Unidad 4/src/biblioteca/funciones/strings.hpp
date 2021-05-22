#ifndef _TSTRINGS_T_
#define _TSTRINGS_T_

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;

int length(string s)
{
   int i;

   for (i = 0; s[i] != '\0'; i++)
   {
   }

   return i;
}

int charCount(string s, char c) // REVISAR no anda
{
   int i, veces;

   veces = 0;
   for (i = 0; i < length(s); i++)
   {
      if (s[i] == c)
      {
         veces++;
      }
   }
   return veces;
}

string substring(string s, int d, int h)
{
   int i;

   for (i = 0; s[i] != '\0'; i++)
   {
      if (i >= d && i < h)
      {
         cout << s[i];
      }
   }

   return "";
}

string substring(string s, int d) // ok
{
   int i;

   for (i = 0; s[i] != '\0'; i++)
   {
      if (i >= d)
      {
         cout << s[i];
      }
   }
   return "";
}

int indexOf(string s, char c) // ok
{
   int i;

   for (i = 0; s[i] != '\0'; i++)
   {
      if (s[i] == c)
      {
         return i;
      }
   }

   return -1;
}

int indexOf(string s, char c, int offSet) // ok
{
   int i;

   for (i = 0; s[i] != '\0'; i++)
   {
      if (i > offSet && s[i] == c)
      {
         return i;
      }
   }

   return 0;
}

int indexOf(string s, string toSearch) // ok   //REVISAR  no anda
{
   int i, j, aparece;

   j = 0;

   for (i = 0; toSearch[j] == '\0'; i++)
   {
      if (toSearch[j] == '\0')
      {
         break;
      }
      if (s[i] == toSearch[j])
      {
         aparece++;
      }

      j++;
   }

   return i - aparece;
}

int indexOf(string s, string toSearch, int offset) // ok
{
   return 0;
}

int lastIndexOf(string s, char c)
{
   return 0;
}

int indexOfN(string s, char c, int n)
{
   return 0;
}

int charToInt(char c)
{
   int numero;

   numero = c - 48;

   return numero;
}

char intToChar(int i)
{

   char caracter;

   caracter = (i + 48);

   return caracter;
}

int potencia(int x, int y) // CREO FUNCION PARA CALCULAR POTENCIAS
{
   if (y == 0)
   {
      return 1;
   }
   else
   {

      if (int(y % 2) == 0)
      {
         return (potencia(x, int(y / 2)) * potencia(x, int(y / 2)));
      }

      else
      {
         return (x * potencia(x, int(y / 2)) * potencia(x, int(y / 2)));
      }
   }
}

int getDigit(int n, int i)
{
   int p = potencia(10, i);
   int q = n / p;

   return q % 10;
}

int digitCount(int n)
{

   int a = 0, t;

   for (t = 0; n / (long)potencia(10, t) >= 1; t++)
   {
      a++;
   }

   return a;
}

string intToString(int i)
{
   int n = digitCount(i);
   string parse = "";

   for (int j = 0; j < n; j++)
   {
      int f = (n - j) - 1;

      int digito = getDigit(i, f);
      char c = digito + 48;
      parse += c;
   }

   return parse;
}

int stringToInt(string s, int b) // ok
{
   int parseInt, j;
   int longitud = length(s) - 1;

   char i = 0;

   for (j = longitud; j >= 0; j--)
   {
      int x;

      if (s[j] >= '0' and s[j] <= '9')
      {
         x = '0';
      }

      else
      {
         x = 'A' - 10;
      }

      parseInt = parseInt + (s[j] - x) * potencia(b, i);
      i++;
   }

   return parseInt;
}

int stringToInt(string s) // ok
{
   int parseInt, j;
   int longitud = length(s) - 1;

   char i = 0;

   for (j = longitud; j >= 0; j--)
   {

      parseInt = parseInt + (s[j] - '0') * potencia(10, i);
      i++;
   }

   return parseInt;
}

string charToString(char c)
{
   string a;
   a += c;

   return a;
}

char stringToChar(string s)
{
   char a;

   a = s[0];
   return a;
}

string stringToString(string s)
{
   string a;
   a = s;
   return a;
}

string doubleToString(double d) // saltear
{
   char x[100];
   sprintf(x, "%f", d); // esto es de lenguaje C, no se usa

   string ret = x;

   return ret;
}

double stringToDouble(string s) // No se hace
{
   return 1.1;
}

bool isEmpty(string s)
{
   bool a;
   string verdad;

   a = s == "";

   if (a == 0)
   {
      verdad = "false";
   }
   else
   {
      verdad = "true";
   }

   return a;
}

bool startsWith(string s, string x)
{
   int coincidencia;
   for (int i = 0; i <= length(x); i++)
   {
      if (x[i] == s[i])
      {
         coincidencia++;
      }
   }

   if (coincidencia == length(x))
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool endsWith(string s, string x)
{
   int coincidencia;
   int posX = length(x);
   for (int i = length(s); posX >= 0; i--)
   {

      if (x[posX] == s[i])
      {
         coincidencia++;
      }

      posX--;
   }

   if (coincidencia - 1 == length(x))
   {
      return true;
   }
   else
   {
      return false;
   }
}

bool contains(string s, char c)
{
   int coincidencia;
   for (int i = 0; i <= length(s); i++)
   {
      if (s[i] == c)
      {
         coincidencia = 1;
      }
   }

   if (coincidencia == 1)
   {
      return true;
   }
   else
   {
      return false;
   }
}

string replace(string s, char oldChar, char newChar)
{

   for (int i = 0; i <= length(s); i++)
   {
      if (s[i] == oldChar)
      {
         s[i] = newChar;
      }
   }

   return s;
}

string insertAt(string s, int pos, char c) // NO SALE
{

   char primera[length(s)];
   char segunda[length(s) + 1];
   int j = 0;

   for (int i = 0; i < length(s) + 1; i++)
   {
      primera[i] = s[i];
      if (i < pos)
      {
         segunda[j] = primera[i];
         j++;
      }

      if (i == pos)
      {
         segunda[j] = c;
         j++;
      }

      if (i > pos)
      {
         segunda[j] = primera[i - 1];
         j++;
      }
   }
   segunda[j] = '\0';

   s = segunda;

   return s;

   /* SOLUCION 

   string insertAt(string s, int pos, char c)
{
   string r = substring (s,0, pos)+ c + substring(s,pos) ;
   return r;
}
   


   */
}

string removeAt(string s, int pos)
{
   char primera[length(s)];
   char segunda[length(s) + 1];
   int j = 0;

   for (int i = 0; i < length(s); i++)
   {
      primera[i] = s[i];
      if (i < pos || i > pos)
      {
         segunda[j] = primera[i];
         j++;
      }

      if (i == pos)
      {

         segunda[j + 1] = primera[i];
      }
   }
   segunda[j] = '\0';

   s = segunda;

   return s;
}

string ltrim(string s)
{
   int largo = length(s);
   int i = 0;

   while (s[i] == ' ')
   {
      i++;
   }

   return substring(s, i, largo);
   /*  Profe

    int largo = length(s);
   int i = 0;

   while (s[i] != ' ')
   {
      i++;
   }

   return substring(s, i, largo);
   

   */
}

string rtrim(string s)
{
   int largo = length(s) - 1;

   while (s[largo] == ' ')
   {
      largo--;
   }

   return substring(s, 0, largo + 1);
}

string trim(string s) // no anda, deberia andar con ltrim(rtrim(s))
{
   int largo = length(s) - 1;

   while (s[largo] == ' ')
   {
      largo--;
   }

   return ltrim(ltrim(substring(s, 0, largo + 1)));
}

string replicate(char c, int n)
{

   string a;
   for (int i = 0; i <= n; i++)
   {
      a += c;
   }

   return a;
}

string spaces(int n)
{
   string a;
   for (int i = 0; i <= n; i++)
   {
      a += ' ';
   }

   return a;
}

string lpad(string s, int n, char c)
{
   string a;
   for (int i = 0; i <= n; i++)
   {

      a += c;
   }

   a += s;

   return a;
}

string rpad(string s, int n, char c)
{
   string a;
   a += s;
   for (int i = 0; i <= n; i++)
   {

      a += c;
   }

   return a;
}

string cpad(string s, int n, char c)
{
   string a;
   int espacio = (n - length(s));

   for (int i = 0; i <= espacio; i++)
   {
      if (i < (espacio / 2))
      {
         a += c;
      }
      if (i == (espacio / 2))
      {
         a += s;
      }
      if (i > (espacio / 2))
      {
         a += c;
      }
   }

   return a;
}

bool isDigit(char c)
{

   if (c >= 48 && c <= 57)
   {
      return true;
   }

   else
   {
      return false;
   }
}

bool isLetter(char c)
{
   if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
   {
      return true;
   }

   else
   {
      return false;
   }
}

bool isUpperCase(char c)
{
   if ((c >= 65 && c <= 90))
   {
      return true;
   }

   else
   {
      return false;
   }
}

bool isLowerCase(char c)
{
   if ((c >= 97 && c <= 122))
   {
      return true;
   }

   else
   {
      return false;
   }
}

char toUpperCase(char c)
{

   if (c >= 97 && c <= 122)
   {
      c -= 32;
   }

   else
   {
      return c;
   }

   return c;
}

char toLowerCase(char c)
{
   if (c >= 65 && c <= 90)
   {

      c += 32;
   }
   else
   {
      return c;
   }
   return c;
}

string toUpperCase(string s)
{
   for (int i = 0; i <= length(s); i++)
   {
      if (s[i] >= 97 && s[i] <= 122)
      {
         s[i] -= 32;
      }

      else
      {
         s[i] = s[i];
      }
   }

   return s;
}

string toLowerCase(string s)
{
   for (int i = 0; i <= length(s); i++)
   {
      if (s[i] >= 65 && s[i] <= 90)
      {
         s[i] += 32;
      }

      else
      {
         s[i] = s[i];
      }
   }

   return s;
}

#endif
