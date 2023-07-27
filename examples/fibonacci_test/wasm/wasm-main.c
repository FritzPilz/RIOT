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
#include "xtimer.h"
#include "wasm_export.h"

/*provide some test program*/
#include "blob/test.wasm.h"
#include "blob/hello.wasm.h"

bool iwasm_runtime_init(void);
void iwasm_runtime_destroy(void);

int iwasm_instance_exec_main(wasm_module_inst_t module_inst, int argc, char **argv);

static wasm_module_t fib_module;
static wasm_module_inst_t fib_instance = NULL;

/* wamr_run is a very direct interpretation of "i like to have a wamr_run" */
int wamr_run(void *bytecode, size_t bytecode_len, int argc, char **argv);

/* wamr_run_cp creates a copy bytecode and argv
 * if argc is 0 it is set to 1 and argv[0] is set to ""
 * to create some space for a return value */
int wamr_run_cp(const void *bytecode, size_t bytecode_len, int argc, const char **argv);

#define telltruth(X) ((X) ? "true" : "false")

int main(void)
{
    int res = 0;
    (void)res;

    printf("iwasm_initilised: %s\n", telltruth(iwasm_runtime_init()));

    uint8_t * wasm_buf = malloc(hello_wasm_len);
    if (!wasm_buf) {
        return -1;
    }

    memcpy(wasm_buf, hello_wasm, sizeof(hello_wasm));

    char error_buf[128];
    if (!(fib_module = wasm_runtime_load(hello_wasm, sizeof(hello_wasm),
        error_buf, sizeof(error_buf)))) {
        puts(error_buf);
    }

    if (!(fib_instance = wasm_runtime_instantiate(fib_module, 8 * 1024,
        8 * 1024, error_buf, sizeof(error_buf)))) {
        puts(error_buf);
        return 1;
    }

    int app_argc = 1;

    char *app_argv[] = {"24"};
    uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());
    int ret = iwasm_instance_exec_main(fib_instance, app_argc, app_argv);
    uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());
    printf("fib(%s):\n", app_argv[0]);
    printf("ret = %d\n", ret);
    printf("Time taken: %f ms\n", (end_time-start_time)/1000.0);

    wasm_runtime_deinstantiate(fib_instance);
     wasm_runtime_unload(fib_module);

    iwasm_runtime_destroy();
    free(wasm_buf);
}


