/* Copyright (C) World
 * a native printf is provided by the builtin libc of wamr */

#include <stddef.h>
#include <stdint.h>
#include "saul.h"

#ifdef __cplusplus
extern "C" int printf( const char *, ...);
#define WASM_EXPORT __attribute__((visibility("default"))) extern "C"
#else
extern int printf( const char *, ...);
#define WASM_EXPORT __attribute__((visibility("default")))
#endif

WASM_EXPORT int main(int argc, char **argv)
{
    int type = SAUL_SENSE_TEMP;
    uintptr_t device = saul_reg_find_type(type);
    return (int)(saul_reg_read(device) * 100);
}
