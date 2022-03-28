#include "cpu.h"

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
		defineRegion(0U,0x0U, 0x0U, 0U);
		defineRegion(1U, 0x0U, 0x0U, 0U);
		TZ_SAU_Enable();
	}else{
		TZ_SAU_Disable();
	}
}
