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

int fib(int n){
    if(n <= 2){
        return n;
    }
    int fib = 1;
    int prevFib = 0;
    for(int i = 1; i < n; ++i){
        int temp = fib;
        fib += prevFib;
        prevFib = temp;
    }
    return fib;
}

int main(void)
{

    unsigned int ctx = 24;
    int64_t result = 0;

    xtimer_usleep(500);
    printf("fib(%d):\n",ctx);
    xtimer_usleep(500);
    printf("Plain results in ms,");
    xtimer_usleep(500);
    uint32_t time_taken = 0;
    for(int i = 0; i < 20; ++i){
        uint32_t start_time_run = xtimer_usec_from_ticks(xtimer_now());
        fib(ctx);
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
