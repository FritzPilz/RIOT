#include "cpu.h"
#include "arm_cmse.h"
#include "include/SAU.h"
#include <stdio.h>
#include <stdlib.h>

extern char __START_NS__[], __END_NS__[];
extern char __START_NSC__[], __END_NSC__[];
extern char __NS_STACK_END__[], __NS_STACK_START__[];

typedef unsigned int volatile ui_v;

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
//		toggle_S(i%3);
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
	}else{
		TZ_SAU_Disable();
	}
	return regions;
}

void printRegions(SAU_Region* regions)
{
	char buffer[33];

	puts("Info for configured regions(num, region, base-address, limit-address, isNSC):");
	for(int i = 0; i < 3; ++i)
	{
		puts(__itoa(i,buffer,10));
		puts(__itoa(regions[i].region,buffer,10));
		puts(__itoa(regions[i].base,buffer,16));
		puts(__itoa(regions[i].limit,buffer,16));
		puts(__itoa(regions[i].nsc,buffer,2));
	}
	void* fp = (void *) regions[0].base;

	cmse_address_info_t info = cmse_TT_fptr(fp);
	puts("Info struct for ns_region:(address, secure-bit, sau-region, valid-region)");
	puts(__itoa((unsigned int)fp,buffer,16));
	puts(__itoa(info.flags.secure,buffer,2));
	puts(__itoa(info.flags.sau_region,buffer,2));
	puts(__itoa(info.flags.sau_region_valid,buffer,2));

	fp = (void *) regions[0].base;
	info = cmse_TT_fptr(fp);
	puts("Info struct for ns_region:(address, secure-bit, sau-region, valid-region)");
	puts(__itoa((unsigned int)fp,buffer,16));
	puts(__itoa(info.flags.secure,buffer,2));
	puts(__itoa(info.flags.sau_region,buffer,2));
	puts(__itoa(info.flags.sau_region_valid,buffer,2));
}
