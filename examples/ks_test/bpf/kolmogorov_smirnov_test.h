#ifndef KS_TEST
#define KS_TEST

#define RANGE 97.0
#define STEP 5.0
#define STEPS 20
#define SIZE1 500
#define SIZE2 250

typedef struct KS_Test_Results{
	int max_diff;
	int p_value;
} KS_Test_Results;

typedef struct KS_Test_Setup{
    int* arr1;
    int len1;
    int* arr2;
    int len2;
    int significance;
} KS_Test_Setup;

typedef struct KS_Context{
    KS_Test_Setup* setup;
    KS_Test_Results* result;
} KS_Context;

KS_Test_Results* kolmogorov_smirnov_test(KS_Context* ctx);

int* create_sample(int* sample, int size, int seed);

int* insertionSort(int* arr, int size);

int absolut(int i);

#endif