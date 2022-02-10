#include "board.h"
#include "timex.h"
#include "ztimer.h"
#include "include/ns.h"
#include "include/nsc.h"
#include "include/secure.h"

__attribute__((section(".non-secure"))) __attribute__((noinline)) void ns_test(void)
//Should be executed in Non-Secure state
{
	int status = get_board_state();
	status = status & 0x1;
	if(status)
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
	//veneer_func();
	__asm ( "BL =veneer_func \n\t" );
	//secure_test();
}
