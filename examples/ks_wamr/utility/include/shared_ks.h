#ifndef UTILITY_KS
#define UTILITY_KS

#include <stdint.h>

typedef struct KS_Test_State{
    int32_t* expected_function;
    int32_t* empirical_function;
    uint32_t value;
    uint32_t result;
    uint32_t value_range;
    uint32_t values;
} KS_Test_State;

typedef struct {
    KS_Test_State* kolmogorov_ctx;
} kolmogorov_ctx_t;

#ifdef FUNCTION_SIZE
#define function_size FUNCTION_SIZE
#else
#define function_size 16
#endif

#ifdef GRANULARITY
#define granularity GRANULARITY
#else
#define granularity 4
#endif

extern int32_t expected_function[];
extern int32_t empirical_function[];

#endif