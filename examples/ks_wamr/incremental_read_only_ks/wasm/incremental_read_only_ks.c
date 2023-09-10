#include <stdint.h>

extern int printf( const char *, ...);

#define WASM_EXPORT __attribute__((visibility("default")))

WASM_EXPORT int main(int argc, char **argv)
{
	volatile int value = 0;
	for(int i = 0; i < 100;++i){
		++value;
	}
	printf("Value: %i\n", value);
	return value;
}
