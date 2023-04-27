/**************************************************************************/
/*  This file is part of CertrBPF,                                        */
/*  a formally verified rBPF verifier + interpreter + JIT in Coq.         */
/*                                                                        */
/*  Copyright (C) 2022 Inria                                              */
/*                                                                        */
/*  This program is free software; you can redistribute it and/or modify  */
/*  it under the terms of the GNU General Public License as published by  */
/*  the Free Software Foundation; either version 2 of the License, or     */
/*  (at your option) any later version.                                   */
/*                                                                        */
/*  This program is distributed in the hope that it will be useful,       */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/*  GNU General Public License for more details.                          */
/*                                                                        */
/**************************************************************************/

#include "ibpf_interpreter.h"
#include "fmt.h"


void print_reg (unsigned int r) {
  printf("R%d ", r);
  return ;
}

void print_bpf_insstruction (unsigned long long ins){
  unsigned int op, dst, src;
  int imm, ofs;
  op  = (unsigned int) ins & 255LLU;
  dst = (unsigned int) ((ins & 4095LLU) >> 8LLU);
  src = (unsigned int) ((ins & 65535LLU) >> 12LLU);
  imm = (int) (ins >> 32LLU);
  ofs = (int) (short) (ins << 32LLU >> 48LLU);
  switch (op) {
    //alu64
    case 0x07:
      printf("bpf_add64 "); print_reg(dst); printf("%d", imm); return ;
    case 0x17:
      printf("bpf_sub64 "); print_reg(dst); printf("%d", imm); return ;
    case 0x27:
      printf("bpf_mul64 "); print_reg(dst); printf("%d", imm); return ;
    case 0x37:
      printf("bpf_div64 "); print_reg(dst); printf("%d", imm); return ;
    case 0x47:
      printf("bpf_or64  "); print_reg(dst); printf("%d", imm); return ;
    case 0x57:
      printf("bpf_and64 "); print_reg(dst); printf("%d", imm); return ;
    case 0x67:
      printf("bpf_lsh64 "); print_reg(dst); printf("%d", imm); return ;
    case 0x77:
      printf("bpf_rsh64 "); print_reg(dst); printf("%d", imm); return ;
    case 0x87:
      printf("bpf_neg64 "); print_reg(dst); printf("%d", imm); return ;
    case 0x97:
      printf("bpf_mod64 "); print_reg(dst); printf("%d", imm); return ;
    case 0xa7:
      printf("bpf_xor64 "); print_reg(dst); printf("%d", imm); return ;
    case 0xb7:
      printf("bpf_mov64 "); print_reg(dst); printf("%d", imm); return ;
    case 0xc7:
      printf("bpf_arsh64 "); print_reg(dst); printf("%d", imm); return ;

    case 0x0f:
      printf("bpf_add64 "); print_reg(dst); print_reg(src); return ;
    case 0x1f:
      printf("bpf_sub64 "); print_reg(dst); print_reg(src); return ;
    case 0x2f:
      printf("bpf_mul64 "); print_reg(dst); print_reg(src); return ;
    case 0x3f:
      printf("bpf_div64 "); print_reg(dst); print_reg(src); return ;
    case 0x4f:
      printf("bpf_or64  "); print_reg(dst); print_reg(src); return ;
    case 0x5f:
      printf("bpf_and64 "); print_reg(dst); print_reg(src); return ;
    case 0x6f:
      printf("bpf_lsh64 "); print_reg(dst); print_reg(src); return ;
    case 0x7f:
      printf("bpf_rsh64 "); print_reg(dst); print_reg(src); return ;
    case 0x9f:
      printf("bpf_mod64 "); print_reg(dst); print_reg(src); return ;
    case 0xaf:
      printf("bpf_xor64 "); print_reg(dst); print_reg(src); return ;
    case 0xbf:
      printf("bpf_mov64 "); print_reg(dst); print_reg(src); return ;
    case 0xcf:
      printf("bpf_arsh64 "); print_reg(dst); print_reg(src); return ;

    //alu32
    case 0x04:
      printf("bpf_add32 "); print_reg(dst); printf("%d", imm); return ;
    case 0x14:
      printf("bpf_sub32 "); print_reg(dst); printf("%d", imm); return ;
    case 0x24:
      printf("bpf_mul32 "); print_reg(dst); printf("%d", imm); return ;
    case 0x34:
      printf("bpf_div32 "); print_reg(dst); printf("%d", imm); return ;
    case 0x44:
      printf("bpf_or32  "); print_reg(dst); printf("%d", imm); return ;
    case 0x54:
      printf("bpf_and32 "); print_reg(dst); printf("%d", imm); return ;
    case 0x64:
      printf("bpf_lsh32 "); print_reg(dst); printf("%d", imm); return ;
    case 0x74:
      printf("bpf_rsh32 "); print_reg(dst); printf("%d", imm); return ;
    case 0x84:
      printf("bpf_neg32 "); print_reg(dst); printf("%d", imm); return ;
    case 0x94:
      printf("bpf_mod32 "); print_reg(dst); printf("%d", imm); return ;
    case 0xa4:
      printf("bpf_xor32 "); print_reg(dst); printf("%d", imm); return ;
    case 0xb4:
      printf("bpf_mov32 "); print_reg(dst); printf("%d", imm); return ;
    case 0xc4:
      printf("bpf_arsh32 "); print_reg(dst); printf("%d", imm); return ;
    case 0xd4:
      printf("bpf_jit "); printf("%d", ofs); printf(", %d", imm); return ;

    case 0x0c:
      printf("bpf_add32 "); print_reg(dst); print_reg(src); return ;
    case 0x1c:
      printf("bpf_sub32 "); print_reg(dst); print_reg(src); return ;
    case 0x2c:
      printf("bpf_mul32 "); print_reg(dst); print_reg(src); return ;
    case 0x3c:
      printf("bpf_div32 "); print_reg(dst); print_reg(src); return ;
    case 0x4c:
      printf("bpf_or32  "); print_reg(dst); print_reg(src); return ;
    case 0x5c:
      printf("bpf_and32 "); print_reg(dst); print_reg(src); return ;
    case 0x6c:
      printf("bpf_lsh32 "); print_reg(dst); print_reg(src); return ;
    case 0x7c:
      printf("bpf_rsh32 "); print_reg(dst); print_reg(src); return ;
    case 0x9c:
      printf("bpf_mod32 "); print_reg(dst); print_reg(src); return ;
    case 0xac:
      printf("bpf_xor32 "); print_reg(dst); print_reg(src); return ;
    case 0xbc:
      printf("bpf_mov32 "); print_reg(dst); print_reg(src); return ;
    case 0xcc:
      printf("bpf_arsh32 "); print_reg(dst); print_reg(src); return ;

    //memory
    case 0x10:
      printf("bpf_lddw_low "); print_reg(dst); printf("%d", imm); return ;
    case 0x18:
      printf("bpf_lddw_high "); print_reg(dst); printf("%d", imm); return ;

    case 0x61:
      printf("bpf_ldxw  "); print_reg(dst); printf(", ["); print_reg(src); printf("+ %d]", ofs); return ;
    case 0x69:
      printf("bpf_ldxh  "); print_reg(dst); printf(", ["); print_reg(src); printf("+ %d]", ofs); return ;
    case 0x71:
      printf("bpf_ldxb  "); print_reg(dst); printf(", ["); print_reg(src); printf("+ %d]", ofs); return ;
    case 0x79:
      printf("bpf_ldxdw "); print_reg(dst); printf(", ["); print_reg(src); printf("+ %d]", ofs); return ;

    case 0x62:
      printf("bpf_stw  "); printf("["); print_reg(dst); printf("+ %d]", ofs); printf(", %d", imm); return ;
    case 0x6a:
      printf("bpf_sth  "); printf("["); print_reg(dst); printf("+ %d]", ofs); printf(", %d", imm); return ;
    case 0x72:
      printf("bpf_stb  "); printf("["); print_reg(dst); printf("+ %d]", ofs); printf(", %d", imm); return ;
    case 0x7a:
      printf("bpf_stdw "); printf("["); print_reg(dst); printf("+ %d]", ofs); printf(", %d", imm); return ;

    case 0x63:
      printf("bpf_stxw  "); printf("["); print_reg(dst); printf("+ %d]", ofs); printf(", %d", imm); return ;
    case 0x6b:
      printf("bpf_stxh  "); printf("["); print_reg(dst); printf("+ %d]", ofs); printf(", %d", imm); return ;
    case 0x73:
      printf("bpf_stxb  "); printf("["); print_reg(dst); printf("+ %d]", ofs); printf(", %d", imm); return ;
    case 0x7b:
      printf("bpf_stxdw "); printf("["); print_reg(dst); printf("+ %d]", ofs); printf(", %d", imm); return ;

    //branch
    case 0x05:
      printf("bpf_ja "); printf(" +%d]", ofs); return ;

    case 0x15:
      printf("bpf_jeq "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;
    case 0x25:
      printf("bpf_jgt "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;
    case 0x35:
      printf("bpf_jge "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;
    case 0xa5:
      printf("bpf_jlt "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;
    case 0xb5:
      printf("bpf_jle "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;
    case 0x45:
      printf("bpf_jset "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;
    case 0x55:
      printf("bpf_jne "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;
    case 0x65:
      printf("bpf_jsgt "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;
    case 0x75:
      printf("bpf_jsge "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;
    case 0xc5:
      printf("bpf_jslt "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;
    case 0xd5:
      printf("bpf_jsle "); print_reg(dst); printf(", %d", imm);  printf(", +%d", ofs); return ;

    case 0x1d:
      printf("bpf_jeq "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;
    case 0x2d:
      printf("bpf_jgt "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;
    case 0x3d:
      printf("bpf_jge "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;
    case 0xad:
      printf("bpf_jlt "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;
    case 0xbd:
      printf("bpf_jle "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;
    case 0x4d:
      printf("bpf_jset "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;
    case 0x5d:
      printf("bpf_jne "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;
    case 0x6d:
      printf("bpf_jsgt "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;
    case 0x7d:
      printf("bpf_jsge "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;
    case 0xcd:
      printf("bpf_jslt "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;
    case 0xdd:
      printf("bpf_jsle "); print_reg(dst); printf(", "); print_reg(src);  printf(", +%d", ofs); return ;

    case 0x85:
      printf("bpf_call "); printf(" %d", imm); return ;
    case 0x95:
      printf("bpf_exit "); return ;
    default: printf("error: op = %x", op);
      return;

  }
}

void print_jit_state(struct jit_state* st){
  printf("pc= %02d flag= %d\n",  (*st).pc_loc, (*st).flag);
    print_u64_dec((*st).regs_st[0]);
    printf("(R0)\n");
    print_u64_dec((*st).regs_st[1]);
    printf("(R1)\n");
    print_u64_dec((*st).regs_st[2]);
    printf("(R2)\n");
    print_u64_dec((*st).regs_st[3]);
    printf("(R3)\n");
    print_u64_dec((*st).regs_st[4]);
    printf("(R4)\n");
    print_u64_dec((*st).regs_st[5]);
    printf("(R5)\n");
    print_u64_dec((*st).regs_st[6]);
    printf("(R6)\n");
    print_u64_dec((*st).regs_st[7]);
    printf("(R7)\n");
    print_u64_dec((*st).regs_st[8]);
    printf("(R8)\n");
    print_u64_dec((*st).regs_st[9]);
    printf("(R9)\n");
    print_u64_dec((*st).regs_st[10]);
    printf("(R10)\n");
  return ;
}


void print_load_store_regs(struct jit_state* st){
  for(unsigned i = 0; i < 11; i++){
    printf("R%d",i);
    if ((*st).load_store_regs[i] == 0) {
      printf("_perm = NonPerm; ");
    } else if ((*st).load_store_regs[i] == 1) {
      printf("_perm = LoadPerm; ");
    } else if ((*st).load_store_regs[i] == 2) {
      printf("_perm = StorePerm; ");
    } else if ((*st).load_store_regs[i] == 3) {
      printf("_perm = LoadStorePerm; ");
    } else {
      printf("_perm = Undef; ");
    }
  }
  printf("\n");

  return ;
}

void print_thumb(struct jit_state* st){
  printf("thumb list: ");
  for(unsigned i = 0; i < (*st).thumb_len; i++) {
    printf("%x: %u; ", i, (*st).thumb[i]);
    if ((i+1)%8 == 0) { printf("\n"); }
  }
  printf("\n");
  return ;
}

void print_ibpf(struct jit_state* st){
  printf("ibpf list: ");
  for(unsigned i = 0; i < (*st).ins_len; i++) {
    print_bpf_insstruction((*st).jit_ins[i]);
    printf("(%d)\n", i);
  }
  printf("\n");
  return ;
}

void print_jitted_arm(struct jit_state* st){
  printf("jitted thumb list: ");
  for(unsigned i = 0; i < (*st).jitted_len; i++) {
    printf("0x%x: 0x%x\n ", i, (*st).jitted_list[i]);
    //if ((i+1)%8 == 0) { printf("\n"); }
  }
  printf("\n");
  return ;
}

void print_jit_state_all(struct jit_state* st){
  print_jit_state(st);
  print_ibpf(st);
  print_load_store_regs(st);
  print_jitted_arm(st);
  return ;
}

static __attribute__((always_inline)) inline unsigned int eval_pc (struct jit_state* st) {
  return (*st).pc_loc;
}

static __attribute__((always_inline)) inline void upd_pc(struct jit_state* st, unsigned int pc) {
  (*st).pc_loc = pc;
  return ;
}
static __attribute__((always_inline)) inline void upd_pc_incr(struct jit_state* st) {
  (*st).pc_loc = (*st).pc_loc+1;
  return ;
}


static __attribute__((always_inline)) inline unsigned long long eval_reg(struct jit_state* st, unsigned int i){
  return (*st).regs_st[i];
}

static __attribute__((always_inline)) inline void upd_reg (struct jit_state* st, unsigned int i, unsigned long long v){
  (*st).regs_st[i] = v;
  return ;
}

static __attribute__((always_inline)) inline unsigned eval_flag(struct jit_state* st){
  return (*st).flag;
}

static __attribute__((always_inline)) inline void upd_flag(struct jit_state* st, unsigned f){
  (*st).flag = f;
  return ;
}

static __attribute__((always_inline)) inline unsigned int eval_mrs_num(struct jit_state* st){
  return (*st).mrs_num;
}

static __attribute__((always_inline)) inline struct memory_region *eval_mrs_regions(struct jit_state* st){
  return (*st).bpf_mrs;
}


static __attribute__((always_inline)) inline unsigned long long load_mem(struct jit_state* st, unsigned int chunk, unsigned char* addr){
  switch (chunk) {
    case 1: return *(unsigned char *) addr;
    case 2: return *(unsigned short *) addr;
    case 4: return *(unsigned int *) addr;
    case 8: return *(unsigned long long *) addr;
    default: /*printf ("load:addr = %" PRIu64 "\n", v); (*st).flag = BPF_ILLEGAL_MEM;*/ return 0LLU;
  }
}

static __attribute__((always_inline)) inline void store_mem_reg(struct jit_state* st, unsigned char* addr, unsigned int chunk, unsigned long long v){
  switch (chunk) {
    case 1: *(unsigned char *) addr = v; return ;
    case 2: *(unsigned short *) addr = v; return ;
    case 4: *(unsigned int *) addr = v; return ;
    case 8: *(unsigned long long *) addr = v; return ;
    default: /*printf ("store_reg:addr = %" PRIu64 "\n", addr); (*st).flag = BPF_ILLEGAL_MEM;*/ return ;
  }
}

static __attribute__((always_inline)) inline void store_mem_imm(struct jit_state* st, unsigned char* addr, unsigned int chunk, int v){
  switch (chunk) {
    case 1: *(unsigned char *) addr = v; return ;
    case 2: *(unsigned short *) addr = v; return ;
    case 4: *(unsigned int *) addr = v; return ;
    case 8: *(unsigned long long *) addr = v; return ;
    default: /*printf ("store_imm:addr = %" PRIu64 "\n", addr); (*st).flag = BPF_ILLEGAL_MEM;*/ return ;
  }
}

static __attribute__((always_inline)) inline unsigned int eval_ins_len(struct jit_state* st)
{
  return (*st).ins_len;
}

static __attribute__((always_inline)) inline unsigned long long eval_ins(struct jit_state* st, unsigned int idx)
{ //print_jit_state(st);
  return *((*st).jit_ins + idx);
}

static __attribute__((always_inline)) inline _Bool cmp_ptr32_nullM(unsigned char* addr){
   return (addr == 0);
}

static __attribute__((always_inline)) inline unsigned int get_dst(unsigned long long ins)
{
  return (unsigned int) ((ins & 4095LLU) >> 8LLU);
}

static __attribute__((always_inline)) inline unsigned int get_src(unsigned long long ins)
{
  return (unsigned int) ((ins & 65535LLU) >> 12LLU);
}

static __attribute__((always_inline)) inline struct memory_region *get_mem_region(unsigned int n, struct memory_region *mrs)
{
  return mrs + n;
}

static __attribute__((always_inline)) inline unsigned char *_bpf_get_call(int imm) {
  /* deleting `return NULL;` and adding your system APIs
  switch (imm) {
    default: return ...
  }
  */
  return NULL;
}

static __attribute__((always_inline)) inline unsigned int exec_function(struct jit_state* st, unsigned char * ptr){
  if (ptr == 0){
    (*st).flag = vBPF_ILLEGAL_CALL;
    return 0U;
  }
  else {
    /**do something e.g. print; */
    return 0U;
  }
}

static __attribute__((always_inline)) inline void upd_IR11_jittedthumb(struct jit_state* st, _Bool f){
  (*st).use_IR11 = f;
  return ;
}

static __attribute__((always_inline)) inline void add_ins_jittedthumb(struct jit_state* st, unsigned int ins){
  if ((*st).ins_len < JITTED_LIST_MAX_LENGTH){
    (*st).thumb[(*st).thumb_len] = ins;
    (*st).thumb_len = (*st).thumb_len + 1U;
    return ;
  }
  else {
    (*st).flag = vBPF_ILLEGAL_ARM_LEN; return ;
  }
}

static __attribute__((always_inline)) inline void upd_bpf_offset_jittedthumb(struct jit_state* st){
  (*st).offset = (*st).offset + 1U;
  return ;
}

static __attribute__((always_inline)) inline void upd_load_store_regs_jittedthumb(struct jit_state* st, unsigned int r, unsigned int ls){
  unsigned int history;
  history = (*st).load_store_regs[r];
  if (ls == LoadPerm) {
    if ((history == NonPerm) || (history == LoadPerm)) {
      (*st).load_store_regs[r] = LoadPerm;
    }
    else if (history == StorePerm) {
      (*st).load_store_regs[r] = StorePerm;
    }
    else if (history == LoadAndStore) {
      (*st).load_store_regs[r] = LoadAndStore;
    }
  }
  else if (ls == StorePerm) {
    if (history == NonPerm) {
      (*st).load_store_regs[r] = StorePerm;
    }
    else if (history == LoadPerm) {
      (*st).load_store_regs[r] = LoadAndStore;
    }
    else if (history == StorePerm) {
      (*st).load_store_regs[r] = StorePerm;
    }
    else if (history == LoadAndStore) {
      (*st).load_store_regs[r] = LoadAndStore;
    }
  }
  else if (ls == LoadAndStore) {
    if (history == NonPerm) {
      (*st).load_store_regs[r] = LoadAndStore;
    }
    else if (history == LoadPerm) {
      (*st).load_store_regs[r] = LoadAndStore;
    }
    else if (history == StorePerm) {
      (*st).load_store_regs[r] = StorePerm;
    }
    else if (history == LoadAndStore) {
      (*st).load_store_regs[r] = LoadAndStore;
    }
  }
  return ;
}

static __attribute__((always_inline)) inline void upd_thumb_jittedthumb(struct jit_state* st, unsigned int ins, unsigned int pc){
  (*st).thumb[pc] = ins;
  return ;
}

static __attribute__((always_inline)) inline void upd_jitted_list(struct jit_state* st, unsigned int ins){
  (*st).jitted_list[(*st).jitted_len] = ins;
  (*st).jitted_len = (*st).jitted_len + 1U;
  return ;
}


static __attribute__((always_inline)) inline void magic_function(struct jit_state* st, unsigned int ofs){
  //_magic_function is user-defined or compcert build-in
  // for user-defined, we swapped the order to make sure r0 is the start address of jitted_list while r1 is the start address of jit_state.
  _magic_function(ofs, st);
  return ;
}

static __attribute__((always_inline)) inline _Bool eval_use_IR11(struct jit_state* st){
  return (*st).use_IR11;
}

static __attribute__((always_inline)) inline unsigned int eval_offset(struct jit_state* st){
  return (*st).offset;
}

static __attribute__((always_inline)) inline unsigned int eval_thumb_len(struct jit_state* st){
  return (*st).thumb_len;
}

static __attribute__((always_inline)) inline unsigned int eval_jitted_len(struct jit_state* st){
  return (*st).jitted_len;
}

static __attribute__((always_inline)) inline _Bool is_non_reg(struct jit_state* st, unsigned int r){
  return (*st).load_store_regs[r] == 0U;
}

static __attribute__((always_inline)) inline _Bool is_load_reg(struct jit_state* st, unsigned int r){
  return ((*st).load_store_regs[r] == 1U) || ((*st).load_store_regs[r] == 3U);
}

static __attribute__((always_inline)) inline _Bool is_store_reg(struct jit_state* st, unsigned int r){
  return ((*st).load_store_regs[r] == 2U) || ((*st).load_store_regs[r] == 3U);
}

// a recursion implementation of power2 to replace pow(2, _) from math.h because CompCert doesn't support math.h
static __attribute__((always_inline)) inline unsigned int power2(unsigned int width){
  if (width == 0U) {
    return 1U;
  }
  else {
    return 2U * power2(width - 1U);
  }
}

static __attribute__((always_inline)) inline unsigned int decode_thumb(unsigned int ins, unsigned int from, unsigned int size){
  return ( (ins >> from) & (power2(size) - 1U) );
}

static __attribute__((always_inline)) inline unsigned int encode_thumb(unsigned int v, unsigned int ins, unsigned int from, unsigned int size){
  unsigned int mask;
  mask = (power2(size) - 1U) << from;
  return ( ((v & (power2(size) - 1U)) << from) | (ins & (~mask)) );
}

static __attribute__((always_inline)) inline unsigned int reg_of_ireg(unsigned int ir){
  return ir;
}

static __attribute__((always_inline)) inline unsigned char opcode_reg_of_imm(unsigned char op){
  switch (op) {
    case 4:
      return 12;
    case 20:
      return 28;
    case 36:
      return 44;
    case 68:
      return 76;
    case 84:
      return 92;
    case 164:
      return 172;
    case 180:
      return 188;
    default:
      return 0;
  }
}

static __attribute__((always_inline)) inline unsigned int eval_thumb_ins(struct jit_state* st, unsigned int idx){
  return *((*st).thumb + idx);
}

static __attribute__((always_inline)) inline _Bool ins_is_bpf_alu32(unsigned long long ins){
  unsigned char op;
  op = (unsigned char) (ins & 255LLU);
  return (op == 4) || (op == 12) ||
  	 (op == 20) || (op == 28) ||
  	 (op == 36) || (op == 44) ||
  	 (op == 60) ||
  	 (op == 68) || (op == 76) ||
  	 (op == 84) || (op == 92) ||
  	 (op == 108) || (op == 124) ||
  	 (op == 132) ||
  	 (op == 164) || (op == 172) ||
  	 (op == 180) || (op == 188) ||
  	 (op == 204);
}
static __attribute__((always_inline)) inline _Bool ins_is_bpf_jump(unsigned long long ins){
  unsigned char op;
  op = (unsigned char) (ins & 255LLU);
  return (op == 5) ||
  	 (op == 21) || (op == 29) ||
  	 (op == 37) || (op == 45) ||
  	 (op == 53) || (op == 61) ||
  	 (op == 69) || (op == 77) ||
  	 (op == 85) || (op == 93) ||
  	 (op == 101) || (op == 109) ||
  	 (op == 117) || (op == 125) ||
  	 (op == 165) || (op == 173) ||
  	 (op == 181) || (op == 189) ||
  	 (op == 197) || (op == 205) ||
  	 (op == 213) || (op == 221);

}

static __attribute__((always_inline)) inline void reset_init_jittedthumb(struct jit_state* st){
  (*st).use_IR11 = 0;
  for (int i = 0; i < 11; i ++) { (*st).load_store_regs[i] = NonPerm; }
  (*st).offset = 0U;
  (*st).thumb_len = 0U;
  return ;
}

static __attribute__((always_inline)) inline unsigned int eval_key_value2_arm_ofs(struct jit_state* st, unsigned int key){
  return (*st).kv2[key].arm_ofs;
}

static __attribute__((always_inline)) inline unsigned int eval_key_value2_alu32_ofs(struct jit_state* st, unsigned int key){
  return (*st).kv2[key].alu32_ofs;
}

static __attribute__((always_inline)) inline void add_key_value2(struct jit_state* st, unsigned int pc, unsigned int ofs0, unsigned int ofs1){
  (*st).kv2[pc].arm_ofs = ofs0;
  (*st).kv2[pc].alu32_ofs = ofs1;
  return ;
}

/*******************below code are automatically generated by dx (after repatch) ***************************/

static __attribute__((always_inline)) inline unsigned short construct_thumb_b(unsigned short cd, unsigned short imm8)
{
  unsigned int ins_imm8;
  ins_imm8 = encode_thumb(imm8, 53248, 0U, 8U);
  return encode_thumb(cd, ins_imm8, 8U, 4U);
}

static __attribute__((always_inline)) inline unsigned short construct_thumb2_shift_rd_rm(unsigned short rd, unsigned short rm)
{
  unsigned int ins_rd;
  ins_rd = encode_thumb(rd, rm, 8U, 4U);
  return encode_thumb(15, ins_rd, 12U, 4U);
}

static __attribute__((always_inline)) inline void jit_alu32_thumb_store_template_jit(struct jit_state* st, unsigned short rt, unsigned short rn, unsigned short imm12)
{
  unsigned int str_low;
  unsigned int str_high;
  str_low = encode_thumb(rn, 63680, 0U, 4U);
  str_high = encode_thumb(rt, imm12, 12U, 4U);
  upd_jitted_list(st, str_low);
  upd_jitted_list(st, str_high);
  return;
}

static __attribute__((always_inline)) inline void jit_alu32_thumb_load_template_jit(struct jit_state* st, unsigned short rt, unsigned short rn, unsigned short imm12)
{
  unsigned int str_low;
  unsigned int str_high;
  str_low = encode_thumb(rn, 63696, 0U, 4U);
  str_high = encode_thumb(rt, imm12, 12U, 4U);
  upd_jitted_list(st, str_low);
  upd_jitted_list(st, str_high);
  return;
}

static __attribute__((always_inline)) inline int get_offset(unsigned long long ins)
{
  return (int) (short) (ins << 32LLU >> 48LLU);
}

static __attribute__((always_inline)) inline void jit_alu32_pre(struct jit_state* st)
{
  unsigned int ins_rdn;
  unsigned int ins_rm;
  unsigned int ins_mov;
  ins_rdn = encode_thumb(4, 17920, 0U, 3U);
  ins_rm = encode_thumb(1, ins_rdn, 3U, 4U);
  ins_mov = encode_thumb(1, ins_rm, 7U, 1U);
  upd_jitted_list(st, ins_mov);
  return;
}

static __attribute__((always_inline)) inline void jit_alu32_thumb_upd_save(struct jit_state* st, unsigned int r)
{
  _Bool b;
  b = is_non_reg(st, r);
  if (b) {
    return;
  } else {
    jit_alu32_thumb_store_template_jit(st, r, 13U, r * 4);
    return;
  }
}

static __attribute__((always_inline)) inline void jit_alu32_thumb_save(struct jit_state* st)
{
  _Bool b;
  jit_alu32_thumb_upd_save(st, 4U);
  jit_alu32_thumb_upd_save(st, 5U);
  jit_alu32_thumb_upd_save(st, 6U);
  jit_alu32_thumb_upd_save(st, 7U);
  jit_alu32_thumb_upd_save(st, 8U);
  jit_alu32_thumb_upd_save(st, 9U);
  jit_alu32_thumb_upd_save(st, 10U);
  b = eval_use_IR11(st);
  if (b) {
    jit_alu32_thumb_store_template_jit(st, 11, 13U, 44);
    return;
  } else {
    return;
  }
}

static __attribute__((always_inline)) inline void jit_alu32_thumb_upd_load(struct jit_state* st, unsigned int r)
{
  _Bool b;
  b = is_load_reg(st, r);
  if (b) {
    jit_alu32_thumb_load_template_jit(st, r, 12, r * 8 + 8);
    return;
  } else {
    return;
  }
}

static __attribute__((always_inline)) inline _Bool no_reg_load(struct jit_state* st)
{
  _Bool b0;
  _Bool b1;
  _Bool b2;
  _Bool b3;
  _Bool b4;
  _Bool b5;
  _Bool b6;
  _Bool b7;
  _Bool b8;
  _Bool b9;
  _Bool b10;
  b0 = is_load_reg(st, 0U);
  if (b0) {
    return 0;
  } else {
    b1 = is_load_reg(st, 1U);
    if (b1) {
      return 0;
    } else {
      b2 = is_load_reg(st, 2U);
      if (b2) {
        return 0;
      } else {
        b3 = is_load_reg(st, 3U);
        if (b3) {
          return 0;
        } else {
          b4 = is_load_reg(st, 4U);
          if (b4) {
            return 0;
          } else {
            b5 = is_load_reg(st, 5U);
            if (b5) {
              return 0;
            } else {
              b6 = is_load_reg(st, 6U);
              if (b6) {
                return 0;
              } else {
                b7 = is_load_reg(st, 7U);
                if (b7) {
                  return 0;
                } else {
                  b8 = is_load_reg(st, 8U);
                  if (b8) {
                    return 0;
                  } else {
                    b9 = is_load_reg(st, 9U);
                    if (b9) {
                      return 0;
                    } else {
                      b10 = is_load_reg(st, 10U);
                      if (b10) {
                        return 0;
                      } else {
                        return 1;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

static __attribute__((always_inline)) inline void jit_alu32_thumb_load(struct jit_state* st)
{
  _Bool b;
  b = no_reg_load(st);
  if (b) {
    return;
  } else {
    jit_alu32_thumb_upd_load(st, 10U);
    jit_alu32_thumb_upd_load(st, 9U);
    jit_alu32_thumb_upd_load(st, 8U);
    jit_alu32_thumb_upd_load(st, 7U);
    jit_alu32_thumb_upd_load(st, 6U);
    jit_alu32_thumb_upd_load(st, 5U);
    jit_alu32_thumb_upd_load(st, 4U);
    jit_alu32_thumb_upd_load(st, 3U);
    jit_alu32_thumb_upd_load(st, 2U);
    jit_alu32_thumb_upd_load(st, 1U);
    jit_alu32_thumb_upd_load(st, 0U);
    return;
  }
}

static __attribute__((always_inline)) inline void bpf_alu32_to_thumb_reg(struct jit_state* st, unsigned char op, unsigned int dst, unsigned int src)
{
  unsigned int d;
  unsigned int rdn;
  unsigned int ins_rdn;
  unsigned int ins_rm;
  unsigned int ins;
  unsigned int r;
  unsigned int ins_lo;
  unsigned int ins_hi;
  unsigned int ins_hi0;
  unsigned int lsl_lo;
  unsigned short lsl_hi;
  unsigned int lsr_lo;
  unsigned short lsr_hi;
  unsigned int asr_lo;
  unsigned short asr_hi;
  switch (op) {
    case 12:
      if (dst < 8) {
        d = 0;
      } else {
        d = 1;
      }
      if (dst < 8) {
        rdn = dst;
      } else {
        rdn = dst - 8;
      }
      ins_rdn = encode_thumb(rdn, 17408, 0U, 3U);
      ins_rm = encode_thumb(src, ins_rdn, 3U, 4U);
      ins = encode_thumb(d, ins_rm, 7U, 1U);
      add_ins_jittedthumb(st, ins);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      if (src == 11U) {
        return;
      } else {
        r = reg_of_ireg(src);
        upd_load_store_regs_jittedthumb(st, r, 1U);
        return;
      }
    case 28:
      ins_lo = encode_thumb(dst, 60320, 0U, 4U);
      ins_hi = encode_thumb(dst, src, 8U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      if (src == 11U) {
        return;
      } else {
        r = reg_of_ireg(src);
        upd_load_store_regs_jittedthumb(st, r, 1U);
        return;
      }
    case 44:
      ins_lo = encode_thumb(dst, 64256, 0U, 4U);
      ins_hi0 = encode_thumb(dst, src, 8U, 4U);
      ins_hi = encode_thumb(15, ins_hi0, 12U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      if (src == 11U) {
        return;
      } else {
        r = reg_of_ireg(src);
        upd_load_store_regs_jittedthumb(st, r, 1U);
        return;
      }
    case 60:
      if (dst == 0U && src == 1U) {
        add_ins_jittedthumb(st, 64432);
        add_ins_jittedthumb(st, 61681);
        upd_load_store_regs_jittedthumb(st, dst, 3U);
        if (src == 11U) {
          return;
        } else {
          r = reg_of_ireg(src);
          upd_load_store_regs_jittedthumb(st, r, 1U);
          return;
        }
      } else {
        upd_flag(st, 10U);
        return;
      }
    case 76:
      ins_lo = encode_thumb(dst, 59968, 0U, 4U);
      ins_hi = encode_thumb(dst, src, 8U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      if (src == 11U) {
        return;
      } else {
        r = reg_of_ireg(src);
        upd_load_store_regs_jittedthumb(st, r, 1U);
        return;
      }
    case 92:
      ins_lo = encode_thumb(dst, 59904, 0U, 4U);
      ins_hi = encode_thumb(dst, src, 8U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      if (src == 11U) {
        return;
      } else {
        r = reg_of_ireg(src);
        upd_load_store_regs_jittedthumb(st, r, 1U);
        return;
      }
    case 108:
      lsl_lo = encode_thumb(dst, 64000, 0U, 4U);
      lsl_hi = construct_thumb2_shift_rd_rm(dst, src);
      add_ins_jittedthumb(st, lsl_lo);
      add_ins_jittedthumb(st, lsl_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      if (src == 11U) {
        return;
      } else {
        r = reg_of_ireg(src);
        upd_load_store_regs_jittedthumb(st, r, 1U);
        return;
      }
    case 124:
      lsr_lo = encode_thumb(dst, 64032, 0U, 4U);
      lsr_hi = construct_thumb2_shift_rd_rm(dst, src);
      add_ins_jittedthumb(st, lsr_lo);
      add_ins_jittedthumb(st, lsr_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      if (src == 11U) {
        return;
      } else {
        r = reg_of_ireg(src);
        upd_load_store_regs_jittedthumb(st, r, 1U);
        return;
      }
    case 172:
      ins_lo = encode_thumb(dst, 60032, 0U, 4U);
      ins_hi = encode_thumb(dst, src, 8U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      if (src == 11U) {
        return;
      } else {
        r = reg_of_ireg(src);
        upd_load_store_regs_jittedthumb(st, r, 1U);
        return;
      }
    case 188:
      if (dst == src) {
        return;
      } else {
        if (dst < 8) {
          d = 0;
        } else {
          d = 1;
        }
        if (dst < 8) {
          rdn = dst;
        } else {
          rdn = dst - 8;
        }
        ins_rdn = encode_thumb(rdn, 17920, 0U, 3U);
        ins_rm = encode_thumb(src, ins_rdn, 3U, 4U);
        ins = encode_thumb(d, ins_rm, 7U, 1U);
        add_ins_jittedthumb(st, ins);
        upd_load_store_regs_jittedthumb(st, dst, 2U);
        if (src == 11U) {
          return;
        } else {
          r = reg_of_ireg(src);
          upd_load_store_regs_jittedthumb(st, r, 1U);
          return;
        }
      }
    case 204:
      asr_lo = encode_thumb(dst, 64064, 0U, 4U);
      asr_hi = construct_thumb2_shift_rd_rm(dst, src);
      add_ins_jittedthumb(st, asr_lo);
      add_ins_jittedthumb(st, asr_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      if (src == 11U) {
        return;
      } else {
        r = reg_of_ireg(src);
        upd_load_store_regs_jittedthumb(st, r, 1U);
        return;
      }
    default:
      upd_flag(st, 12U);
      return;

  }
}

static __attribute__((always_inline)) inline void bpf_alu32_to_thumb_imm(struct jit_state* st, unsigned char op, unsigned int dst, unsigned int imm8)
{
  unsigned int ins_lo;
  unsigned int ins_hi;
  switch (op) {
    case 4:
      ins_lo = encode_thumb(dst, 61696, 0U, 4U);
      ins_hi = encode_thumb(dst, imm8, 8U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      return;
    case 20:
      ins_lo = encode_thumb(dst, 61856, 0U, 4U);
      ins_hi = encode_thumb(dst, imm8, 8U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      return;
    case 36:
      upd_flag(st, 12U);
      return;
    case 68:
      ins_lo = encode_thumb(dst, 61504, 0U, 4U);
      ins_hi = encode_thumb(dst, imm8, 8U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      return;
    case 84:
      ins_lo = encode_thumb(dst, 61440, 0U, 4U);
      ins_hi = encode_thumb(dst, imm8, 8U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      return;
    case 132:
      ins_lo = encode_thumb(dst, 61888, 0U, 4U);
      ins_hi = encode_thumb(dst, 0U, 8U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      return;
    case 164:
      ins_lo = encode_thumb(dst, 61568, 0U, 4U);
      ins_hi = encode_thumb(dst, imm8, 8U, 4U);
      add_ins_jittedthumb(st, ins_lo);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 3U);
      return;
    case 180:
      ins_hi = encode_thumb(dst, imm8, 8U, 4U);
      add_ins_jittedthumb(st, 62016);
      add_ins_jittedthumb(st, ins_hi);
      upd_load_store_regs_jittedthumb(st, dst, 2U);
      return;
    default:
      upd_flag(st, 12U);
      return;

  }
}

static __attribute__((always_inline)) inline void mov_int_to_movw(struct jit_state* st, unsigned int i, unsigned int r)
{
  unsigned int lo_imm8;
  unsigned int lo_imm3;
  unsigned int lo_i;
  unsigned int lo_imm4;
  unsigned int movw_lo_0;
  unsigned int movw_lo;
  unsigned int movw_hi_0;
  unsigned int movw_hi;
  lo_imm8 = decode_thumb(i, 0U, 8U);
  lo_imm3 = decode_thumb(i, 8U, 3U);
  lo_i = decode_thumb(i, 11U, 1U);
  lo_imm4 = decode_thumb(i, 12U, 4U);
  movw_lo_0 = encode_thumb(lo_imm4, 62016, 0U, 4U);
  movw_lo = encode_thumb(lo_i, movw_lo_0, 10U, 1U);
  movw_hi_0 = encode_thumb(r, lo_imm8, 8U, 4U);
  movw_hi = encode_thumb(lo_imm3, movw_hi_0, 12U, 3U);
  add_ins_jittedthumb(st, movw_lo);
  add_ins_jittedthumb(st, movw_hi);
  return;
}

static __attribute__((always_inline)) inline void mov_int_to_movt(struct jit_state* st, unsigned int i, unsigned int r)
{
  unsigned int hi_imm8;
  unsigned int hi_imm3;
  unsigned int hi_i;
  unsigned int hi_imm4;
  unsigned int movt_lo_0;
  unsigned int movt_lo;
  unsigned int movt_hi_0;
  unsigned int movt_hi;
  hi_imm8 = decode_thumb(i, 16U, 8U);
  hi_imm3 = decode_thumb(i, 24U, 3U);
  hi_i = decode_thumb(i, 27U, 1U);
  hi_imm4 = decode_thumb(i, 28U, 4U);
  movt_lo_0 = encode_thumb(hi_imm4, 62144, 0U, 4U);
  movt_lo = encode_thumb(hi_i, movt_lo_0, 10U, 1U);
  add_ins_jittedthumb(st, movt_lo);
  movt_hi_0 = encode_thumb(r, hi_imm8, 8U, 4U);
  movt_hi = encode_thumb(hi_imm3, movt_hi_0, 12U, 3U);
  add_ins_jittedthumb(st, movt_hi);
  return;
}

static __attribute__((always_inline)) inline int get_immediate(unsigned long long ins)
{
  return (int) (ins >> 32LLU);
}

static __attribute__((always_inline)) inline unsigned char get_opcode_ins(unsigned long long ins)
{
  return (unsigned char) (ins & 255LLU);
}

static __attribute__((always_inline)) inline unsigned char nat_to_opcode_alu32(unsigned char op)
{
  if ((op & 7U) == 4U) {
    if (0U == (op & 8U)) {
      return 4U;
    } else {
      return 12U;
    }
  } else {
    return 0U;
  }
}

static __attribute__((always_inline)) inline unsigned char nat_to_opcode_alu32_reg(unsigned char op)
{
  return op;
}

static __attribute__((always_inline)) inline unsigned char nat_to_opcode_alu32_imm(unsigned char op)
{
  return op;
}

static __attribute__((always_inline)) inline void bpf_alu32_to_thumb(struct jit_state* st, unsigned long long ins)
{
  unsigned char op;
  unsigned char opc;
  unsigned int dst;
  int imm32;
  unsigned char opr;
  unsigned int src;
  unsigned char opi;
  unsigned int hi_32;
  unsigned char opk;
  op = get_opcode_ins(ins);
  opc = nat_to_opcode_alu32(op);
  dst = get_dst(ins);
  imm32 = get_immediate(ins);
  switch (opc) {
    case 12:
      opr = nat_to_opcode_alu32_reg(op);
      src = get_src(ins);
      bpf_alu32_to_thumb_reg(st, opr, dst, src);
      return;
    case 4:
      opi = nat_to_opcode_alu32_imm(op);
      if ((opi == 36U) == 0 && 0U <= imm32 && imm32 <= 255U) {
        bpf_alu32_to_thumb_imm(st, opi, dst, imm32);
        return;
      } else {
        hi_32 = decode_thumb(imm32, 16U, 16U);
        if (hi_32 == 0U) {
          if (opi == 180U) {
            mov_int_to_movw(st, imm32, dst);
            upd_load_store_regs_jittedthumb(st, dst, 2U);
            return;
          } else {
            upd_IR11_jittedthumb(st, 1);
            mov_int_to_movw(st, imm32, 11U);
            opk = opcode_reg_of_imm(opi);
            bpf_alu32_to_thumb_reg(st, opk, dst, 11U);
            return;
          }
        } else {
          if (opi == 180U) {
            mov_int_to_movw(st, imm32, 11U);
            mov_int_to_movt(st, imm32, 11U);
            upd_load_store_regs_jittedthumb(st, dst, 2U);
            return;
          } else {
            upd_IR11_jittedthumb(st, 1);
            mov_int_to_movw(st, imm32, 11U);
            mov_int_to_movt(st, imm32, 11U);
            opk = opcode_reg_of_imm(opi);
            bpf_alu32_to_thumb_reg(st, opk, dst, 11U);
            return;
          }
        }
      }
    default:
      upd_flag(st, 12U);
      return;

  }
}

static __attribute__((always_inline)) inline unsigned int get_store_ins_num(struct jit_state* st)
{
  _Bool b;
  unsigned int n0;
  unsigned int n1;
  unsigned int n2;
  unsigned int n3;
  unsigned int n4;
  unsigned int n5;
  unsigned int n6;
  unsigned int n7;
  unsigned int n8;
  unsigned int n9;
  b = is_store_reg(st, 0U);
  if (b) {
    n0 = 1U;
  } else {
    n0 = 0U;
  }
  b = is_store_reg(st, 1U);
  if (b) {
    n1 = n0 + 1U;
  } else {
    n1 = n0;
  }
  b = is_store_reg(st, 2U);
  if (b) {
    n2 = n1 + 1U;
  } else {
    n2 = n1;
  }
  b = is_store_reg(st, 3U);
  if (b) {
    n3 = n2 + 1U;
  } else {
    n3 = n2;
  }
  b = is_store_reg(st, 4U);
  if (b) {
    n4 = n3 + 1U;
  } else {
    n4 = n3;
  }
  b = is_store_reg(st, 5U);
  if (b) {
    n5 = n4 + 1U;
  } else {
    n5 = n4;
  }
  b = is_store_reg(st, 6U);
  if (b) {
    n6 = n5 + 1U;
  } else {
    n6 = n5;
  }
  b = is_store_reg(st, 7U);
  if (b) {
    n7 = n6 + 1U;
  } else {
    n7 = n6;
  }
  b = is_store_reg(st, 8U);
  if (b) {
    n8 = n7 + 1U;
  } else {
    n8 = n7;
  }
  b = is_store_reg(st, 9U);
  if (b) {
    n9 = n8 + 1U;
  } else {
    n9 = n8;
  }
  b = is_store_reg(st, 10U);
  if (b) {
    return n9 + 1U;
  } else {
    return n9;
  }
}

static __attribute__((always_inline)) inline void jit_alu32_to_thumb_pass(struct jit_state* st, unsigned int fuel, unsigned int entry_point)
{
  unsigned int n;
  unsigned long long ins;
  _Bool b;
  if (fuel == 0U) {
    return;
  } else {
    n = fuel - 1U;
    ins = eval_ins(st, entry_point);
    b = ins_is_bpf_alu32(ins);
    if (b) {
      bpf_alu32_to_thumb(st, ins);
      upd_bpf_offset_jittedthumb(st);
      jit_alu32_to_thumb_pass(st, n, entry_point + 1U);
      return;
    } else {
      return;
    }
  }
}

static __attribute__((always_inline)) inline void jit_alu32_thumb_upd_store(struct jit_state* st, unsigned int r)
{
  _Bool b;
  b = is_store_reg(st, r);
  if (b) {
    jit_alu32_thumb_store_template_jit(st, r, 12, r * 8 + 8);
    return;
  } else {
    return;
  }
}

static __attribute__((always_inline)) inline void jit_alu32_thumb_store(struct jit_state* st)
{
  jit_alu32_thumb_upd_store(st, 0U);
  jit_alu32_thumb_upd_store(st, 1U);
  jit_alu32_thumb_upd_store(st, 2U);
  jit_alu32_thumb_upd_store(st, 3U);
  jit_alu32_thumb_upd_store(st, 4U);
  jit_alu32_thumb_upd_store(st, 5U);
  jit_alu32_thumb_upd_store(st, 6U);
  jit_alu32_thumb_upd_store(st, 7U);
  jit_alu32_thumb_upd_store(st, 8U);
  jit_alu32_thumb_upd_store(st, 9U);
  jit_alu32_thumb_upd_store(st, 10U);
  return;
}

static __attribute__((always_inline)) inline void jit_alu32_thumb_upd_reset(struct jit_state* st, unsigned int r)
{
  _Bool b;
  b = is_non_reg(st, r);
  if (b) {
    return;
  } else {
    jit_alu32_thumb_load_template_jit(st, r, 13U, r * 4);
    return;
  }
}

static __attribute__((always_inline)) inline void jit_alu32_thumb_reset(struct jit_state* st)
{
  _Bool f;
  f = eval_use_IR11(st);
  if (f) {
    jit_alu32_thumb_load_template_jit(st, 11, 13U, 44);
  }
  jit_alu32_thumb_upd_reset(st, 10U);
  jit_alu32_thumb_upd_reset(st, 9U);
  jit_alu32_thumb_upd_reset(st, 8U);
  jit_alu32_thumb_upd_reset(st, 7U);
  jit_alu32_thumb_upd_reset(st, 6U);
  jit_alu32_thumb_upd_reset(st, 5U);
  jit_alu32_thumb_upd_reset(st, 4U);
  return;
}

static __attribute__((always_inline)) inline void jit_alu32_post(struct jit_state* st)
{
  unsigned int ins_rm;
  jit_alu32_thumb_load_template_jit(st, 13U, 13U, 0);
  ins_rm = encode_thumb(14U, 18176, 3U, 4U);
  upd_jitted_list(st, ins_rm);
  return;
}

static __attribute__((always_inline)) inline void copy_thumb_list_from_to_aux(struct jit_state* st, unsigned int fuel, unsigned int pc)
{
  unsigned int n;
  unsigned int ins0;
  if (fuel == 0U) {
    return;
  } else {
    n = fuel - 1U;
    ins0 = eval_thumb_ins(st, pc);
    upd_jitted_list(st, ins0);
    copy_thumb_list_from_to_aux(st, n, pc + 1U);
    return;
  }
}

static __attribute__((always_inline)) inline void copy_thumb_list_from_to(struct jit_state* st)
{
  unsigned int len;
  len = eval_thumb_len(st);
  copy_thumb_list_from_to_aux(st, len, 0U);
  return;
}

static __attribute__((always_inline)) inline void jit_alu32_to_thumb(struct jit_state* st, unsigned int pc)
{
  unsigned int len;
  unsigned int ofs0;
  unsigned int ofs1;
  reset_init_jittedthumb(st);
  len = eval_ins_len(st);
  jit_alu32_to_thumb_pass(st, len, pc);
  ofs0 = eval_jitted_len(st);
  ofs1 = eval_offset(st);
  add_key_value2(st, pc, ofs0, ofs1 - 1U);
  jit_alu32_pre(st);
  jit_alu32_thumb_save(st);
  jit_alu32_thumb_load(st);
  copy_thumb_list_from_to(st);
  jit_alu32_thumb_store(st);
  jit_alu32_thumb_reset(st);
  jit_alu32_post(st);
  return;
}

static __attribute__((always_inline)) inline void jit_alu32_aux(struct jit_state* st, unsigned int fuel, unsigned int pc, _Bool pre_is_alu32)
{
  unsigned int n;
  unsigned long long ins;
  _Bool b;
  int ofs;
  unsigned int next_pc;
  unsigned long long next_ins;
  if (fuel == 0U) {
    return;
  } else {
    n = fuel - 1U;
    ins = eval_ins(st, pc);
    b = ins_is_bpf_alu32(ins);
    if (b) {
      if (pre_is_alu32 == 0) {
        jit_alu32_to_thumb(st, pc);
        jit_alu32_aux(st, n, pc + 1U, 1);
        return;
      } else {
        jit_alu32_aux(st, n, pc + 1U, 1);
        return;
      }
    } else {
      b = ins_is_bpf_jump(ins);
      if (b) {
        ofs = get_offset(ins);
        next_pc = pc + ofs + 1U;
        next_ins = eval_ins(st, next_pc);
        b = ins_is_bpf_alu32(next_ins);
        if (b) {
          jit_alu32_to_thumb(st, next_pc);
          jit_alu32_aux(st, n, pc + 1U, 0);
          return;
        } else {
          jit_alu32_aux(st, n, pc + 1U, 0);
          return;
        }
      } else {
        jit_alu32_aux(st, n, pc + 1U, 0);
        return;
      }
    }
  }
}

void jit_alu32(struct jit_state* st)
{
  unsigned int len;
  len = eval_ins_len(st);
  jit_alu32_aux(st, len, 0U, 0);
  return;
}

static __attribute__((always_inline)) inline unsigned int reg64_to_reg32(unsigned long long d)
{
  return (unsigned int) d;
}

static __attribute__((always_inline)) inline long long eval_immediate(int ins)
{
  return (long long) ins;
}

static __attribute__((always_inline)) inline unsigned long long get_src64(struct jit_state* st, unsigned char x, unsigned long long ins)
{
  int imm;
  long long imm64;
  unsigned int src;
  unsigned long long src64;
  if (0U == (x & 8U)) {
    imm = get_immediate(ins);
    imm64 = eval_immediate(imm);
    return (unsigned long long) imm64;
  } else {
    src = get_src(ins);
    src64 = eval_reg(st, src);
    return src64;
  }
}

static __attribute__((always_inline)) inline unsigned int get_src32(struct jit_state* st, unsigned char x, unsigned long long ins)
{
  int imm;
  unsigned int src;
  unsigned long long src64;
  unsigned int src32;
  if (0U == (x & 8U)) {
    imm = get_immediate(ins);
    return imm;
  } else {
    src = get_src(ins);
    src64 = eval_reg(st, src);
    src32 = reg64_to_reg32(src64);
    return src32;
  }
}

static __attribute__((always_inline)) inline unsigned char get_opcode_alu64(unsigned char op)
{
  return (unsigned char) (op & 240);
}

static __attribute__((always_inline)) inline unsigned char get_opcode_alu32(unsigned char op)
{
  return (unsigned char) (op & 240);
}

static __attribute__((always_inline)) inline unsigned char get_opcode_branch(unsigned char op)
{
  return (unsigned char) (op & 240);
}

static __attribute__((always_inline)) inline unsigned char get_opcode_mem_ld_imm(unsigned char op)
{
  return (unsigned char) (op & 255);
}

static __attribute__((always_inline)) inline unsigned char get_opcode_mem_ld_reg(unsigned char op)
{
  return (unsigned char) (op & 255);
}

static __attribute__((always_inline)) inline unsigned char get_opcode_mem_st_imm(unsigned char op)
{
  return (unsigned char) (op & 255);
}

static __attribute__((always_inline)) inline unsigned char get_opcode_mem_st_reg(unsigned char op)
{
  return (unsigned char) (op & 255);
}

static __attribute__((always_inline)) inline unsigned char get_opcode(unsigned char op)
{
  return (unsigned char) (op & 7);
}

unsigned int get_add(unsigned int x, unsigned int y)
{
  return x + y;
}

unsigned int get_sub(unsigned int x, unsigned int y)
{
  return x - y;
}

static __attribute__((always_inline)) inline unsigned int get_addr_ofs(unsigned long long x, int ofs)
{
  return (unsigned int) (x + (unsigned long long) ofs);
}

static __attribute__((always_inline)) inline unsigned int get_start_addr(struct memory_region *mr)
{
  return (*mr).start_addr;
}

static __attribute__((always_inline)) inline unsigned int get_block_size(struct memory_region *mr)
{
  return (*mr).block_size;
}

static __attribute__((always_inline)) inline unsigned int get_block_perm(struct memory_region *mr)
{
  return (*mr).block_perm;
}

static __attribute__((always_inline)) inline _Bool is_well_chunk_bool(unsigned int chunk)
{
  switch (chunk) {
    case 1:
      return 1;
    case 2:
      return 1;
    case 4:
      return 1;
    case 8:
      return 1;
    default:
      return 0;

  }
}

static __attribute__((always_inline)) inline unsigned char *check_mem_aux2(struct memory_region *mr, unsigned int perm, unsigned int addr, unsigned int chunk)
{
  unsigned int start;
  unsigned int size;
  unsigned int mr_perm;
  unsigned int lo_ofs;
  unsigned int hi_ofs;
  start = get_start_addr(mr);
  size = get_block_size(mr);
  mr_perm = get_block_perm(mr);
  lo_ofs = get_sub(addr, start);
  hi_ofs = get_add(lo_ofs, chunk);
  if (hi_ofs <= size
        && (lo_ofs <= 4294967295U - chunk && 0U == lo_ofs % chunk)
        && mr_perm >= perm) {
    return (*mr).block_ptr + lo_ofs;
  } else {
    return 0;
  }
}

static __attribute__((always_inline)) inline unsigned char *check_mem_aux(struct jit_state* st, unsigned int num, unsigned int perm, unsigned int chunk, unsigned int addr, struct memory_region *mrs)
{
  unsigned int n;
  struct memory_region *cur_mr;
  unsigned char *check_mem;
  _Bool is_null;
  if (num == 0U) {
    return 0;
  } else {
    n = num - 1U;
    cur_mr = get_mem_region(n, mrs);
    check_mem = check_mem_aux2(cur_mr, perm, addr, chunk);
    is_null = cmp_ptr32_nullM(check_mem);
    if (is_null) {
      return check_mem_aux(st, n, perm, chunk, addr, mrs);
    } else {
      return check_mem;
    }
  }
}

unsigned char *check_mem(struct jit_state* st, unsigned int perm, unsigned int chunk, unsigned int addr)
{
  _Bool well_chunk;
  unsigned int mem_reg_num;
  struct memory_region *mrs;
  unsigned char *check_mem;
  _Bool is_null;
  well_chunk = is_well_chunk_bool(chunk);
  if (well_chunk) {
    mem_reg_num = eval_mrs_num(st);
    mrs = eval_mrs_regions(st);
    check_mem =
      check_mem_aux(st, mem_reg_num, perm, chunk, addr, mrs);
    is_null = cmp_ptr32_nullM(check_mem);
    if (is_null) {
      return 0;
    } else {
      return check_mem;
    }
  } else {
    return 0;
  }
}

static __attribute__((always_inline)) inline void step_opcode_alu64(struct jit_state* st, unsigned long long dst64, unsigned long long src64, unsigned int dst, unsigned char op)
{
  unsigned char opcode_alu64;
  unsigned int src32;
  opcode_alu64 = get_opcode_alu64(op);
  switch (opcode_alu64) {
    case 0:
      upd_reg(st, dst, dst64 + src64);
      return;
    case 16:
      upd_reg(st, dst, dst64 - src64);
      return;
    case 32:
      upd_reg(st, dst, dst64 * src64);
      return;
    case 48:
      if (src64 != 0LLU) {
        upd_reg(st, dst, dst64 / src64);
        return;
      } else {
        upd_flag(st, 10U);
        return;
      }
    case 64:
      upd_reg(st, dst, dst64 | src64);
      return;
    case 80:
      upd_reg(st, dst, dst64 & src64);
      return;
    case 96:
      src32 = reg64_to_reg32(src64);
      if (src32 < 64U) {
        upd_reg(st, dst, dst64 << src32);
        return;
      } else {
        upd_flag(st, 11U);
        return;
      }
    case 112:
      src32 = reg64_to_reg32(src64);
      if (src32 < 64U) {
        upd_reg(st, dst, dst64 >> src32);
        return;
      } else {
        upd_flag(st, 11U);
        return;
      }
    case 128:
      if (op == 135) {
        upd_reg(st, dst, -dst64);
        return;
      } else {
        upd_flag(st, 2U);
        return;
      }
    case 144:
      if (src64 != 0LLU) {
        upd_reg(st, dst, dst64 % src64);
        return;
      } else {
        upd_flag(st, 10U);
        return;
      }
    case 160:
      upd_reg(st, dst, dst64 ^ src64);
      return;
    case 176:
      upd_reg(st, dst, src64);
      return;
    case 192:
      src32 = reg64_to_reg32(src64);
      if (src32 < 64U) {
        upd_reg(st, dst,
                (unsigned long long) ((long long) dst64 >> src32));
        return;
      } else {
        upd_flag(st, 11U);
        return;
      }
    default:
      upd_flag(st, 2U);
      return;

  }
}

static __attribute__((always_inline)) inline void step_opcode_alu32(struct jit_state* st, unsigned char op, unsigned int pc)
{
  unsigned char opcode_alu32;
  unsigned int ofs0;
  unsigned int ofs1;
  opcode_alu32 = get_opcode_alu32(op);
  switch (opcode_alu32) {
    case 0:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 16:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 32:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 48:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 64:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 80:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 96:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 112:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 128:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 144:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 160:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 176:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    case 192:
      ofs0 = eval_key_value2_arm_ofs(st, pc);
      ofs1 = eval_key_value2_alu32_ofs(st, pc);
      magic_function(st, ofs0);
      upd_pc(st, pc + ofs1);
      return;
    default:
      upd_flag(st, 2U);
      return;

  }
}

static __attribute__((always_inline)) inline void step_opcode_branch(struct jit_state* st, unsigned long long dst64, unsigned long long src64, unsigned int pc, unsigned int ofs, unsigned char op)
{
  unsigned char opcode_jmp;
  unsigned char *f_ptr;
  _Bool is_null;
  unsigned int res;
  opcode_jmp = get_opcode_branch(op);
  switch (opcode_jmp) {
    case 0:
      if (op == 5) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        upd_flag(st, 2U);
        return;
      }
    case 16:
      if (dst64 == src64) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 32:
      if (dst64 > src64) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 48:
      if (dst64 >= src64) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 160:
      if (dst64 < src64) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 176:
      if (dst64 <= src64) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 64:
      if ((dst64 & src64) != 0LLU) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 80:
      if (dst64 != src64) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 96:
      if ((long long) dst64 > (long long) src64) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 112:
      if ((long long) dst64 >= (long long) src64) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 192:
      if ((long long) dst64 < (long long) src64) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 208:
      if ((long long) dst64 <= (long long) src64) {
        upd_pc(st, pc + ofs);
        return;
      } else {
        return;
      }
    case 128:
      if (op == 133) {
        f_ptr = _bpf_get_call((int) src64);
        is_null = cmp_ptr32_nullM(f_ptr);
        if (is_null) {
          upd_flag(st, 5U);
          return;
        } else {
          res = exec_function(st, f_ptr);
          upd_reg(st, 0U, (unsigned long long) res);
          return;
        }
      } else {
        upd_flag(st, 2U);
        return;
      }
    case 144:
      if (op == 149) {
        upd_flag(st, 1U);
        return;
      } else {
        upd_flag(st, 2U);
        return;
      }
    default:
      upd_flag(st, 2U);
      return;

  }
}

static __attribute__((always_inline)) inline void step_opcode_mem_ld_imm(struct jit_state* st, int imm, unsigned long long dst64, unsigned int dst, unsigned char op)
{
  unsigned char opcode_ld;
  opcode_ld = get_opcode_mem_ld_imm(op);
  switch (opcode_ld) {
    case 24:
      upd_reg(st, dst, (unsigned long long) (unsigned int) imm);
      return;
    case 16:
      upd_reg(st, dst,
              dst64 | (unsigned long long) (unsigned int) imm << 32U);
      return;
    default:
      upd_flag(st, 2U);
      return;

  }
}

static __attribute__((always_inline)) inline void step_opcode_mem_ld_reg(struct jit_state* st, unsigned int addr, unsigned int dst, unsigned char op)
{
  unsigned char opcode_ld;
  unsigned char *addr_ptr;
  _Bool is_null;
  unsigned long long v;
  opcode_ld = get_opcode_mem_ld_reg(op);
  switch (opcode_ld) {
    case 97:
      addr_ptr = check_mem(st, 1U, 4U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        v = load_mem(st, 4U, addr_ptr);
        upd_reg(st, dst, v);
        return;
      }
    case 105:
      addr_ptr = check_mem(st, 1U, 2U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        v = load_mem(st, 2U, addr_ptr);
        upd_reg(st, dst, v);
        return;
      }
    case 113:
      addr_ptr = check_mem(st, 1U, 1U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        v = load_mem(st, 1U, addr_ptr);
        upd_reg(st, dst, v);
        return;
      }
    case 121:
      addr_ptr = check_mem(st, 1U, 8U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        v = load_mem(st, 8U, addr_ptr);
        upd_reg(st, dst, v);
        return;
      }
    default:
      upd_flag(st, 2U);
      return;

  }
}

static __attribute__((always_inline)) inline void step_opcode_mem_st_imm(struct jit_state* st, int imm, unsigned int addr, unsigned char op)
{
  unsigned char opcode_st;
  unsigned char *addr_ptr;
  _Bool is_null;
  opcode_st = get_opcode_mem_st_imm(op);
  switch (opcode_st) {
    case 98:
      addr_ptr = check_mem(st, 2U, 4U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        store_mem_imm(st, addr_ptr, 4U, imm);
        return;
      }
    case 106:
      addr_ptr = check_mem(st, 2U, 2U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        store_mem_imm(st, addr_ptr, 2U, imm);
        return;
      }
    case 114:
      addr_ptr = check_mem(st, 2U, 1U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        store_mem_imm(st, addr_ptr, 1U, imm);
        return;
      }
    case 122:
      addr_ptr = check_mem(st, 2U, 8U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        store_mem_imm(st, addr_ptr, 8U, imm);
        return;
      }
    default:
      upd_flag(st, 2U);
      return;

  }
}

static __attribute__((always_inline)) inline void step_opcode_mem_st_reg(struct jit_state* st, unsigned long long src64, unsigned int addr, unsigned char op)
{
  unsigned char opcode_st;
  unsigned char *addr_ptr;
  _Bool is_null;
  opcode_st = get_opcode_mem_st_reg(op);
  switch (opcode_st) {
    case 99:
      addr_ptr = check_mem(st, 2U, 4U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        store_mem_reg(st, addr_ptr, 4U, src64);
        return;
      }
    case 107:
      addr_ptr = check_mem(st, 2U, 2U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        store_mem_reg(st, addr_ptr, 2U, src64);
        return;
      }
    case 115:
      addr_ptr = check_mem(st, 2U, 1U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        store_mem_reg(st, addr_ptr, 1U, src64);
        return;
      }
    case 123:
      addr_ptr = check_mem(st, 2U, 8U, addr);
      is_null = cmp_ptr32_nullM(addr_ptr);
      if (is_null) {
        upd_flag(st, 3U);
        return;
      } else {
        store_mem_reg(st, addr_ptr, 8U, src64);
        return;
      }
    default:
      upd_flag(st, 2U);
      return;

  }
}

static __attribute__((always_inline)) inline void step(struct jit_state* st)
{
  unsigned int pc;
  unsigned long long ins;
  unsigned char op;
  unsigned char opc;
  unsigned int dst;
  unsigned long long dst64;
  unsigned long long src64;
  int ofs;
  int imm;
  unsigned int src;
  unsigned int addr;
  pc = eval_pc(st);
  ins = eval_ins(st, pc);
  op = get_opcode_ins(ins);
  opc = get_opcode(op);
  dst = get_dst(ins);
  switch (opc) {
    case 7:
      dst64 = eval_reg(st, dst);
      src64 = get_src64(st, op, ins);
      step_opcode_alu64(st, dst64, src64, dst, op);
      return;
    case 4:
      step_opcode_alu32(st, op, pc);
      return;
    case 5:
      dst64 = eval_reg(st, dst);
      ofs = get_offset(ins);
      src64 = get_src64(st, op, ins);
      step_opcode_branch(st, dst64, src64, pc,
                         (unsigned int) ofs, op);
      return;
    case 0:
      dst64 = eval_reg(st, dst);
      imm = get_immediate(ins);
      step_opcode_mem_ld_imm(st, imm, dst64, dst, op);
      return;
    case 1:
      src = get_src(ins);
      src64 = eval_reg(st, src);
      ofs = get_offset(ins);
      addr = get_addr_ofs(src64, ofs);
      step_opcode_mem_ld_reg(st, addr, dst, op);
      return;
    case 2:
      dst64 = eval_reg(st, dst);
      ofs = get_offset(ins);
      imm = get_immediate(ins);
      addr = get_addr_ofs(dst64, ofs);
      step_opcode_mem_st_imm(st, imm, addr, op);
      return;
    case 3:
      dst64 = eval_reg(st, dst);
      src = get_src(ins);
      src64 = eval_reg(st, src);
      ofs = get_offset(ins);
      addr = get_addr_ofs(dst64, ofs);
      step_opcode_mem_st_reg(st, src64, addr, op);
      return;
    default:
      upd_flag(st, 2U);
      return;

  }
}

static __attribute__((always_inline)) inline void ibpf_interpreter_aux(struct jit_state* st, unsigned int fuel)
{
  unsigned int fuel0;
  unsigned int len;
  unsigned int pc;
  unsigned int f;
  unsigned int len0;
  unsigned int pc0;
  if (fuel == 0U) {
    upd_flag(st, 6U);
    return;
  } else {
    fuel0 = fuel - 1U;
    len = eval_ins_len(st);
    pc = eval_pc(st);
    if (pc < len) {
      step(st); //print_jit_state(st);
      f = eval_flag(st);
      if (f == 0U) {
        len0 = eval_ins_len(st);
        pc0 = eval_pc(st);
        if (pc0 + 1U < len0) {
          upd_pc_incr(st);
          ibpf_interpreter_aux(st, fuel0);
          return;
        } else {
          upd_flag(st, 6U);
          return;
        }
      } else {
        return;
      }
    } else {
      upd_flag(st, 6U);
      return;
    }
  }
}

unsigned long long ibpf_interpreter(struct jit_state* st, unsigned int fuel)
{
  unsigned int f;
  unsigned long long res;
  ibpf_interpreter_aux(st, fuel);
  f = eval_flag(st);
  if (f == 1U) {
    res = eval_reg(st, 0U);
    return res;
  } else {
    return 0LLU;
  }
}

