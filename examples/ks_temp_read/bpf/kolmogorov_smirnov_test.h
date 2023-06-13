#ifndef KS_TEST
#define KS_TEST

#include "bpf/shared.h"

#define RANGE 1024
#define STEP 64
#define STEPS 16

typedef struct KS_Test_State{
    __bpf_shared_ptr(int32_t *, expectedFunction);
    __bpf_shared_ptr(int32_t *, empiricalFunction);
    uint32_t value;
    uint32_t result;
} KS_Test_State;

typedef struct {
    __bpf_shared_ptr(KS_Test_State *, kolmogorov_ctx);
} kolmogorov_ctx_t;

uint32_t delta_kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx);

void create_function(void);

float toTemperature(uint32_t value);

void printList(int32_t* arr1, int32_t* arr2);

int32_t read_nrf52_temp(void);

int32_t expectedFunction[16];
int32_t empiricalFunction[16];

#endif
