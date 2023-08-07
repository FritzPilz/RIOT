#include <stdint.h>
#include "../../utility/utility_ks.h"

extern int printf( const char *, ...);

#define WASM_EXPORT __attribute__((visibility("default")))

WASM_EXPORT int main(int argc, char **argv)
{
	int value = 100; int inc = 0;
	for(int i = 0; i < value;++i){
		++inc;
	}

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

	printf("Arguments:\n");
	for(int i = 0; i < argc-1; ++i){
		printf("%u|", (uint32_t)argv[i][1*4-1]);
		printf("%u|", (uint32_t)argv[i][2*4-1]);
		printf("%u|", (uint32_t)argv[i][3*4-1]);
		printf("%u|", (uint32_t)argv[i][4*4-1]);
		printf("%u|", (uint32_t)argv[i][5*4-1]);
		printf("%u|", (uint32_t)argv[i][6*4-1]);
		printf("%u\n", (uint32_t)argv[i][7*4-1]);
	}

	return result;
}
