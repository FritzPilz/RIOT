#ifndef KS_TEST
#define KS_TEST

#define RANGE 1024
#define STEP 64
#define STEPS 16

uint32_t delta_kolmogorov_smirnov_test(int32_t value);

void create_function(void);

float toTemperature(uint32_t value);

void printList(int32_t* arr1, int32_t* arr2);

int32_t expectedFunction[16];
int32_t empiricalFunction[16];

#endif
