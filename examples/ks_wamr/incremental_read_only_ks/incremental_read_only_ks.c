#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "xtimer.h"

#include "../ks_test.h"
#include "../utility/utility_ks.h"
#include "wasm_export.h"

#include "incremental_read_only_ks.wasm.h"

#define runs 5

static benchmark_runs test_runs[runs] =
{
	{.times_to_run = 1, .time_taken_in_usec = 0},
	{.times_to_run = 8, .time_taken_in_usec = 0},
	{.times_to_run = 64, .time_taken_in_usec = 0},
	{.times_to_run = 512, .time_taken_in_usec = 0},
	{.times_to_run = 4096, .time_taken_in_usec = 0}
};

static wasm_module_t fibonacci_module;
static wasm_module_inst_t fibonacci_instance = NULL;

int iwasm_instance_exec_main(wasm_module_inst_t module_inst, int argc, char **argv);
bool iwasm_runtime_init(void);

void run_wasm_test(benchmark_runs* test);
int32_t prepare_wasm_run(uint8_t* wasm_buf);
void cleanup_wasm(uint8_t* wasm_buf);

void launch_test_case(KS_Test_State* ks_state){	
	puts("Fibonacci Test");
	++ks_state->value;

    uint8_t * wasm_buf = NULL;
	prepare_wasm_run(wasm_buf);

	printf("Start wasm test:\n");
    for(int i = 0; i < runs; ++i){
		run_wasm_test(&test_runs[i]);

		#if(VERBOSE_DEBUG == 1)
			printf("Result: %li\n", ks_state->result);
			print_list(&ks_state);
		#endif
		clear_empirical_function();
	}
	print_csv_header(test_runs, runs);
	print_csv_body(test_runs, runs, "Random WASM in ms,");

	printf("Start reference test:\n");
	for(int i = 0; i < runs; ++i){
		run_reference_test(&test_runs[i]);

		#if(VERBOSE_DEBUG == 1)
			print_list(&ks_state);
		#endif
		clear_empirical_function();
	}
	cleanup_wasm(wasm_buf);
	print_csv_body(test_runs, runs, "Random Plain in ms,");
}

void create_function(benchmark_runs* run){
	for(uint32_t i = 0; i < function_size; ++i){
		expected_function[i] = run->times_to_run/function_size*(function_size-i);
	}
}

void run_wasm_test(benchmark_runs* test){
	int argc = 1;
    char *argv[] = { "100" };
	create_function(test);

	uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());
    for(uint32_t i = 0; i < test->times_to_run; ++i){
        iwasm_instance_exec_main(fibonacci_instance, argc, argv);
    }

	uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());
	test->time_taken_in_usec = (end_time-start_time);
}

void run_reference_test(benchmark_runs* test){
	create_function(test);

	uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());

	for(uint32_t i = 0; i < test->times_to_run; ++i){
		uint32_t value = xtimer_usec_from_ticks(xtimer_now())%(function_size*granularity);
		kolmogorov_smirnov_test(value);
	}
	 uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());
	 test->time_taken_in_usec = (end_time-start_time);
}

int32_t prepare_wasm_run(uint8_t* wasm_buf){
	iwasm_runtime_init();
	wasm_buf = malloc(sizeof(incremental_read_only_ks_wasm));
	if(!wasm_buf){
		return -1;
	}
	memcpy(wasm_buf, incremental_read_only_ks_wasm, sizeof(incremental_read_only_ks_wasm));

	char error_buf[128];
    if (!(fibonacci_module = wasm_runtime_load(wasm_buf, sizeof(incremental_read_only_ks_wasm),
        error_buf, sizeof(error_buf)))) {
        puts(error_buf);
		return -1;
    }

    if (!(fibonacci_instance = wasm_runtime_instantiate(fibonacci_module, 8 * 1024,
        8 * 1024, error_buf, sizeof(error_buf)))) {
        puts(error_buf);
        return -1;
    }

	//attr_container_set_bytearray(,"Empricial Function",,);
	//attr_container_set_bytearray(,"Expected Function",,);
	return 0;
}

void cleanup_wasm(uint8_t* wasm_buf){
	wasm_runtime_deinstantiate(fibonacci_instance);
    free(wasm_buf);
}