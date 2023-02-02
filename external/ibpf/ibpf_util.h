
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

void ibpf_full_state_init(ibpf_full_state_t *state);

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
