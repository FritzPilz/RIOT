/* Please note: Do NOT include bpf.h in the bpf part. stdlib.h cannot be found */

#ifndef UTILITY_KS
#define UTILITY_KS

#include "bpf/shared.h"

typedef struct KS_Test_State{
    __bpf_shared_ptr(int32_t *, expected_function);
    __bpf_shared_ptr(int32_t *, empirical_function);
    uint32_t value;
    uint32_t result;
    uint32_t value_range;
    uint32_t values;
} KS_Test_State;

typedef struct {
    __bpf_shared_ptr(KS_Test_State *, kolmogorov_ctx);
} kolmogorov_ctx_t;

void print_list(KS_Test_State* run);
void clearEmpiricalFunction(void);
void launch_test_case(KS_Test_State* ks_state);

#ifdef FUNCTION_SIZE
#define function_size FUNCTION_SIZE
#else
#define function_size 16
#endif

#ifdef VALUE_RANGE
#define granularity VALUE_RANGE
#else
#define granularity 4
#endif

extern int32_t expected_function[];
extern int32_t empirical_function[];

#endif