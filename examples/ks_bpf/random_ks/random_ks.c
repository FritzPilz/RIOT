#include <stdio.h>
#include "xtimer.h"

#include "bpf.h"
#include "bpf/shared.h"
#include "../utility/include/test_ks.h"
#include "../utility/include/shared_ks.h"
#include "bpf/random_ks_bpf.bin.h"

#define runs 7

static uint8_t _stack[512] = { 0 };
static benchmark_runs test_runs[runs] =
{
	{.times_to_run = 1, .time_taken_in_usec = 0},
	{.times_to_run = 4, .time_taken_in_usec = 0},
	{.times_to_run = 8, .time_taken_in_usec = 0},
	{.times_to_run = 12, .time_taken_in_usec = 0},
	{.times_to_run = 64, .time_taken_in_usec = 0},
	{.times_to_run = 512, .time_taken_in_usec = 0},
	{.times_to_run = 4096, .time_taken_in_usec = 0}
};

void launch_test_case(KS_Test_State* ks_state){
	bpf_t ks_bpf = {
	    .application = random_ks_bpf_bin,
    	.application_len = sizeof(random_ks_bpf_bin),
        .stack = _stack,
	    .stack_size = sizeof(_stack)
    };

    bpf_mem_region_t expectedFunction_region, empiricalFunction_region, ks_state_region;
	kolmogorov_ctx_t ctx = {.kolmogorov_ctx = ks_state};

	bpf_setup(&ks_bpf);

	bpf_add_region(&ks_bpf, &expectedFunction_region, &expected_function, sizeof(int32_t)*function_size, BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
    bpf_add_region(&ks_bpf, &empiricalFunction_region, &empirical_function, sizeof(int32_t)*function_size, BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
	bpf_add_region(&ks_bpf, &ks_state_region, ks_state, sizeof(*ks_state), BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
	
	printf("Start bpf test:\n");
    for(int i = 0; i < runs; ++i){
		ks_state->value = 0;
		ks_state->result = 0;

		run_bpf_test(&ks_bpf, &ctx, &test_runs[i]);

		#if(VERBOSE_DEBUG == 1)
			printf("Result: %li\n", ks_state->result);
			print_list(ks_state);
		#endif
		clear_empirical_function();
	}
	print_csv_header(test_runs, runs);
	print_csv_body(test_runs, runs, "Random FC in ms,");

	printf("Start reference test:\n");
	for(int i = 0; i < runs; ++i){
		ks_state->value = 0;
		ks_state->result = 0;

		run_reference_test(&test_runs[i]);

		#if(VERBOSE_DEBUG == 1)
			print_list(ks_state);
		#endif
		clear_empirical_function();
	}
	print_csv_body(test_runs, runs, "Random Plain in ms,");
}

void create_function(benchmark_runs* run){
	for(uint32_t i = 0; i < function_size; ++i){
		expected_function[i] = run->times_to_run/function_size*(function_size-i);
	}
}

void run_bpf_test(bpf_t* ks_bpf, kolmogorov_ctx_t* ctx, benchmark_runs* test){
	int64_t res = 0;
	create_function(test);

	uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());

	for(uint32_t i = 0; i < test->times_to_run; ++i){
		ctx->kolmogorov_ctx->value = xtimer_usec_from_ticks(xtimer_now())%(function_size*granularity);
		bpf_execute_ctx(ks_bpf, ctx, sizeof(*ctx), &res);
	}

	uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());
	test->time_taken_in_usec = (end_time-start_time);
}

void run_reference_test(benchmark_runs* test){
	create_function(test);

	uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());

	for(uint32_t i = 0; i < test->times_to_run; ++i){
		uint32_t value = xtimer_usec_from_ticks(xtimer_now())%(function_size*granularity);
		kolmogorov_smirnov_test(value);
	}
	 uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());
	 test->time_taken_in_usec = (end_time-start_time);
}