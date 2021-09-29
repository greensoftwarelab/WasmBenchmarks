#ifdef SMALL_DATASET
#define INPUT 10
#endif
#ifdef LARGE_DATASET
#define INPUT 13
#endif

#ifndef SMALL_DATASET
  #ifndef LARGE_DATASET
    #ifndef MEDIUM_DATASET
      #define MEDIUM_DATASET
    #endif
  #endif
#endif

#ifdef MEDIUM_DATASET
#define INPUT 12
#endif
