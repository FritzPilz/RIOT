#ifndef NONSECURE
#define NONSECURE

#define CPUID_NS 0xE002ED0

int get_board_state(void);

void ns_test(void);

#endif
