#include <stdio.h>
#include "utility_ks.h"

void clearEmpiricalFunction(benchmark_runs* run){
	for(uint32_t i = 0; i < run->values; ++i){
		empirical_function[i] = 0;
	}
}

void print_list(KS_Test_State* state){
	for(uint32_t i = 0; i < state->values; ++i){
		printf("x%li: %li, y%li: %li\n", i, state->expected_function[i], i, state->empirical_function[i]);
	}
}