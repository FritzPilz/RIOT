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

#include "board.h"
#include "timex.h"
#include "ztimer.h"


void startSAU(void)
{
	__asm(	"svc 2 \n\t"	);
}

void endSAU(void)
{
	__asm(	"svc 3 \n\t"	);
}

void toggle(uint32_t t)
{
	switch(t) {
		case 0: LED0_TOGGLE; break;
		case 1: LED1_TOGGLE; break;
		case 2: LED2_TOGGLE; break;
		default: break; puts("The LED does not exist.");
	}
	ztimer_sleep(ZTIMER_USEC, 500*1000);
}

int main(void)
{
    toggle(0);
    toggle(0);
    while(1){

    }

    return 0;
}
