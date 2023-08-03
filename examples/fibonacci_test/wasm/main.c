/*
 * Copyright (C) 2019 Freie Universität Berlin
 * Copyright (C) 2021 Inria
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       (Mock-up) BLE heart rate sensor example with BPF
 *
 * @author      Koen Zandberg <koen@bergzand.net>
 *
 * @}
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "xtimer.h"
#include "wasm_export.h"

#include "blob/hello.wasm.h"

static wasm_module_t fibonacci_module;
static wasm_module_inst_t fibonacci_instance = NULL;

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

    memcpy(wasm_buf, hello_wasm, sizeof(hello_wasm));

    char error_buf[128];
    if (!(fibonacci_module = wasm_runtime_load(wasm_buf, sizeof(hello_wasm),
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
    int result;
    xtimer_usleep(500);
    printf("fib(24):\n");
    xtimer_usleep(500);
    printf("WASM results in ms,");
    xtimer_usleep(500);
    uint32_t time_taken = 0;
    for(int i = 0; i < 20; ++i){
        uint32_t start_time_run = xtimer_usec_from_ticks(xtimer_now());
        result = iwasm_instance_exec_main(fibonacci_instance, argc, argv);
        uint32_t end_time_run = xtimer_usec_from_ticks(xtimer_now());
        time_taken += end_time_run-start_time_run;   
        printf("%f,", (time_taken)/1000.0);
        xtimer_usleep(500);
    }

    printf("\n");
    printf("Result: %ld\n", (unsigned long)result);

    wasm_runtime_deinstantiate(fibonacci_instance);

    free(wasm_buf);

    return (result == 0) ? 0 : -1;
}
