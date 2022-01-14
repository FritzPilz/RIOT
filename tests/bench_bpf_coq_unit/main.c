/*
 * Copyright (C) 2020 Inria
 * Copyright (C) 2020 Koen Zandberg <koen@bergzand.net>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Tests bpf virtual machine
 *
 * @author      Koen Zandberg <koen@bergzand.net>
 *
 * @}
 */
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include "embUnit.h"
#include "timex.h"
#include "ztimer.h"
#include "bpf/shared.h"
#include "bpf/instruction.h"
#include "unaligned.h"
#include "util.h"

#if BPF_COQ
#include "interpreter.h"
#else
#include "bpf.h"
#endif

static uint8_t _bpf_stack[512];

#if BPF_COQ
static struct memory_region init_memory_region0 = {.start_addr = 0LLU, .block_size = 0LLU };
static struct memory_region init_memory_region1 = {.start_addr = 0LLU, .block_size = sizeof(_bpf_stack) };
static struct memory_region init_memory_region2 = {.start_addr = 0LLU, .block_size = 0LLU };
#endif

static const test_content_t tests[] = {
    {
        .instruction = {
            .opcode = 0x07,
        },
        .name = "ALU Add",
    },
    {
        .instruction = {
            .opcode = 0x0f,
        },
        .name = "ALU Add imm",
    },
    {
        .instruction = {
            .opcode = 0x2f,
            .dst = 0,
            .immediate = 45,
        },
        .name = "ALU mul imm",
    },
    {
        .instruction = {
            .opcode = 0x79,
            .dst = 0,
            .src = 10,
            .offset = -16,
        },
        .name = "MEM ldxdw",
    },
    {
        .instruction = {
            .opcode = 0x7a,
            .dst = 10,
            .offset = -16,
            .immediate = 45,
        },
        .name = "MEM stdw",
    },
    {
        .instruction = {
            .opcode = 0x7b,
            .dst = 10,
            .src = 0,
            .offset = -8,
        },
        .name = "MEM stxdw",
    },
    {
        .instruction = {
            .opcode = 0x05,
            .offset = 0,
        },
        .name = "Branch always",
    },
    {
        .instruction = {
            .opcode = 0x1d,
            .offset = 0,
            .dst = 10,
            .src = 10,
        },
        .name = "Branch eq (jump)",
    },
    {
        .instruction = {
            .opcode = 0x1d,
            .offset = 0,
            .dst = 0,
            .src = 10,
        },
        .name = "Branch eq (cont)",
    },
};

static test_application_t test_app;

int main(void)
{
    printf("| %-16s | %-8s | %-6s | %-6s | %-16s |\n",
           "Test", "duration", "code", "us/instr", "instr per sec");
    for (size_t test_idx = 0; test_idx < ARRAY_SIZE(tests); test_idx++) {
#if BPF_COQ
       struct memory_regions init_memory_regions = {
            .bpf_ctx = &init_memory_region0,
            .bpf_stk = &init_memory_region1,
            .content = &init_memory_region2
       };
       init_memory_region1.start_addr = (intptr_t)_bpf_stack;
       struct bpf_state st = {
            .state_pc = 0LLU,
            .regsmap = {0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU, (intptr_t)_bpf_stack},
            .bpf_flag = BPF_OK,
            .mrs = &init_memory_regions
       };
#else
        bpf_t bpf = {
            .application = (uint8_t*)&test_app,
            .application_len = sizeof(test_app),
            .stack = _bpf_stack,
            .stack_size = sizeof(_bpf_stack),
            .flags = BPF_FLAG_PREFLIGHT_DONE,
        };
        bpf_setup(&bpf);
        int64_t res = 0;
#endif
        fill_instruction(&tests[test_idx].instruction, &test_app);

        uint32_t begin = ztimer_now(ZTIMER_USEC); // unsigned long long -> uint64_t
#if BPF_COQ
        int result = bpf_interpreter(&st, test_app.text, sizeof(test_app.text), 10000);
#else
        int result = bpf_execute_ctx(&bpf, NULL, 0, &res);
#endif
        uint32_t end = ztimer_now(ZTIMER_USEC);
        float duration = (float)(end-begin);
        float us_per_op = duration/NUM_INSTRUCTIONS;
        float kops_per_sec = (float)(NUM_INSTRUCTIONS*US_PER_MS) / duration;
        printf("| %-16s | %2.4fms | %6d | %2.4fus | %7.2f kops/sec |\n",
                tests[test_idx].name,
                duration/US_PER_MS, (signed)result, us_per_op, kops_per_sec);
    }

    return 0;
}
