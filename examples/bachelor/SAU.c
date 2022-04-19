#include "cpu.h"
#include "include/main.h"
#include <stdio.h>
#include <stdlib.h>

extern char __START_NSC__[], __END_NSC__[];

void defineRegion(unsigned int regNum, unsigned int baseAddr, unsigned int limitAddr, unsigned int isNSC)
{
	SAU->RNR = regNum;
	SAU->RBAR = (baseAddr & SAU_RBAR_BADDR_Msk);
	SAU->RLAR = (((limitAddr & SAU_RLAR_LADDR_Msk) | isNSC << SAU_RLAR_NSC_Pos) & SAU_RLAR_NSC_Msk) | 1U;
}

void configureSAU(int enable)
{
	for(int i = 0; i < 6; ++i){
		toggle_S(i%3);
	}
	/*char buffer[16];
	puts("NS-Region");
	puts(__itoa((unsigned int)__START_NS__,buffer,16));
	puts(__itoa((unsigned int)__END_NS__,buffer,16));
	*/
	//puts("NSC-Region");
	//puts(__itoa((unsigned int)__START_NSC__,buffer,16));
	//puts(__itoa((unsigned int)__END_NSC__,buffer,16));
	//__TZ_set_MSP_NS((unsigned int)(__STACK_NS_START__));
	//__TZ_set_PSP_NS((unsigned int)(__STACK_NS_START__));
	if(enable)
	{
		defineRegion(0U,0x8040000,0x807E800,0U);
		//defineRegion(1U,(unsigned int)__START_NSC__,(unsigned int)__END_NSC__, 1U);
		defineRegion(2U,0x20018000,0x2002F700,0U);

		__DSB();
		__ISB();

		//__HAL_RCC_SYSCFG_CLK_ENABLE();
		SYSCFG->CSLCKR |= SYSCFG_CSLCKR_LOCKSAU;

		TZ_SAU_Enable();
	}else{
		TZ_SAU_Disable();
	}
}
