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

#define CPUID_NS 0xE002ED00

typedef void __attribute__((cmse_nonsecure_call)) nsfp(void);

unsigned int isSecure_S(void)
{
	return *(volatile unsigned int *) CPUID_NS;
}

void startSAU(void)
{
	__asm volatile (	"svc 2 \n\t"	);
}

void endSAU(void)
{
	__asm volatile (	"svc 3 \n\t"	);
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
	ztimer_sleep(ZTIMER_USEC, 500*1000);
}

__attribute__((cmse_nonsecure_entry)) void callback(nsfp* fp)
{
	toggle_S(1);
	toggle_S(1);
	__asm volatile ("bkpt 2");
	fp();
}

int main(void)
{
	char buffer[33];
	startSAU();

	volatile unsigned int secure = isSecure_S();
	if(secure){
		toggle_S(1);
		toggle_S(1);
	}else{
		toggle_S(2);
		toggle_S(2);
	}

	nsfp *fp = (nsfp *) (ns_test);
	struct cmse_address_info info = testRegion((void *) fp);
	puts("Info struct for ns_test:(secure-bit, sau-region, valid-region)");
	puts(__itoa(info.secure,buffer,2));
	puts(__itoa(info.sau_region,buffer,2));
	puts(__itoa(info.sau_region_valid,buffer,2));
	fp = cmse_nsfptr_create(fp);
	callback(fp);
	
	endSAU();
	while(1){
		toggle_S(2);
	}
}
