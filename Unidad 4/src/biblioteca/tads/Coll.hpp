#ifndef _TCOLL_T_
#define _TCOLL_T_

#include <iostream>
#include "../funciones/strings.hpp"

using namespace std;

template <typename T>
struct Coll
{

   string s;
   char sep;
   int p;
};

template <typename T>
Coll<T> coll(char sep)
{

   Coll<T> c;
   c.s = "";
   c.sep = '|';

   return c;
}

template <typename T>
Coll<T> coll()
{

   Coll<T> c;
   c.s = "";
   c.p = 0;
   c.sep = '|';
   return c;
}

template <typename T>
int collSize(Coll<T> c)
{
   return tokenCount(c.s, c.sep);
}

template <typename T>
void collRemoveAll(Coll<T> &c)
{
   c.s = "";
}

template <typename T>
void collRemoveAt(Coll<T> &c, int p)
{
   removeTokenAt(c.s, c.sep, p);
}

template <typename T>
int collAdd(Coll<T> &c, T t, string tToString(T))
{
   addToken(c.s, c.sep, tToString(t));
   return collSize(c) - 1;
}

template <typename T>
void collSetAt(Coll<T> &c, T t, int p, string tToString(T))
{
   setTokenAt(c.s, c.sep, tToString(t), p);
   removeTokenAt(c.s, c.sep, p + 1);
}

template <typename T>
T collGetAt(Coll<T> c, int p, T tFromString(string))
{

   return tFromString(getTokenAt(c.s, c.sep, p));
}

// CREO FUNCIONES cmpTK para comparar datos

int cmpIntInt(int a, int b)
{
   return a - b;
}

int cmpStringString(string a, string b)
{
   return a < b ? -1 : a > b ? 1
                             : 0;
}

template <typename T, typename K>
int collFind(Coll<T> c, K k, int cmpTK(T, K), T tFromString(string))
{
   int i = 0;
   bool encontre = false;

   while (i < collSize<T>(c) && !encontre)
   {
      T t = collGetAt<T>(c, i, tFromString);

      if (cmpTK(t, k) == 0)
      {
         encontre = true;
      }
      else
      {
         i++;
      }
   }

   return encontre ? i : -1;
}

template <typename T>
void collSort(Coll<T> &c, int cmpTT(T, T), T tFromString(string), string tToString(T))
{

   bool ordenado = false;
   while (!ordenado)
   {

      ordenado = true;
      for (int i = 0; i <= collSize<T>(c) - 1; i++)
      {

         T e1 = collGetAt<T>(c, i, tFromString);
         T e2 = collGetAt<T>(c, i + 1, tFromString);

         if (cmpTT(e1, e2) < 0)
         {

            collSetAt<T>(c, e1, i + 1, tToString);
            collSetAt<T>(c, e2, i, tToString);

            ordenado = false;
         }
      }
   }
}

template <typename T>
bool collHasNext(Coll<T> &c)
{

   if (c.p == collSize(c))
   {
      return false;
   }
   return true;
}

template <typename T>
T collNext(Coll<T> &c, T tFromString(string))
{

   T t;
   t = tFromString(getTokenAt(c.s, c.sep, c.p));
   c.p = c.p + 1;

   return t;
}

template <typename T>
void collReset(Coll<T> &c)
{
   c.p = 0;
}

template <typename T>
string collToString(Coll<T> c)
{
   return c.sep + c.s;
}

template <typename T>
Coll<T> collFromString(string s)
{
   Coll<T> x;
   x.sep = s[0];
   x.s = substring(s, 1);

   return x;
}

#endif
