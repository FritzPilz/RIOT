#include <stdint.h>
#include "../../utility/utility_ks.h"

extern int printf( const char *, ...);
extern long strtol(const char *restrict nptr, char **restrict endptr, int base);

#define WASM_EXPORT __attribute__((visibility("default")))

WASM_EXPORT int main(int argc, char **argv)
{
	char* endptr;
	uint32_t value = strtol(argv[argc-1], &endptr, 10);

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
