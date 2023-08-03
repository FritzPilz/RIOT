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

void print_csv_header(benchmark_runs* run, int32_t runs){
    printf(",");
    for(int i = 0; i < runs; ++i){
        if(i != runs-1){
            printf("%li,", run[i].times_to_run);
        }else{
            printf("%li,Regression Slope, Regression Intercept, R^2\n", run[i].times_to_run);
        }
    }
}

void print_csv_body(benchmark_runs* run, int32_t runs, const char* test_type){
    float* observations_x = (float*)calloc(runs, sizeof(float));
    float* observations_y = (float*)calloc(runs, sizeof(float));
    for(int i = 0; i < runs; ++i){
        observations_x[i] = (float)run[i].times_to_run;
        observations_y[i] = (float)run[i].time_taken_in_usec/1000.0;
    }
    float coefficient_b = covariance(observations_x, observations_y, runs)/variance(observations_x, runs);
    float coefficient_a = average(observations_y, runs) - coefficient_b * average(observations_x, runs);
    float res_square = 0.0; float tot_square = 0.0;
    for(int i = 0; i < runs; ++i){
        float temp_res = (observations_y[i]-linear_function(coefficient_a,coefficient_b,observations_x[i]));
        res_square += temp_res*temp_res;
        tot_square += (observations_y[i]-average(observations_y, runs))*(observations_y[i]-average(observations_y, runs));
    }
    float r_squared = 1.0 - res_square/tot_square;
    printf("%s",test_type);
    for(int i = 0; i < runs; ++i){
        if(i != runs-1){
            printf("%f,", run[i].time_taken_in_usec/1000.0);
        }else{
            printf("%f,%f,%f,%f\n", run[i].time_taken_in_usec/1000.0, coefficient_b, coefficient_a, r_squared);
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

float average(float* observations, int32_t values){
    float sum = 0.0;
    for(int i = 0; i < values; ++i){
        sum += observations[i];
    }
    return sum/values;
}

float variance(float* observations, int32_t values){
    float average_x = average(observations, values);
    float sum = 0;
    for(int i = 0; i < values; ++i){
        sum += (observations[i] - average_x)*(observations[i] - average_x);
    }
    return sum;
}

float covariance(float* observations_x, float* observations_y, int32_t values){
    float average_x = average(observations_x, values); float average_y = average(observations_y, values);
    float sum = 0;
    for(int i = 0; i < values; ++i){
        sum += (observations_x[i] - average_x)*(observations_y[i] - average_y);
    }
    return sum;
}

float linear_function(float a, float b, float x){
    return a+b*x;
}