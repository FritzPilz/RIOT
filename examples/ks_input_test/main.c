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

#include "bpf.h"
#include "blob/bpf/kolmogorov_smirnov_test.bin.h"

static uint8_t _stack[512] = { 0 };

int main(void){
	create_function();
	bpf_init();

	xtimer_ticks32_t start_time = xtimer_now();

	bpf_t ks_bpf = {
        .application = kolmogorov_smirnov_test_bin,
        .application_len = sizeof(kolmogorov_smirnov_test_bin),
        .stack = _stack,
        .stack_size = sizeof(_stack)
    };

	bpf_mem_region_t expectedFunction_region, empiricalFunction_region, ks_state_region;

	KS_Test_State ks_state = {
		.empiricalFunction = empiricalFunction,
		.expectedFunction = expectedFunction,
		.value = 0,
		.result = 0,
	};
	kolmogorov_ctx_t ctx = {.kolmogorov_ctx = &ks_state}; int64_t res = 0;

	bpf_setup(&ks_bpf);

	bpf_add_region(&ks_bpf, &ks_state_region, &ks_state, sizeof(ks_state), BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
	bpf_add_region(&ks_bpf, &expectedFunction_region, &expectedFunction, sizeof(expectedFunction), BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
    bpf_add_region(&ks_bpf, &empiricalFunction_region, &empiricalFunction, sizeof(empiricalFunction), BPF_MEM_REGION_READ | BPF_MEM_REGION_WRITE);
	random_init(43);
	for(uint32_t i = 0; i < RANGE; ++i){
		ks_state.value = random_uint32_range(0,1024);
		bpf_execute_ctx(&ks_bpf, &ctx, sizeof(ctx), &res);
		//if(i % STEPS == 15){
		//	printf("max: %ld\n", ks_state.result);
		//}
	}

	xtimer_ticks32_t end_time = xtimer_now();

	uint32_t elapsed_time = xtimer_diff(end_time, start_time).ticks32;

	xtimer_sleep(1);

	printf("Elapsed Time: %ld", elapsed_time);
	printList(expectedFunction, empiricalFunction);

	return 0;
}

void create_function(void){
	//Assume that all values are equally distributed
	for(uint32_t i = 0; i < STEPS; ++i){
		expectedFunction[i] = STEP*(STEPS-i);
	}
}

void printList(int32_t* arr1, int32_t* arr2){
	for(int i = 0; i < 16; ++i){
		printf("x%i: %ld, y%i: %ld\n", i, arr1[i], i, arr2[i]);
	}
}

float toTemperature(uint32_t val){
	return (val-105)/(1.961);
}
