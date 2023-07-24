/*
 * Copyright (c) 2021 Koen Zandberg
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
 * @brief       Minimal bpf example
 *
 * @author      Koen Zandberg <koen.zandberg@inria.fr>
 *
 * @}
 */
#include <stdio.h>
#include "xtimer.h"

#include "bpf.h"
#include "blob/bpf/fibonacci.bin.h"

static uint8_t _stack[512] = { 0 };

int main(void)
{
    bpf_init();

    bpf_t bpf = {
        .application = fibonacci_bin,
        .application_len = sizeof(fibonacci_bin),
        .stack = _stack,
        .stack_size = sizeof(_stack),
    };

    unsigned int ctx = 24;
    int64_t result = 0;

    bpf_setup(&bpf);

    uint32_t start_time = xtimer_usec_from_ticks(xtimer_now());    
    int res = bpf_execute(&bpf, (void*)ctx, sizeof(ctx), &result);
    uint32_t end_time = xtimer_usec_from_ticks(xtimer_now());

    printf("fib(%d):\n",ctx);
    printf("Return code: %d\n", res);
    printf("Result: %ld\n", (unsigned long)result);
    printf("Time taken: %f\n", (end_time-start_time)/1000.0);

    /* should never be reached */
    return 0;
}
