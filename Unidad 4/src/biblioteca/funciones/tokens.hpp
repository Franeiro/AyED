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
   int veces = 0;
   int k = 0, f = 0;
   string aux1, aux2;
   for (k = 0; veces < (i + 1); k++)
   {

      aux1 += s[k];
      if (s[k + 1] == sep || s[k + 1] == '\0')
      {
         veces++;
         if (veces == i + 1)
         {

            break;
         }

         aux1 = aux2;
      }
   }

   while (aux1[f] == sep)
   {
      f++;
   }

   return substring(aux1, f, length(aux1));

   return aux1;
}

void removeTokenAt(string &s, char sep, int i) // Funciona una sola vez y con i < 0   :((((
{
   string aux, aux2;
   int veces = 0;
   for (int j = 0; j <= length(s); j++)
   {
      aux += s[j];

      if (s[j] == sep || s[j] == '\0')
      {
         veces++;
      }

      if (veces == i)
      {
         if (i == 0)
         {
            /*
            while (aux[j] == sep)
            {
               f++;
            }
            s = substring(s, j, f + 1);
            */
         }
         aux[j] = aux2[0];
      }
   }

   s = aux;
}

void setTokenAt(string &s, char sep, string t, int i) // revisar Add token y/o getToken
{

   string x = "";
   for (int j = 0; j < tokenCount(s, sep); j++)
   {

      if (j != i)
      {
         string w = getTokenAt(s, sep, j);

         addToken(x, sep, w);
      }

      else
      {
         addToken(x, sep, t);
      }
   }

   s = x;

   /*
   FORMA DIFICL.

   int p1,p2; 
   char sep1;
   char sep2;

   if(i==0)
   {
      p1=0;
      sep1="";
     
   }

   else
   {
      p1 = indexOfN(s,sep,i);
      sep1= charToString(sep);
   }

  
   string s1 = substring(s, 0, p1);

   sep2 = charToString(sep);
   p2 = indexOfN(s,sep,i+1);
   string s2 = substring(s, p2+1),

   string x = sep1 + s1 + t + sep2 + s2;

   s=x;

   
  */
}

int findToken(string s, char sep, string t) // revisar para ultimo token y xq hay q restar 2;
{
   string aux;
   int a = 0;
   for (int i = 0; i <= length(s); i++)
   {
      aux += s[i];
      int j = 0;
      if (s[i] == t[j])
      {
         int k = i;
         while (s[i] == t[j] && j < length(t))
         {
            j++;
            i++;
            aux += s[i];
         }
         if (j == length(t))
         {
            a = tokenCount(aux, sep) - 2;
            break;
         }

         else
         {
            i = k;
         }
      }
   }

   return a;
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
