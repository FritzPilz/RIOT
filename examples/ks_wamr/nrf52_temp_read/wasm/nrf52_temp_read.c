#include <stdint.h>
#include "nrf52_temp_read.h"
#include "../../utility/utility_ks.h"

extern int printf( const char *, ...);

#define WASM_EXPORT __attribute__((visibility("default")))

inline uint64_t read_memory(volatile uint64_t address){
	return *(volatile uint64_t*) address;
}

inline void write_memory(volatile uint64_t address, volatile uint64_t value){
	*(volatile uint64_t *) address = value;
}

WASM_EXPORT int main(int argc, char **argv)
{
	write_memory(TASKS_START, 1);
	while(read_memory(EVENTS_DATARDY)==0){}
	write_memory(EVENTS_DATARDY, 0);
	int value = read_memory(TEMP);
	write_memory(TASKS_STOP, 1);

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

	return result;
}