#ifndef _TTOKENS_T_
#define _TTOKENS_T_

#include <iostream>
#include <stdio.h>
#include "strings.hpp"
using namespace std;

int tokenCount(string s, char sep)
{
   int veces = 0;
   int lleno = 0;

   if (!isEmpty(s))
   {

      for (int i = 0; i <= length(s); i++)
      {

         if (s[i] == sep)
         {
            veces++;
         }
      }

      lleno++;
   }

   return veces + lleno;
}

void addToken(string &s, char sep, string t)
{
   if (!isEmpty(s))
   {
      s += sep + t;
   }
   else
   {
      s += t;
   }
}

string getTokenAt(string s, char sep, int i)
{
   int veces = 0, desde = 0, hasta = 0;
   for (int j = 0; j <= length(s); j++)
   {

      if (s[j] == sep)
      {
         veces++;
      }

      if (veces == i)
      {
         if (i == 0)
         {
            desde = j;
         }
         else
         {
            desde = j + 1;
         }

         veces++;
      }

      if (veces == i + 1)
      {
         hasta = j + 1;
      }
   }

   return substring(s, desde, hasta);
}

void removeTokenAt(string &s, char sep, int i)
{
   int veces = 0, desde = 0, hasta = 0;
   for (int j = 0; j <= length(s); j++)
   {

      if (s[j] == sep)
      {
         veces++;
      }

      if (veces == i)
      {
         if (i == 0)
         {
            desde = j;
         }
         else
         {
            desde = j + 1;
         }

         veces++;
      }

      if (veces == i + 1)
      {
         hasta = j + 1;
      }
   }
   s = substring(s, 0, desde) + substring(s, hasta + 1);
}

void setTokenAt(string &s, char sep, string t, int i)
{
   int veces = 0, desde = 0;
   for (int j = 0; j <= length(s); j++)
   {

      if (s[j] == sep)
      {
         veces++;
      }

      if (veces == i)
      {
         if (i == 0)
         {
            desde = j;
         }
         else
         {
            desde = j + 1;
         }

         veces++;
      }
   }
   s = substring(s, 0, desde) + t + sep + substring(s, desde);
}

int findToken(string s, char sep, string t)
{
   int coincide = 0;
   for (int j = 0; j <= length(s); j++)
   {
      string a = getTokenAt(s, sep, j);

      for (int n = 0; n <= length(t); n++)
      {
         if (a[n] == t[n])
         {
            coincide++;
         }

         if (coincide == length(t) && coincide == length(a))
         {
            return j;
            break;
         }
      }
   }

   return -1;
}

int valorNumerico(string s)
{
   int valor, sumatoria = 0;
   int sumatoria2 = 0;

   for (int i = 0; i < length(s); i++)
   {

      string a = charToString(s[i]);

      if (stringToInt(a) <= 78)
      {
         valor = stringToInt(a) - 16;
      }

      if (valor >= 15)
      {
         if (stringToInt(a) != 165)
         {
            valor += 1;
         }
         else
         {
            valor = 15;
         }
      }

      sumatoria += valor;
   }

   while (sumatoria > 9)
   {
      string digitos = intToString(sumatoria);

      sumatoria2 = 0;

      for (int k = 0; k < length(digitos); k++)
      {
         sumatoria2 += charToInt(digitos[k]);
      }

      sumatoria = sumatoria2;
   }

   return sumatoria;
}

int primerosNNumerosD(int n, int m, int d)
{
   int veces = 0;
   string numeroEnString;
   for (int i = 0; veces != n; i++)
   {
      numeroEnString = intToString(i);
      if (charCount(numeroEnString, intToChar(d)) == m)
      {
         veces++;
         cout << i << endl;
      }
   }
   return 0;
}

#endif
