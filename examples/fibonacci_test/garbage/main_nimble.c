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
#include "timex.h"
#include "wasm_export.h"

#include "blob/hello.wasm.h"

static wasm_module_t fibonacci_module;
static wasm_module_inst_t fibonacci_instance = NULL;
static uint8_t fibonacci_bytecode[sizeof(hello_wasm)];

int iwasm_instance_exec_main(wasm_module_inst_t module_inst, int argc, char **argv);

bool iwasm_runtime_init(void);

int main(void)
{
    puts("Fibonacci Test");

    int res = 0;
    (void)res;

    iwasm_runtime_init();

    uint8_t * wasm_buf = malloc(sizeof(fibonacci_bytecode));
    if (!wasm_buf) {
        return -1;
    }

    memcpy(fibonacci_bytecode, wasm_buf, sizeof(fibonacci_bytecode));

    char error_buf[128];
    if (!(fibonacci_module = wasm_runtime_load(fibonacci_bytecode, sizeof(fibonacci_bytecode),
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
