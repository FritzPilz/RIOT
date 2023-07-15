#include <stdio.h>
#include "bpf.h"
#include "bpf/shared.h"
#include "ks_test.h"
#include "utility/utility_ks.h"

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

void print_csv(benchmark_runs* run, int32_t runs){
    printf("Number of runs,");
    for(int i = 0; i < runs; ++i){
        if(i != runs-1){
            printf("%li,", run[i].times_to_run);
        }else{
            printf("%li\n", run[i].times_to_run);
        }
    }
    printf("Time Taken,");
    for(int i = 0; i < runs; ++i){
        if(i != runs-1){
            printf("%f ms,", run[i].time_taken_in_usec/1000.0);
        }else{
            printf("%f ms\n", run[i].time_taken_in_usec/1000.0);
        }
    }
}

uint32_t kolmogorov_smirnov_test(uint32_t value){
	for(uint32_t i = 0; i < function_size; ++i){
		if(value < i*granularity){
			continue;
		}else{
			++empirical_function[i];
		}
	}
	int32_t result = 0;
	for(uint32_t i = 0; i < function_size; ++i){
		int32_t F1 = expected_function[i]; int32_t F2 = empirical_function[i];
		int32_t diff = F1-F2;
		if(diff < 0){
			diff = -diff;
		}
		result = (diff > result) ? diff : result;
	}
	return (uint32_t)result;
}