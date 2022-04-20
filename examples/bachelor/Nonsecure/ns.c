// #include "board.h"
// #include "timex.h"
// #include "ztimer.h"
// #include "arm_cmse.h"

#define CPUID_NS 0xE002ED00

__attribute__((section(".test"), used)) unsigned int isSecure_NS(void)
{
	return *(unsigned int volatile*) CPUID_NS;
}

/*__attribute__((section(".test"), used)) void toggle_NS(unsigned int t)
{
	switch(t){
		case 0: LED0_TOGGLE; break;
		case 1: LED1_TOGGLE; break;
		case 2: LED2_TOGGLE; break;
		default: break;
	}
	ztimer_sleep(ZTIMER_USEC, 500*1000);
}*/

__attribute__((section(".test"), used)) void ns_test(void)
{
	/*unsigned int volatile secure = isSecure_NS();
	if(!secure){
		toggle_NS(0);
		toggle_NS(0);
	}else{
		toggle_NS(2);
		toggle_NS(2);
	}*/
}

__attribute__((section(".test_start"),used)) int main(void)
{
	//__TZ_set_PSP_NS(0x20027F00);
	ns_test();
	while(1){};
}
