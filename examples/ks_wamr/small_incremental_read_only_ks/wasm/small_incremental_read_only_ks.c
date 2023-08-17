#include <stdint.h>

#define WASM_EXPORT __attribute__((visibility("default")))

WASM_EXPORT int main(int argc, char **argv)
{
	volatile int value = 0;
	for(int i = 0; i < 10;++i){
		++value;
	}

	return value;

}
