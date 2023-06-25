/* Please note: Do NOT include bpf.h in the bpf part. stdlib.h cannot be found */

#ifndef KS_TEST
#define KS_TEST

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

void create_function(benchmark_runs* run);

void print_list(benchmark_runs* run);

void clearEmpiricalFunction(benchmark_runs* run);

int32_t expected_function[32];

int32_t empirical_function[32];

#ifndef NRF_TEMP_BASE
#define NRF_TEMP_BASE               0x4000C000UL
#endif

#define TASKS_START NRF_TEMP_BASE+0x00000000
#define TASKS_STOP NRF_TEMP_BASE+0x00000004
#define EVENTS_DATARDY NRF_TEMP_BASE+0x00000100
#define TEMP NRF_TEMP_BASE+0x00000508

#endif