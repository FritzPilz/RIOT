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
#include "xtimer.h"

/*provide some test program*/
#include "blob/test.wasm.h"
#include "blob/hello.wasm.h"

bool iwasm_runtime_init(void);
void iwasm_runtime_destroy(void);

/* wamr_run is a very direct interpretation of "i like to have a wamr_run" */
int wamr_run(void *bytecode, size_t bytecode_len, int argc, char **argv);

/* wamr_run_cp creates a copy bytecode and argv
 * if argc is 0 it is set to 1 and argv[0] is set to ""
 * to create some space for a return value */
int wamr_run_cp(const void *bytecode, size_t bytecode_len, int argc, const char **argv);

#define telltruth(X) ((X) ? "true" : "false")

int main(void)
{
    printf("iwasm_initilised: %s\n", telltruth(iwasm_runtime_init()));

    int app_argc = 1;

    const char *app_argv[] = {"24"};
    uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());
    int ret = wamr_run_cp(hello_wasm, hello_wasm_len, app_argc, app_argv);
    uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());
    printf("fib(%s):\n", app_argv[0]);
    printf("ret = %d\n", ret);
    printf("Time taken: %f ms\n", (end_time-start_time)/1000.0);

    iwasm_runtime_destroy();
}


