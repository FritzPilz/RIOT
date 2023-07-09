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
#include "cpu_conf.h"

#include "bpf.h"
#include "bpf/nrf52_temp_read_bpf.bin.h"
#include "../utility/utility_ks.h"
#include "../ks_test.h"

const int32_t runs = 4;

static uint8_t _stack[512] = { 0 };
static benchmark_runs test_runs[4] =
{
	{.times_to_run = 32, .time_taken_in_usec = 0, .values = 32, .valueRange = 4},
	{.times_to_run = 512, .time_taken_in_usec = 0, .values = 32, .valueRange = 4},
	{.times_to_run = 1024, .time_taken_in_usec = 0, .values = 32, .valueRange = 4},
	{.times_to_run = 2048, .time_taken_in_usec = 0, .values = 32, .valueRange = 4}
};

void runTest(bpf_t* ks_bpf, kolmogorov_ctx_t* ctx, benchmark_runs* test);

void launch_test_case(void){
	bpf_t ks_bpf = {
	    .application = nrf52_temp_read_bpf_bin,
    	.application_len = sizeof(nrf52_temp_read_bpf_bin),
        .stack = _stack,
	    .stack_size = sizeof(_stack)
    };

	bpf_mem_region_t expectedFunction_region, empiricalFunction_region, ks_state_region, temperature_sensor_region;
	KS_Test_State ks_state; kolmogorov_ctx_t ctx = {.kolmogorov_ctx = &ks_state};

	bpf_setup(&ks_bpf);

	bpf_add_region(&ks_bpf, &expectedFunction_region, &expected_function, sizeof(int32_t)*function_size, BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
    bpf_add_region(&ks_bpf, &empiricalFunction_region, &empirical_function, sizeof(int32_t)*function_size, BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
	bpf_add_region(&ks_bpf, &temperature_sensor_region ,NRF_TEMP , sizeof(*NRF_TEMP), BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
	bpf_add_region(&ks_bpf, &ks_state_region, &ks_state, sizeof(ks_state), BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);

	ks_state.expected_function = expected_function;
	ks_state.empirical_function = empirical_function;

	for(int i = 0; i < 4; ++i){

		ks_state.value = 0;
		ks_state.result = 0;
		ks_state.valueRange = test_runs[i].valueRange;
		ks_state.values = test_runs[i].values;

		runTest(&ks_bpf, &ctx, &test_runs[i]);

		float elapsed_time_msec = test_runs[i].time_taken_in_usec/1000.0;

		printf("Elapsed Time: %f microseconds\n", elapsed_time_msec);
		printf("Value: %li\n", ks_state.value);
		printf("Result: %li\n", ks_state.result);
		print_list(&ks_state);
		clearEmpiricalFunction();
	}
}

void create_function(benchmark_runs* run){
	//Assume that all values are equally distributed
	printf("create functtion...\n");
	for(uint32_t i = 0; i < run->values; ++i){
		expected_function[i] = run->times_to_run/run->values*(run->values-i);
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