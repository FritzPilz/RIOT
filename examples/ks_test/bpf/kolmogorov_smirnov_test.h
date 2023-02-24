#ifndef KS_TEST
#define KS_TEST

#include "bpf/shared.h"

#define RANGE 97.0
#define STEP 5.0
#define STEPS 20
#define SIZE1 500
#define SIZE2 250

typedef struct KS_Test_Results{
	uint32_t max_diff;
	uint32_t p_value;
} KS_Test_Results;

typedef struct KS_Test_Setup{
    __bpf_shared_ptr(uint32_t *, arr1);
    __bpf_shared_ptr(uint32_t *, arr2);
    uint32_t len1;
    uint32_t len2;
    uint32_t significance;
} KS_Test_Setup;

typedef struct KS_Context{
    __bpf_shared_ptr(KS_Test_Setup*, setup);
    __bpf_shared_ptr(KS_Test_Results*, result);
} KS_Context __attribute__((aligned(64)));

typedef struct {
    __bpf_shared_ptr(KS_Context *, kolmogorov_ctx);
} kolmogorov_ctx_t;

KS_Test_Results* kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx);

uint32_t* create_sample(uint32_t* sample, uint32_t size, uint32_t seed);

uint32_t* insertionSort(uint32_t* arr, uint32_t size);

#endif