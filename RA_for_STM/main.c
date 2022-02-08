/* 
 * Written by Fritz Pilz for the Bachelor Thesis:
 * Freie Universitaet Berlin
 * */

#include "board.h"
#include "timex.h"
#include "ztimer.h"
#include "include/secure.h"
#include "include/ns.h"
#include "include/nsc.h"
#include "include/SAU.h"

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

void do_priviliged_stuff(int enable);
extern char __START__[], __SECURE__[], __NS__[], __NSC__[];

__attribute__((noinline)) int get_board_state(void)
{
	int res = 0;
	__asm
	(	"svc 3		\n\t"
		"mov %0, r0	\n\t" :
		"=r" (res)
	);
	return res;
}

__attribute__((noinline)) __attribute__((section(".secure"))) void priviliged_syscall(void)
{
	__asm ( "svc 2 \n\t" );
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
		LED0_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED0_TOGGLE;
	}
	else
	{
		LED1_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
	}
	__asm(	"orr lr, lr, #0 \n\t"
		"BXNS LR 	\n\t"	);
}

__attribute__((section(".secure"))) __attribute__((noinline)) int main(void)
{
	int status = get_board_state();
	status = status & 0x1;
	if(status)
	{
		LED0_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED0_TOGGLE;
	}
	else
	{
		LED1_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED1_TOGGLE;
	}
	ztimer_sleep(ZTIMER_USEC, 5000*1000);
	do_priviliged_stuff(1);
	__asm(	"push {r0, r1}		\n\t"
		"ldr r0, =func_test	\n\t"
		"movs r1, #1		\n\t"
		"bics r0, r1		\n\t"
		"BLXNS r0		\n\t"
		"pop {r0, r1}		\n\t"
	);
	do_priviliged_stuff(0);
	while(1){
		LED2_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
	}
	return 0;
}
