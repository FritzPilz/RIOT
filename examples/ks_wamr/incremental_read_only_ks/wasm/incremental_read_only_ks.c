#include <stdint.h>

void pass_WAMR_value(int value);

#define WASM_EXPORT __attribute__((visibility("default")))

WASM_EXPORT int main(int argc, char **argv)
{
	volatile int value = 0;
	for(int i = 0; i < 100;++i){
		++value;
	}
	pass_WAMR_value(value);
	return value;
}
