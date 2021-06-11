#ifndef _TFILES_T_
#define _TFILES_T_

#include <iostream>
#include <stdio.h>

template <typename T>
void write(FILE *f, T t)
{
   fwrite(&t, sizeof(T), 1, f);
}

template <typename T>
T read(FILE *f)
{
   T t;
   fread(&t, sizeof(T), 1, f);
   return t;
}

template <typename T>
void seek(FILE *f, int n)
{
   fseek(f, n);
}

template <typename T>
int fileSize(FILE *f)
{
   int actual = ftell(f);
   fseek(f, 0, SEEK_END);

   int ultimo = ftell(f);

   fseek(f, actual, SEEK_SET);
   return ultimo;
}

template <typename T>
int filePos(FILE *f)
{
   return ftell(f);
}

#endif
