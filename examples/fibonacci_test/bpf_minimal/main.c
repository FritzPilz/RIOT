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
    xtimer_usleep(500);
    printf("fib(%d):\n",ctx);
    xtimer_usleep(500);
    printf("BPF results in ms,");
    xtimer_usleep(500);
    uint32_t time_taken = 0;
    for(int i = 0; i < 20; ++i){
        uint32_t start_time_run = xtimer_usec_from_ticks(xtimer_now());
        bpf_execute(&bpf, (void*)ctx, sizeof(ctx), &result);
        uint32_t end_time_run = xtimer_usec_from_ticks(xtimer_now());
        time_taken += end_time_run-start_time_run;
        printf("%f,", (time_taken)/1000.0);
        xtimer_usleep(500);
    }
    printf("\n");
    printf("Result: %ld\n", (unsigned long)result);

    /* should never be reached */
    return 0;
}
