#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
   FILE *fp;
   int small = 1000000;
   int medium = 2000000;
   int large = 4000000;
   
   srand(time(NULL));  
   fp = fopen("datasets.h", "w+");

   fprintf(fp, "#ifdef SMALL_DATASET\n#define INPUT {");

   for (int i = 0; i < 5; i++)
   {
       int r = (rand()%small)+1;     
       fprintf(fp,"%d,",r);
   }
   fprintf(fp,"}\n#endif\n#ifdef LARGE_DATASET\n#define INPUT {");
   
   for (int i = 0; i < 5; i++)
   {
       int r = (rand()%large)+1;     
       fprintf(fp,"%d,",r);
   }
   fprintf(fp,"}\n#endif\n\n#ifndef SMALL_DATASET\n\t#ifndef LARGE_DATASET\n\t\t#ifndef MEDIUM_DATASET\n\t\t\t#define MEDIUM_DATASET\n\t\t#endif\n\t#endif\n#endif\n\n#ifdef MEDIUM_DATASET\n#define INPUT {");

   for (int i = 0; i < 5; i++)
   {
       int r = (rand()%medium)+1;   
       fprintf(fp,"%d,",r);
   }
   fprintf(fp,"}\n#endif\n");
   fclose(fp);
   return 0;
}