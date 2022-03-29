#include "cpu.h"

extern char __START_NS__[], __END_NS__[];
extern char __START_NSC__[], __END_NSC__[];

void defineRegion(unsigned int regNum, unsigned int baseAddr, unsigned int limitAddr, unsigned int isNSC)
{
	SAU->RNR = regNum;
	SAU->RBAR = (baseAddr & SAU_RBAR_BADDR_Msk);
	SAU->RLAR = (((limitAddr & SAU_RLAR_LADDR_Msk) | isNSC << SAU_RLAR_NSC_Pos) & SAU_RLAR_NSC_Msk) | 1U;
}

void configureSAU(int enable)
{
	if(enable)
	{
		defineRegion(0U,(unsigned int)__START_NS__, (unsigned int)__END_NS__, 0U);
		defineRegion(1U,(unsigned int)__START_NSC__,(unsigned int)__END_NSC__, 1U);
		TZ_SAU_Enable();
	}else{
		TZ_SAU_Disable();
	}
}
