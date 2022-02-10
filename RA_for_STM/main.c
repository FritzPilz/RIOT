/* 
 * Written by Fritz Pilz for the Bachelor Thesis:
 * Freie Universitaet Berlin
 * */

#include "board.h"
#include "timex.h"
#include "ztimer.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/secure.h"
#include "include/ns.h"
#include "include/nsc.h"
#include "include/SAU.h"

#define CPUID 		0xE000ED00
#define CPUID_NS 	0xE002ED00

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

extern char __START__[], __SECURE__[], __NS__[], __NSC__[];

__attribute__((noinline)) int get_board_state(void)
{
	//Maybe didn't do what I expected it to do
	int res = 0;
	__asm
	(	"svc 4		\n\t"
		"mov %0, r0	\n\t" :
		"=r" (res)
	);
	return res;
}

__attribute__((noinline)) __attribute__((section(".secure"))) void start_SAU(void)
{
	__asm ( "svc 2 \n\t"	);
}


__attribute__((noinline)) __attribute__((section(".secure"))) void end_SAU(void)
{
	__asm(	"svc 3 \n\t"	);
}

__attribute__((noinline)) __attribute((section(".secure"))) void do_priviliged_stuff(int enable)
{
/* I have created symbols in the linker script which mark the beginning an the End of Sections
 * Those Markers are 32 Bit aligned. */
	if(enable)
	{
		unsigned int res[3];
		declare_NS((unsigned int)__NS__, (unsigned int)__NSC__-1, 1, 1, res);
		declare_NS((unsigned int)__SECURE__, (unsigned int)__NS__-1, 2, 0, res);
		enable_SAU();
	}
	else
	{
		disable_SAU();
	}
	return;
}

__attribute__((section(".secure"))) void secure_test(void)
{
	int status = get_board_state();
	status = status & 0x1;
	
	if(status)
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
	}
	else
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
	}
	/*__asm(	"MOVS r0, #0	\n\t"
		"BICS lr, r0	\n\t"
		"BX lr		\n\t");*/
	return;
}

__attribute__((section(".secure"))) __attribute__((noinline)) int main(void)
{
	int status = get_board_state();
	status = status & 0x1;
	char buffer[33];

	unsigned int* cpuid = (unsigned int *)CPUID;
	unsigned int* cpuid_ns = (unsigned int *)CPUID_NS;

	puts(__itoa(*cpuid,buffer,16));
	puts(__itoa(*cpuid_ns,buffer,16));

	if(status)
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
	}
	else
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
	}
	//start_SAU();
	
	cpuid_ns = (unsigned int *)CPUID_NS;
	
	if(status)
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
	}
	else
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
	}

	puts("Address of func_test:");
	puts(__itoa((unsigned int)ns_test,buffer,16));
	__asm(	"LDR r0, =ns_test	\n\t"
		"MOVS r1, #0x0		\n\t"
		"BICS r0, r1		\n\t"
		"BL =ns_test		\n\t"
	);
	ns_test();
	//end_SAU();
	if(status)
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
	}
	else
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
	}while(1){
		LED2_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
	}
	return 0;
}
