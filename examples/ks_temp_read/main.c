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
//#include "nrf52.h"
#include "cpu_conf.h"
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

	uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());

	for(uint32_t i = 0; i < RANGE; ++i){
		ks_state.value = read_nrf52_temp();
		bpf_execute_ctx(&ks_bpf, &ctx, sizeof(ctx), &res);
	}

	uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());

	uint32_t elapsed_time_usec = (end_time-start_time);
	float elapsed_time_msec = elapsed_time_usec/1000.0;

	printf("Elapsed Time: %f microseconds\n", elapsed_time_msec);
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

int32_t read_nrf52_temp(void) {
	int32_t temp;
	NRF_TEMP->TASKS_START = 1;
	
	while(NRF_TEMP->EVENTS_DATARDY==0){}
	NRF_TEMP->EVENTS_DATARDY = 0;
	
	//Some calculation on the data
	temp = NRF_TEMP->TEMP;
	NRF_TEMP->TASKS_STOP = 1;
	
	printf("Read temperature: %li\n", temp);

	return temp;
}