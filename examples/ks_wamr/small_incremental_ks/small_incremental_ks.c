#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "xtimer.h"

#include "../utility/include/test_ks.h"
#include "../utility/include/shared_ks.h"
#include "wasm_export.h"

#include "small_incremental_ks.wasm.h"

#define runs 7

static benchmark_runs test_runs[runs] =
{
	{.times_to_run = 1, .time_taken_in_usec = 0},
	{.times_to_run = 4, .time_taken_in_usec = 0},
	{.times_to_run = 8, .time_taken_in_usec = 0},
	{.times_to_run = 12, .time_taken_in_usec = 0},
	{.times_to_run = 64, .time_taken_in_usec = 0},
	{.times_to_run = 512, .time_taken_in_usec = 0},
	{.times_to_run = 4096, .time_taken_in_usec = 0}
};

static wasm_module_t small_incremental_module;
static wasm_module_inst_t small_incremental_instance = NULL;

int iwasm_instance_exec_main(wasm_module_inst_t module_inst, int argc, char **argv);
bool iwasm_runtime_init(void);

int32_t prepare_wasm_run(uint8_t* wasm_buf);
void cleanup_wasm(uint8_t* wasm_buf);

void prepare_function(int32_t* func, uint32_t size);
void copy_empirical_function_from_WAMR(wasm_exec_env_t exec_env, int32_t* arr, uint32_t size);

void launch_test_case(KS_Test_State* ks_state){	
	++ks_state->value;

    uint8_t * wasm_buf = NULL;
	prepare_wasm_run(wasm_buf);

	printf("Start wasm test:\n");
    for(int i = 0; i < runs; ++i){
		run_wasm_test(&test_runs[i]);

		#if(VERBOSE_DEBUG == 1)
			printf("Result: %li\n", ks_state->result);
			print_list(ks_state);
		#endif
		clear_empirical_function();
	}
	print_csv_header(test_runs, runs);
	print_csv_body(test_runs, runs, "Small Incremental WASM in ms,");

	printf("Start reference test:\n");
	for(int i = 0; i < runs; ++i){
		run_reference_test(&test_runs[i]);

		#if(VERBOSE_DEBUG == 1)
			print_list(ks_state);
		#endif
		clear_empirical_function();
	}
	cleanup_wasm(wasm_buf);
	print_csv_body(test_runs, runs, "Small Incremental Plain in ms,");
}

void create_function(benchmark_runs* run){
	for(uint32_t i = 0; i < function_size; ++i){
		expected_function[i] = run->times_to_run/function_size*(function_size-i);
	}
}

void run_wasm_test(benchmark_runs* test){
	create_function(test);
	int argc = 5;
	uint8_t empirical_function_copy[function_size*sizeof(int32_t)+1]; uint8_t expected_function_copy[function_size*sizeof(int32_t)+1];
	char function_size_buf[10];char granularity_buf[10];char value_buf[10];
	empirical_function_copy[(function_size*sizeof(int32_t)+1)]; memset(empirical_function_copy,0,(function_size*sizeof(int32_t)+1));
	expected_function_copy[(function_size*sizeof(int32_t)+1)]; memset(expected_function_copy,0,(function_size*sizeof(int32_t)+1));
	memcpy(expected_function_copy, expected_function, sizeof(expected_function_copy)-1);
	prepare_function((int32_t)expected_function_copy, (function_size));

	uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());
	snprintf(function_size_buf, sizeof(function_size_buf), "%lu", function_size);
	snprintf(granularity_buf, sizeof(granularity_buf), "%lu", granularity);
    for(uint32_t i = 0; i < test->times_to_run; ++i){
		snprintf(value_buf, sizeof(value_buf), "%lu", 10);
		memcpy(empirical_function_copy, empirical_function, sizeof(empirical_function_copy)-1);
		prepare_function((int32_t)empirical_function_copy, (function_size));
		char *argv[] = { empirical_function_copy, expected_function_copy, function_size_buf, granularity_buf, value_buf};
        iwasm_instance_exec_main(small_incremental_instance, argc, argv);
    }

	uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());
	test->time_taken_in_usec = (end_time-start_time);
}

void run_reference_test(benchmark_runs* test){
	create_function(test);

	uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());

	for(uint32_t i = 0; i < test->times_to_run; ++i){
		volatile int value = 0;
		for(int j = 0; j < 10; ++j){
			++value;
		}
		kolmogorov_smirnov_test(value);
	}
	 uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());
	 test->time_taken_in_usec = (end_time-start_time);
}

int32_t prepare_wasm_run(uint8_t* wasm_buf){
		static NativeSymbol native_symbols[] =
	{
		{
			"copy_empirical_function_from_WAMR",
			copy_empirical_function_from_WAMR,
			"(*~)"
		}
	};

	iwasm_runtime_init();

	int32_t n_native_symbols = sizeof(native_symbols) / sizeof(NativeSymbol);
	if (!wasm_runtime_register_natives("env", native_symbols, n_native_symbols)){
		printf("Registration of host function in WAMR module failed!");
		while(1);
	}

	wasm_buf = malloc(sizeof(small_incremental_ks_wasm));
	if(!wasm_buf){
		return -1;
	}
	memcpy(wasm_buf, small_incremental_ks_wasm, sizeof(small_incremental_ks_wasm));

	char error_buf[128];
    if (!(small_incremental_module = wasm_runtime_load(wasm_buf, sizeof(small_incremental_ks_wasm),
        error_buf, sizeof(error_buf)))) {
        puts(error_buf);
		return -1;
    }

    if (!(small_incremental_instance = wasm_runtime_instantiate(small_incremental_module, 8 * 1024,
        8 * 1024, error_buf, sizeof(error_buf)))) {
        puts(error_buf);
        return -1;
    }
	return 0;
}

void cleanup_wasm(uint8_t* wasm_buf){
	wasm_runtime_deinstantiate(small_incremental_instance);
    free(wasm_buf);
}

void prepare_function(int32_t* func, uint32_t size){
	for(int i = 0; i < size; ++i){
		if((func[i] & 0xff) == 0xff){
			func[i] |= 0x10180ff;
		}else{
			func[i] += 0x1010101;
		}
	}
}

void copy_empirical_function_from_WAMR(wasm_exec_env_t exec_env, int32_t* arr, uint32_t size){
	memcpy(empirical_function, arr, size);
}