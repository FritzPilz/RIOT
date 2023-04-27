/*
 * Copyright (C) 2023 Inria
 * Copyright (C) 2023 Koen Zandberg <koen@bergzand.net>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */
#include "ibpf_util.h"
#include <stddef.h>

uint16_t *jitted_thumb_list;

__attribute__ ((noinline)) void _magic_function(unsigned int ofs, struct jit_state* st){
  int res = 0;
  // disables some compiler optimizations
  __asm volatile (
    "orr %[input_0], #0x1\n\t"
    "mov r12, sp\n\t"
    "sub sp, sp, #48\n\t"
    "str r12, [sp, #0]\n\t"
    "mov pc, %[input_0]\n\t"
    : [result] "=r" (res)
    : [input_1] "r" (st), [input_0] "r" (jitted_thumb_list + ofs)
    : "cc" //The instruction modifies the condition code flags
  );
  return ;
}

void ibpf_full_state_init(ibpf_full_state_t *state)
{
    memset(state, 0, sizeof(ibpf_full_state_t));
    state->bpf_flag = vBPF_OK;
    state->st.flag = &state->bpf_flag;
    state->st.regs_st = state->bpf_regs_map;
    state->st.mrs_num = 2;
    state->st.bpf_mrs = state->mrs;
    state->st.ep_list = state->entry_point_list;
    state->st.load_store_regs = state->bpf_load_store_regs;
    state->st.thumb = state->thumb_list;
    state->st.jitted_list = state->jitted_thumb_list;

    state->mrs[0].start_addr = (uintptr_t)state->stack;
    state->mrs[0].block_size = 512;
    state->mrs[0].block_perm = Writable;
    state->mrs[0].block_ptr = state->stack;
    jitted_thumb_list = state->jitted_thumb_list;
}

