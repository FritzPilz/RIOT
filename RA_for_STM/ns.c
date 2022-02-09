#include "board.h"
#include "timex.h"
#include "ztimer.h"
#include "include/ns.h"
#include "include/nsc.h"
#include "include/secure.h"

__attribute((section(".non-secure")))void func_test(void)
//Should be executed in Non-Secure state
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
	ztimer_sleep(ZTIMER_USEC, 500*1000);
	veneer_func();
	__asm ( "b =venner_func" );
}
