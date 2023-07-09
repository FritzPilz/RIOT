#include <stdio.h>
#include "bpf.h"
#include "ks_test.h"
#include "utility/utility_ks.h"

int32_t expected_function[function_size];
int32_t empirical_function[function_size];

int main(void){
    bpf_init();
    launch_test_case();
}

void print_csv(benchmark_runs* run, int32_t runs){
    printf("Number of runs,");
    for(int i = 0; i < runs; ++i){
        if(i != runs-1){
            printf("%f ms,", run[i].times_to_run/1000.0);
        }else{
            printf("%f ms\n", run[i].times_to_run/1000.0);
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