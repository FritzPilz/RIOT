#ifndef KS_TEST
#define KS_TEST

#include "bpf/shared.h"

typedef struct benchmark_runs{
    uint32_t times_to_run;
    uint32_t time_taken_in_usec;
    char* test_type;
} benchmark_runs;

void create_function(benchmark_runs* run);
void runReferenceTest(benchmark_runs* test);

void print_csv(benchmark_runs* run, int32_t runs, const char* test_type);
uint32_t kolmogorov_smirnov_test(uint32_t value);

#endif