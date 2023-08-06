#include <stdint.h>

#define WASM_EXPORT __attribute__((visibility("default")))

WASM_EXPORT int main(int argc, char **argv)
{
	int value = 100; int result = 0;
	for(int i = 0; i < value;++i){
		++result;
	}

	return result;

}
