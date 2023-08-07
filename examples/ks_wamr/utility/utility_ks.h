/* Please note: Do NOT include bpf.h in the bpf part. stdlib.h cannot be found */

#ifndef UTILITY_KS
#define UTILITY_KS

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

void print_list(KS_Test_State* run);
void clear_empirical_function(void);
void launch_test_case(KS_Test_State* ks_state);

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