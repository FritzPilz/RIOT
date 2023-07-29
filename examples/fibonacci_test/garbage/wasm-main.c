/*
 * Copyright (C) 2020 TU Bergakademie Freiberg Karl Fessel
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "wasm_export.h"

/*provide some test program*/
#include "blob/hello.wasm.h"

static wasm_module_t fibonacci_module;
static wasm_module_inst_t fibonacci_instance = NULL;

bool iwasm_runtime_init(void);
void iwasm_runtime_destroy(void);

/* wamr_run is a very direct interpretation of "i like to have a wamr_run" */
int wamr_run(void *bytecode, size_t bytecode_len, int argc, char **argv);

/* wamr_run_cp creates a copy bytecode and argv
 * if argc is 0 it is set to 1 and argv[0] is set to ""
 * to create some space for a return value */
int wamr_run_cp(const void *bytecode, size_t bytecode_len, int argc, const char **argv);

int iwasm_instance_exec_main(wasm_module_inst_t module_inst, int argc, char **argv);

bool iwasm_runtime_init(void);

int main(void)
{
    puts("Fibonacci Test");

    int res = 0;
    (void)res;

    iwasm_runtime_init();

    uint8_t * wasm_buf = malloc(sizeof(hello_wasm));
    if (!wasm_buf) {
        return -1;
    }

    memcpy((void*)hello_wasm, wasm_buf, sizeof(hello_wasm));

    char error_buf[128];
    if (!(fibonacci_module = wasm_runtime_load(hello_wasm, sizeof(hello_wasm),
        error_buf, sizeof(error_buf)))) {
        puts(error_buf);
    }

    if (!(fibonacci_instance = wasm_runtime_instantiate(fibonacci_module, 8 * 1024,
        8 * 1024, error_buf, sizeof(error_buf)))) {
        puts(error_buf);
        return -1;
    }

    int argc = 1;
    char *argv[] = { "Test" };

    int result = iwasm_instance_exec_main(fibonacci_instance, argc, argv);

    wasm_runtime_deinstantiate(fibonacci_instance);

    int16_t fmt_result = (intptr_t)result;
    printf("Resulting fibonacci %i\n", fmt_result);

    free(wasm_buf);

    return (result == 0) ? 0 : -1;
}