#ifndef KS_TEST
#define KS_TEST

#include "bpf/shared.h"

typedef struct benchmark_runs{
    uint32_t times_to_run;
    uint32_t time_taken_in_usec;
    uint32_t valueRange;
    uint32_t values;
} benchmark_runs;

void launch_test_case(void);
void create_function(benchmark_runs* run);

#endif