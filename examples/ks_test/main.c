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
#include "bpf/kolmogorov_smirnov_test.h"

#include "bpf.h"
#include "blob/bpf/increment.bin.h"
#include "blob/bpf/kolmogorov_smirnov_test.bin.h"

static uint8_t _stack[512] = { 0 };

int ks_trampoline(void);

int main(void)
{
    bpf_init();

    puts("All up, running the rBPF VM now");

    bpf_t bpf = {
        .application = increment_bin,
        .application_len = sizeof(increment_bin),
        .stack = _stack,
        .stack_size = sizeof(_stack),
    };

    unsigned int ctx = 4;
    int64_t result = 0;

    bpf_setup(&bpf);
    int res = bpf_execute(&bpf, (void*)ctx, sizeof(ctx), &result);

    ks_trampoline();

    printf("Return code: %d\n", res);
    printf("Result: %ld\n", (unsigned long)result);

    /* should never be reached */
    return 0;
}

////////KS TEST//////////

int ks_trampoline(void){
	int s1[SIZE1];
	create_sample(s1, SIZE1, 11);
	int s2[SIZE2];
	create_sample(s2, SIZE2, 7);

    insertionSort(s1, SIZE1); insertionSort(s2, SIZE2);
    
    KS_Test_Setup setup = {.arr1 = s1, .arr2 = s2, .len1 = SIZE1, .len2 = SIZE2, .significance = 0.05};
	KS_Test_Results result;
	
    //kolmogorov_smirnov_test(&setup, &result);
    bpf_t ks_bpf = {
        .application = kolmogorov_smirnov_test_bin,
        .application_len = sizeof(kolmogorov_smirnov_test_bin),
        .stack = _stack,
        .stack_size = sizeof(_stack)
    };

    int64_t res = 0;

    KS_Context ctx = {.setup = &setup, .result = &result};
    bpf_setup(&ks_bpf);
    bpf_execute(&ks_bpf,(void*)&ctx,sizeof(ctx),&res);

    float corrected_result = result.max_diff/(float)RANGE;

	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");

	for(int i = 0; i < SIZE1 || i < SIZE2; ++i){
		if(i >= SIZE1){
			printf("x%i: No value          + ", i+1);
		}else{
			printf("x%i: %f                + ", i+1, (s1[i])/(float)RANGE);
		}
		if(i >= SIZE2){
			printf("y%i: No value", i+1);
		}else{
			printf("y%i: %f", i+1, s2[i]/(float)RANGE);
		}
		printf("\n");
	}
	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");

	printf("Result: max_diff: %f, p_value: %f\n", corrected_result, (float)result.p_value);
	return 0;
}

int* create_sample(int* sample, int size, int seed){
    random_init(seed);
	for(int i = 0; i < size; ++i){
		int msec = (random_uint32_range(0,RANGE));
		sample[i] = msec;	
	}
	return sample;
}

int* insertionSort(int* arr, int size){
	//float tmp = 0;
	for(int i = 0; i < size; ++i){
		int j = i - 1; int key = arr[i];
		while(j >= 0 && arr[j] > arr[i]){
			arr[j+1] = arr[j];
			j = j - 1;
		}
		arr[j+1] = key;
	}
    return arr;
}