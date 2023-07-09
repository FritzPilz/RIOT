/* Please note: Do NOT include bpf.h in the bpf part. stdlib.h cannot be found */

#ifndef UTILITY_KS
#define UTILITY_KS

#include "bpf/shared.h"

typedef struct benchmark_runs{
    uint32_t times_to_run;
    uint32_t time_taken_in_usec;
    int32_t* empirical_function;
    int32_t* expected_function;
    uint32_t valueRange;
    uint32_t values;
} benchmark_runs;

typedef struct KS_Test_State{
    __bpf_shared_ptr(int32_t *, expected_function);
    __bpf_shared_ptr(int32_t *, empirical_function);
    uint32_t value;
    uint32_t result;
    uint32_t valueRange;
    uint32_t values;
} KS_Test_State;

typedef struct {
    __bpf_shared_ptr(KS_Test_State *, kolmogorov_ctx);
} kolmogorov_ctx_t;

uint32_t delta_kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx);
void print_list(KS_Test_State* run);
void clearEmpiricalFunction(benchmark_runs* run);

#define function_size 32

extern int32_t expected_function[];
extern int32_t empirical_function[];

#endif