#include <stdio.h>
#include "bpf.h"
#include "utility/include/test_ks.h"
#include "utility/include/shared_ks.h"

int32_t expected_function[function_size];
int32_t empirical_function[function_size];

int main(void){
    bpf_init();

    KS_Test_State ks_state;
    ks_state.expected_function = expected_function;
	ks_state.empirical_function = empirical_function;
	ks_state.values = function_size;
	ks_state.value_range = granularity;

    printf("Granularity: %i\n", granularity);
    printf("Function size: %i\n", function_size);

    launch_test_case(&ks_state);
}