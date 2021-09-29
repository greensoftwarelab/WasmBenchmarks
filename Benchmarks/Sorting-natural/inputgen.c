#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main() {
   FILE *fp;
   int small = 50000;
   int medium = 100000;
   int large = 200000;
   
   srand(time(NULL));   // Initialization, should only be called once.
   fp = fopen("datasets.h", "w+");

   fprintf(fp, "#ifdef SMALL_DATASET\n#define INPUT {");

   for (int i = 0; i < small; i++)
   {
       int r = rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
       fprintf(fp,"L\"%d\",",r);
   }
   fprintf(fp,"}\n#endif\n#ifdef LARGE_DATASET\n#define INPUT {");
   
   for (int i = 0; i < large; i++)
   {
       int r = rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
       fprintf(fp,"L\"%d\",",r);
   }
   fprintf(fp,"}\n#endif\n\n#ifndef SMALL_DATASET\n\t#ifndef LARGE_DATASET\n\t\t#ifndef MEDIUM_DATASET\n\t\t\t#define MEDIUM_DATASET\n\t\t#endif\n\t#endif\n#endif\n\n#ifdef MEDIUM_DATASET\n#define INPUT {");

   for (int i = 0; i < medium; i++)
   {
       int r = rand();      // Returns a pseudo-random integer between 0 and RAND_MAX.
       fprintf(fp,"L\"%d\",",r);
   }
   fprintf(fp,"}\n#endif\n");
   fclose(fp);
   return 0;
}