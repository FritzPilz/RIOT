#include "cpu.h"
#include "include/main.h"
#include "include/SAU.h"
#include <stdio.h>
#include <stdlib.h>

extern char __START_NS__[], __END_NS__[];
extern char __START_NSC__[], __END_NSC__[];
extern char __NS_STACK_END__[], __NS_STACK_START__[];

typedef unsigned int volatile ui_v;

/*The Memory in which I declare a NS-Section is erased, so I need to copy it from another bank where it is stored*/
void copyNS(void)
{
	char volatile* addr = __START_NS__;
	char volatile* ns_addr =  (char *) ((int) __START_NS__ | 0xC000000);
	__asm volatile ("bkpt");
	for(unsigned int i = (unsigned int) __START_NS__; i <= (unsigned int) __END_NSC__ ;++i){
		addr[i] = ns_addr[i];
	}
	__asm volatile("bkpt");
}

SAU_Region defineRegion(ui_v regNum, ui_v baseAddr, ui_v limitAddr, ui_v isNSC)
{
	SAU->RNR = regNum;
	SAU->RBAR = (baseAddr & SAU_RBAR_BADDR_Msk);
	SAU->RLAR = ((limitAddr & SAU_RLAR_LADDR_Msk) | isNSC << SAU_RLAR_NSC_Pos) | 1U;
	
	SAU_Region region = {
		.region = SAU->RNR,
		.base = SAU->RBAR,
		.limit = SAU->RLAR,
		.nsc = isNSC
	};

	return region;
}

SAU_Region * configureSAU(int enable, SAU_Region* regions)
{
	for(int i = 0; i < 3; ++i){
		toggle_S(i%3);
	}
	if(enable)
	{
		regions[0] = defineRegion(0U,(ui_v)__START_NS__,(ui_v)__END_NS__, 0U);
		regions[1] = defineRegion(1U,(ui_v)__START_NSC__,(ui_v)__END_NSC__, 1U);
		regions[2] = defineRegion(2U,(ui_v)__NS_STACK_END__,(ui_v)__NS_STACK_START__,0U);

		__DSB();
		__ISB();

		SYSCFG->CSLCKR |= SYSCFG_CSLCKR_LOCKSAU;

		TZ_SAU_Enable();
		copyNS();
	}else{
		TZ_SAU_Disable();
	}
	return regions;
}
