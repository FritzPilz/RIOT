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
#include "xtimer.h"
#include "random.h"
#include "kolmogorov_smirnov_test.h"

int main(void){
	create_function();
	random_init(43);
	int msec_start = xtimer_now_usec64();
	for(uint32_t i = 0; i < RANGE; ++i){
		int32_t result = delta_kolmogorov_smirnov_test(random_uint32_range(0,1024));
		if(i % STEPS == 15){
			printf("max: %d\n", result);
		}
	}
	int msec_finish = xtimer_now_usec64();

	printList(expectedFunction, empiricalFunction);
	printf("Time taken: %f microseconds\n",(float)(msec_finish-msec_start)/(float)1000.0);

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
		printf("x%i: %d, y%i: %d\n", i, arr1[i], i, arr2[i]);
	}
}

float toTemperature(uint32_t val){
	return (val-105)/(1.961);
}

uint32_t delta_kolmogorov_smirnov_test(int32_t value){
	for(int i = 0; i < STEPS; ++i){
		if(value < i*STEP){
			continue;
		}else{
			++empiricalFunction[i];
		}
	}
	int32_t result = 0;
	for(uint32_t i = 0; i < STEPS; ++i){
		int32_t F1 = expectedFunction[i]; int32_t F2 = empiricalFunction[i];
		int32_t diff = F1-F2;
		if(diff < 0){
			diff = -diff;
		}
		result = (diff > result) ? diff : result;
	}
	return result;
}