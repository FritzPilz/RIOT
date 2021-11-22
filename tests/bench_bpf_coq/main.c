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

#include "interpreter.h"
#include "fletcher32_bpf.h"

static const unsigned char wrap_around_data[] =
        "AD3Awn4kb6FtcsyE0RU25U7f55Yncn3LP3oEx9Gl4qr7iDW7I8L6Pbw9jNnh0sE4DmCKuc"
        "d1J8I34vn31W924y5GMS74vUrZQc08805aj4Tf66HgL1cO94os10V2s2GDQ825yNh9Yuq3"
        "QHcA60xl31rdA7WskVtCXI7ruH1A4qaR6Uk454hm401lLmv2cGWt5KTJmr93d3JsGaRRPs"
        "4HqYi4mFGowo8fWv48IcA3N89Z99nf0A0H2R6P0uI4Tir682Of3Rk78DUB2dIGQRRpdqVT"
        "tLhgfET2gUGU65V3edSwADMqRttI9JPVz8JS37g5QZj4Ax56rU1u0m0K8YUs57UYG5645n"
        "byNy4yqxu7";

struct fletcher32_ctx {
  const unsigned short * data;
  unsigned int words;
};

struct fletcher32_ctx f32_ctx = {
  .data = (const unsigned short *) wrap_around_data,
  .words = sizeof(wrap_around_data)/2,
};

static void bpf_add_region_ctx(struct bpf_state* st){
  (*(*((*st).mrs)).bpf_ctx).start_addr = (intptr_t) &f32_ctx;
  (*(*((*st).mrs)).bpf_ctx).block_size = sizeof(f32_ctx);
}

void bpf_add_region_content(struct bpf_state* st){
  (*(*((*st).mrs)).content).start_addr = (intptr_t) (const uint16_t *)wrap_around_data;
  (*(*((*st).mrs)).content).block_size = sizeof(wrap_around_data);
}


static void tests_bpf_run1(void)
{
    printf("Hello rBPF_fletcher32 C code Testing:\n");
    printf ("fletcher32 start!!! \n");
    unsigned long long result;
    // adding memory_regions
    static struct memory_region init_memory_region0 = {.start_addr = 0LLU, .block_size = 0LLU };
    static struct memory_region init_memory_region1 = {.start_addr = 0LLU, .block_size = 0LLU };
    static struct memory_region init_memory_region2 = {.start_addr = 0LLU, .block_size = 0LLU };

    static struct memory_regions init_memory_regions = {
      .bpf_ctx = &init_memory_region0,
      .bpf_stk = &init_memory_region1,
      .content = &init_memory_region2
    };

    struct bpf_state st = {
      .state_pc = 0LLU,
      .regsmap = {0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU, 0LLU},
      .bpf_flag = BPF_OK,
      .mrs = &init_memory_regions
    };

    bpf_add_region_ctx(&st);
    bpf_add_region_content(&st);

    uint32_t begin1 = ztimer_now(ZTIMER_USEC);
    result = bpf_interpreter(&st, (unsigned long long *) bpf_fletcher32_bpf_bin, sizeof(bpf_fletcher32_bpf_bin), 10000);
    uint32_t end1 = ztimer_now(ZTIMER_USEC);

    printf("rBPF_fletcher32 (dx) C result = 0x:%x\n", (unsigned int)result);
    printf ("fletcher32 end!!! \n");

    printf("Result: %"PRIx32"\n", (uint32_t)result);
    printf("execution time: %f ms\n", (float)(end1-begin1)/US_PER_MS);

    TEST_ASSERT_EQUAL_INT(0x5bac8c3d, (uint32_t)result);
}

Test *tests_bpf(void)
{
    EMB_UNIT_TESTFIXTURES(fixtures) {
        new_TestFixture(tests_bpf_run1),
    };

    EMB_UNIT_TESTCALLER(bpf_tests, NULL, NULL, fixtures);
    return (Test*)&bpf_tests;
}

int main(void)
{
    TESTS_START();
    TESTS_RUN(tests_bpf());
    TESTS_END();

    return 0;
}
