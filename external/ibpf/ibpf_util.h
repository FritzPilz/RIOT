
#ifndef IBPF_UTIL_H
#define IBPF_UTIL_H

#include <string.h>
#include "ibpf_interpreter.h"


typedef struct {
    uint8_t stack[512];
    unsigned bpf_flag;
    uint64_t bpf_regs_map[11];
    __attribute((aligned(4))) unsigned short jitted_thumb_list[JITTED_LIST_MAX_LENGTH];
    unsigned int entry_point_list[ENTRY_POINT_MAX_LENGTH];
    unsigned short thumb_list[JITTED_LIST_MAX_LENGTH];
    unsigned int bpf_load_store_regs[11];
    struct memory_region mrs[2];
    struct jit_state st;
} ibpf_full_state_t;


static inline void ibpf_full_state_init(ibpf_full_state_t *state)
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
}

static inline void ibpf_set_mem_region(ibpf_full_state_t *state, void *ptr, size_t len, unsigned perm)
{
    state->mrs[1].start_addr = (uintptr_t)ptr;
    state->mrs[1].block_size = len;
    state->mrs[1].block_perm = perm;
    state->mrs[1].block_ptr = ptr;
}

static inline void ibpf_set_code(ibpf_full_state_t *state, void *ptr, size_t len)
{
    state->st.ibpf = ptr;
    state->st.ins_len = len/8;
}

#endif /* IBPF_UTIL_H */
