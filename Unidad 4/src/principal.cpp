
#ifndef _MAIN
#define _MAIN

#include <iostream>
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/funciones/tokens.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/Array.hpp"
#include "biblioteca/tads/Map.hpp"
#include "biblioteca/tads/List.hpp"
#include "biblioteca/tads/Stack.hpp"
#include "biblioteca/tads/Queue.hpp"
#include "biblioteca/tads/Coll.hpp"
using namespace std;

int main()
{

   FILE *arch;

   arch = fopen("Demo.DAT", "w+b");

   write<short>(arch, 26598);
   write<short>(arch, 6789);
   write<short>(arch, 0000);

   fclose(arch);

   arch = fopen("Demo.DAT", "r+b");
   short s = read<short>(arch);

   while (!feof(arch))

   {
      cout << s << endl;
      read<short>(arch);
   }

   fclose(arch);

   return 0;
}

#endif
