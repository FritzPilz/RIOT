/*
 * Copyright (c) 2021 Koen Zandberg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       Minimal bpf example
 *
 * @author      Koen Zandberg <koen.zandberg@inria.fr>
 *
 * @}
 */
#include <stdio.h>
#include "random.h"
#include "xtimer.h"
#include "bpf/shared.h"
#include "bpf/kolmogorov_smirnov_test.h"
#include "cpu_conf.h"

#include "bpf.h"
#include "blob/bpf/kolmogorov_smirnov_test.bin.h"

const int32_t runs = 4;

static uint8_t _stack[512] = { 0 };
static benchmark_runs test_runs[4] =
{
	{.times_to_run = 32, .time_taken_in_usec = 0, .empirical_function = empirical_functions[0], .expected_function = expected_functions[0], .values = 32, .valueRange = 4},
	{.times_to_run = 512, .time_taken_in_usec = 0, .empirical_function = empirical_functions[1], .expected_function = expected_functions[1], .values = 32, .valueRange = 4},
	{.times_to_run = 1024, .time_taken_in_usec = 0, .empirical_function = empirical_functions[2], .expected_function = expected_functions[2], .values = 32, .valueRange = 4},
	{.times_to_run = 2048, .time_taken_in_usec = 0, .empirical_function = empirical_functions[3], .expected_function = expected_functions[3], .values = 32, .valueRange = 4}
};
void runTest(bpf_t* ks_bpf, kolmogorov_ctx_t* ctx, benchmark_runs* test);

int main(void){
	bpf_init();

	for(int i = 0; i < runs; ++i){
		bpf_t ks_bpf = {
	        .application = kolmogorov_smirnov_test_bin,
    	    .application_len = sizeof(kolmogorov_smirnov_test_bin),
        	.stack = _stack,
	        .stack_size = sizeof(_stack)
    	};

		bpf_mem_region_t expectedFunction_region, empiricalFunction_region, ks_state_region, temperature_sensor_region;

		KS_Test_State ks_state = {
			.expectedFunction = test_runs->expected_function,
			.empiricalFunction = test_runs->empirical_function,
			.value = 0,
			.result = 0,
			.valueRange = test_runs[i].valueRange,
			.values = test_runs[i].values
		};
		kolmogorov_ctx_t ctx = {.kolmogorov_ctx = &ks_state};

		bpf_setup(&ks_bpf);

		bpf_add_region(&ks_bpf, &ks_state_region, &ks_state, sizeof(ks_state), BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
		bpf_add_region(&ks_bpf, &expectedFunction_region, &test_runs[i].expected_function, sizeof(&test_runs[i].expected_function), BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
    	bpf_add_region(&ks_bpf, &empiricalFunction_region, &test_runs[i].empirical_function, sizeof(&test_runs[i].empirical_function), BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
		bpf_add_region(&ks_bpf, &temperature_sensor_region ,NRF_TEMP , sizeof(*NRF_TEMP), BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);

		runTest(&ks_bpf, &ctx, &test_runs[i]);
		clearEmpiricalFunction(&test_runs[i]);

		float elapsed_time_msec = test_runs[i].time_taken_in_usec/1000.0;

		printf("Elapsed Time: %f microseconds\n", elapsed_time_msec);
		print_list(&test_runs[i]);
	}

	return 0;
}

void create_function(benchmark_runs* run){
	//Assume that all values are equally distributed
	for(uint32_t i = 0; i < run->values; ++i){
		run->expected_function[i] = run->valueRange*(run->values-i);
	}
}

void print_list(benchmark_runs* run){
	for(uint32_t i = 0; i < run->values; ++i){
		printf("x%li: %li, y%li: %li\n", i, run->expected_function[i], i, run->empirical_function[i]);
	}
}

void runTest(bpf_t* ks_bpf, kolmogorov_ctx_t* ctx, benchmark_runs* test){
	int64_t res = 0;
	create_function(test);

	uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());

	for(uint32_t i = 0; i < test->times_to_run; ++i){
		bpf_execute_ctx(ks_bpf, ctx, sizeof(*ctx), &res);
	}

	uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());

	test->time_taken_in_usec = (end_time-start_time);
}

void clearEmpiricalFunction(benchmark_runs* run){
	for(uint32_t i = 0; i < run->values; ++i){
		run->empirical_function[i] = 0;
	}
}