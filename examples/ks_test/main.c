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
#include "bpf/shared.h"
#include "bpf/kolmogorov_smirnov_test.h"

#include "bpf.h"
#include "blob/bpf/increment.bin.h"
#include "blob/bpf/kolmogorov_smirnov_test.bin.h"

typedef struct {
    __bpf_shared_ptr(KS_Context *, data);
} kolmogorov32_ctx_t;

static uint8_t _stack[512] = { 0 };

uint32_t ks_trampoline(void);

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

uint32_t ks_trampoline(void){
	uint32_t s1[SIZE1];
	create_sample(s1, SIZE1, 11);
	uint32_t s2[SIZE2];
	create_sample(s2, SIZE2, 7);

    insertionSort(s1, SIZE1); insertionSort(s2, SIZE2);
    
    KS_Test_Setup setup = {.arr1 = s1, .arr2 = s2, .len1 = SIZE1, .len2 = SIZE2, .significance = 0.05};
	KS_Test_Results result = {.max_diff = 0, .p_value = 0};
	
    bpf_t ks_bpf = {
        .application = kolmogorov_smirnov_test_bin,
        .application_len = sizeof(kolmogorov_smirnov_test_bin),
        .stack = _stack,
        .stack_size = sizeof(_stack)
    };

    int64_t res = 0;

    KS_Context raw_ctx = {.setup = &setup, .result = &result};
	kolmogorov32_ctx_t ctx = {.data = &raw_ctx};
    bpf_setup(&ks_bpf);
    int code = bpf_execute(&ks_bpf,&ctx,sizeof(&ctx),&res);

    float corrected_result = ctx.data->result->max_diff/(float)RANGE;

	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");

	for(uint32_t i = 0; i < SIZE1 || i < SIZE2; ++i){
		if(i >= SIZE1){
			printf("x%i: No value          + ", i+1);
		}else{
			printf("x%i: %f                + ", i+1, (ctx.data->setup->arr1[i])/(float)RANGE);
		}
		if(i >= SIZE2){
			printf("y%i: No value", i+1);
		}else{
			printf("y%i: %f", i+1, ctx.data->setup->arr2[i]/(float)RANGE);
		}
		printf("\n");
	}
	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("Size of ctx: %d\n", sizeof(&ctx));
	printf("Return code: %d\n", code);
	printf("Result: max_diff: %f, p_value: %f\n", corrected_result, (float)result.p_value);
	return 0;
}

uint32_t* create_sample(uint32_t* sample, uint32_t size, uint32_t seed){
    random_init(seed);
	for(uint32_t i = 0; i < size; ++i){
		uint32_t msec = (random_uint32_range(0,RANGE));
		sample[i] = msec;	
	}
	return sample;
}

uint32_t* insertionSort(uint32_t* arr, uint32_t size){
	for(int i = 0; (uint32_t)i < size; ++i){
		int j = i - 1; uint32_t key = arr[i];
		while(j >= 0 && arr[j] > arr[i]){
			arr[j+1] = arr[j];
			j = j - 1;
		}
		arr[j+1] = key;
	}
    return arr;
}