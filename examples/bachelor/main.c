/*
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       main for my bachelor thesis
 *
 * @author      Fritz Pilz
 *
 * @}
 */

#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "timex.h"
#include "ztimer.h"
#include "arm_cmse.h"
#include "include/ns.h"
#include "include/main.h"
#include "include/SAU.h"

#define CPUID_NS 0xE002ED00

typedef void __attribute__((cmse_nonsecure_call)) nsfp(void);
SAU_Region regions[3] = {{0}};

unsigned int isSecure_S(void)
{
	return *(volatile unsigned int *) CPUID_NS;
}

void __attribute__((noinline)) startSAU(void)
{
	//toggle_S(0);
	__asm volatile (	"svc 2 \n\t"	);
	configureSAU(1, regions);
}

void __attribute((noinline)) endSAU(void)
{
	//toggle_S(0);
	__asm volatile (	"svc 3 \n\t"	);
	configureSAU(0, regions);
}

struct cmse_address_info testRegion(void* addr)
{
	struct cmse_address_info info = {0};
	__asm volatile (	"mov r0, %[addr] 	\n\t"
				"svc 4			\n\t"
				"mov %[info], r0	\n\t"
				: [info] "=r" (info)
				: [addr] "r" (addr)
				: "r0");
	return info;
}

void toggle_S(uint32_t t)
{
	switch(t) {
		case 0: LED0_TOGGLE; break;
		case 1: LED1_TOGGLE; break;
		case 2: LED2_TOGGLE; break;
		default: break;
	}
	//ztimer_sleep(ZTIMER_USEC, 500*1000);
}

extern char __NS_STACK_END__[];

void __attribute__((cmse_nonsecure_entry)) callback(nsfp* fp)
{
	toggle_S(1);
	toggle_S(1);
	fp();
}

int main(void)
{
	char buffer[33];

	__asm volatile("bkpt");	
	endSAU();
	startSAU();


	volatile unsigned int secure = isSecure_S();
	if(secure){
		toggle_S(1);
		toggle_S(1);
	}else{
		toggle_S(2);
		toggle_S(2);
	}

	puts("CPUID_NS:");
	puts(__itoa(secure,buffer,16));

	nsfp *fp = cmse_nsfptr_create((nsfp *) (((unsigned int) ns_test)));
	cmse_address_info_t info = cmse_TT_fptr(fp);
	puts("Info struct for ns_test:(address, secure-bit, sau-region, valid-region)");
	puts(__itoa((unsigned int)fp,buffer,16));
	puts(__itoa(info.flags.secure,buffer,2));
	puts(__itoa(info.flags.sau_region,buffer,2));
	puts(__itoa(info.flags.sau_region_valid,buffer,2));
	info = cmse_TT_fptr((unsigned int) (fp) | 0xC000000);
	puts("Info struct for ns_test:(address, secure-bit, sau-region, valid-region)");
	puts(__itoa((unsigned int)fp|0xC000000,buffer,16));
	puts(__itoa(info.flags.secure,buffer,2));
	puts(__itoa(info.flags.sau_region,buffer,2));
	puts(__itoa(info.flags.sau_region_valid,buffer,2));
	info = cmse_TT_fptr(__NS_STACK_END__);
	puts("Info struct for ns-stack:(address, secure-bit, sau-region, valid-region)");
	puts(__itoa((unsigned int)__NS_STACK_END__,buffer,16));
	puts(__itoa(info.flags.secure,buffer,2));
	puts(__itoa(info.flags.sau_region,buffer,2));
	puts(__itoa(info.flags.sau_region_valid,buffer,2));
	for(int i = 0; i < 3; ++i){
		puts("SAU-Region info (region,base,limit,nsc):");
		puts(__itoa(regions[i].region,buffer,16));
		puts(__itoa(regions[i].base,buffer,16));
		puts(__itoa(regions[i].limit,buffer,16));
		puts(__itoa(regions[i].nsc,buffer,16));
	}

	__asm volatile ("bkpt");
	if(cmse_is_nsfptr(fp)){
		puts("Pointer is Nonsecure");
		callback(fp);
	}else{
		puts("Pointer is secure");
	       	ns_test();
	}
	
	endSAU();
	while(1){
		toggle_S(2);
	}
}
