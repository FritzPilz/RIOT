#include <stdint.h>

#define WASM_EXPORT __attribute__((visibility("default")))
void copy_empirical_function_from_WAMR(int32_t* arr, uint32_t size);
void unpack_function(int32_t* func, uint32_t size);

WASM_EXPORT int main(int argc, char **argv)
{
	char* endptr;
	uint32_t function_size = strtol(argv[2], &endptr, 10);
	uint32_t granularity = strtol(argv[3], &endptr, 10);
	volatile uint32_t value = strtol(argv[4], &endptr, 10);
	int32_t* empirical_function = (int32_t*)argv[0];
	int32_t* expected_function = (int32_t*)argv[1];
	unpack_function(empirical_function, function_size);
	unpack_function(expected_function, function_size);
	for(int i = 0; i < 100;++i){
		++value;
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

	return result;
}

void unpack_function(int32_t* func, uint32_t size){
	for(int i = 0; i < size; ++i){
		if((func[i] & 0x8000) == 0x8000){
			func[i] &= 0x00001fff;
		}else{
			func[i] -= 0x1010101;
		}
	}
}