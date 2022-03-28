/* 
 * Written by Fritz Pilz for the Bachelor Thesis:
 * Freie Universitaet Berlin
 * */

#pragma GCC push_options
#pragma GCC optimize ("O0")

#include "board.h"
#include "timex.h"
#include "ztimer.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/secure.h"
#include "include/ns.h"
#include "include/nsc.h"
#include "include/SAU.h"

#define CPUID_NS 0xE002ED00

/* 
 * Inline Assembly: 
 * 
 * __asm [volatile](
 * operation :
 * Output :
 * Input :
 * Clobbers )
 * 
 * */

extern char __START__[], __SECURE__[], __NS__[];
extern char __STARTNSC__[], __NSC__[];

typedef void nsfp (void) __attribute__((cmse_nonsecure_call));


__attribute__((noinline)) __attribute__((section(".secure"))) void start_SAU(void)
{
	__asm ( "svc 2 \n\t"	);
}


__attribute__((noinline)) __attribute__((section(".secure"))) void end_SAU(void)
{
	__asm(	"svc 3 \n\t"	);
}

__attribute__((noinline)) __attribute((section(".secure"))) void enable_debug(void){
	__asm(	"svc 4 \n\t"	);
}

__attribute__((noinline)) __attribute((section(".secure"))) void do_priviliged_stuff(int enable)
{
/* I have created symbols in the linker script which mark the beginning an the End of Sections
 * Those Markers are 32 Bit aligned. */
	if(enable)
	{
		unsigned int res[3];
		declare_NS((unsigned int)__STARTNSC__, (unsigned int)__NSC__-1, 1, 1, res);
		declare_NS((unsigned int)__SECURE__, (unsigned int)__NS__-1, 2, 0, res);
		enable_SAU();

	}
	else
	{
		disable_SAU();
	}
	return;
}

__attribute__((noinline)) __attribute__((section(".secure"))) unsigned int get_board_state_S(void)
{
	return *(unsigned int *) CPUID_NS;
}

__attribute__((noinline)) __attribute__((section(".secure")))  __attribute__((cmse_nonsecure_entry)) void secure_test(void)
{
	char buffer[33];
	unsigned int volatile status = get_board_state_S();
	puts(__itoa(status, buffer, 16));
	
	if(status)
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
	}
	else
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
	}
	return;
}

__attribute__((section(".secure"))) __attribute__((noinline)) __attribute__((cmse_nonsecure_entry)) int main(void)
{
	char buffer[33];

	start_SAU();
	
	unsigned int volatile status = 0;
	status = get_board_state_S();
	
	if(status)
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
	}
	else
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
	}

	nsfp *fp = (nsfp *) ns_test;
	puts("Address of ns_test:");
	puts(__itoa((unsigned int)ns_test,buffer,16));
	puts(__itoa((unsigned int)fp,buffer,16));
	puts(__itoa(status, buffer, 16));
	fp();
	end_SAU();
	while(1){
		LED2_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
	}
}

#pragma GCC pop_options
