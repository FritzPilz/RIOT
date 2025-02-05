#include <stdio.h>

#include "board.h"
#include "timex.h"
#include "ztimer.h"
#include "include/main.h"

#define CPUID_NS 0xE002ED00

__attribute__((section(".non-secure"), used)) unsigned int isSecure_NS(void)
{
	return *(unsigned int volatile*) CPUID_NS;
}

__attribute__((section(".non-secure"), used)) void toggle_NS(uint32_t t)
{
	switch(t){
		case 0: LED0_TOGGLE; break;
		case 1: LED1_TOGGLE; break;
		case 2: LED2_TOGGLE; break;
		default: break;
	}
	ztimer_sleep(ZTIMER_USEC, 500*1000);
}

__attribute__((section(".non-secure"), used)) void ns_test(void)
{
	__asm volatile("bkpt");
	unsigned int volatile secure = isSecure_NS();
	if(!secure){
		puts("Nonsecure: Success");
		//toggle_NS(0);
		//toggle_NS(0);
	}else{
		puts("Secure: Failure");
		//toggle_NS(2);
		//toggle_NS(2);
	}
}
