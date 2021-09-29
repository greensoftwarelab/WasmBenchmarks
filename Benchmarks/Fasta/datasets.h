#ifdef SMALL_DATASET
#define INPUT 6250000
#endif
#ifdef LARGE_DATASET
#define INPUT 25000000
#endif

#ifndef SMALL_DATASET
  #ifndef LARGE_DATASET
    #ifndef MEDIUM_DATASET
      #define MEDIUM_DATASET
    #endif
  #endif
#endif

#ifdef MEDIUM_DATASET
#define INPUT 12500000
#endif