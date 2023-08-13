#ifndef KS_TEST
#define KS_TEST

#include "bpf/shared.h"
#include "bpf.h"

typedef struct KS_Test_State KS_Test_State;
typedef struct kolmogorov_ctx_t kolmogorov_ctx_t;

typedef struct benchmark_runs{
    uint32_t times_to_run;
    uint32_t time_taken_in_usec;
    char* test_type;
} benchmark_runs;

void create_function(benchmark_runs* run);
void run_reference_test(benchmark_runs* test);
void run_bpf_test(bpf_t* ks_bpf, kolmogorov_ctx_t* ctx, benchmark_runs* test);

void print_list(KS_Test_State* run);
void clear_empirical_function(void);
void launch_test_case(KS_Test_State* ks_state);

void print_csv_header(benchmark_runs* run, int32_t runs);
void print_csv_body(benchmark_runs* run, int32_t runs, const char* test_type);
uint32_t kolmogorov_smirnov_test(uint32_t value);

#endif