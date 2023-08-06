#include <stdio.h>
#include "../ks_test.h"
#include "utility_ks.h"

void clear_empirical_function(void){
	for(uint32_t i = 0; i < function_size; ++i){
		empirical_function[i] = 0;
	}
}

void print_list(KS_Test_State* state){
	for(uint32_t i = 0; i < function_size; ++i){
		printf("x%li: %li, y%li: %li\n", i, state->expected_function[i], i, state->empirical_function[i]);
	}
}