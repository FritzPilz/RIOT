#include "board.h"
#include "timex.h"
#include "ztimer.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/ns.h"
#include "include/nsc.h"
#include "include/secure.h"

__attribute__((section(".non-secure"))) __attribute__((noinline)) int get_board_state_NS(void)
{
	return *(unsigned int *) CPUID_NS;
}

__attribute__((section(".non-secure"))) __attribute__((noinline)) __attribute__((optimize("O0"))) void ns_test(void)
//Should be executed in Non-Secure state
{
	unsigned int volatile status = get_board_state_NS();
	
	char buffer[33];
	puts(__itoa(status,buffer,16));

	if(!status)
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED0_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED0_TOGGLE;
	}
	else
	{
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;
		ztimer_sleep(ZTIMER_USEC, 500*1000);
		LED2_TOGGLE;

	}
	ztimer_sleep(ZTIMER_USEC, 500*1000);
	secure_test();
}
