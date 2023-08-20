#include "include/SAU.h"

__attribute__((section(".secure"))) __attribute__((noinline)) unsigned int set_RNR(unsigned int region);
__attribute__((section(".secure"))) __attribute__((noinline)) unsigned int set_RBAR(unsigned int str);
__attribute__((section(".secure"))) __attribute__((noinline)) unsigned int set_RLAR(unsigned int end, unsigned int nsc);

__attribute__((noinline)) unsigned int read_memory(unsigned int location)
{
	return *(unsigned int *)location;
}

 __attribute__((noinline)) void  write_memory(unsigned int location, unsigned int value)
{
	*(unsigned int *)location = value;
	return;
}

 __attribute__((noinline)) void enable_SAU(void)
{
	//unsigned int tmp = read_memory(SAU_CTRL);
	//tmp = tmp | 0x1;
	write_memory(SAU_CTRL, 0x1);
	return;
}

__attribute__((noinline)) unsigned int* declare_NS(unsigned int str,unsigned int end,unsigned int region,unsigned int nsc,unsigned int * res)
{
	//check for valid arguments
	if(region > 7){
		//puts("Invalid region-number, NS memory is not set.\n");
		return (unsigned int *)0;
	}
	res[0] = set_RNR(region);
	res[1] = set_RBAR(str);
	res[2] = set_RLAR(end, nsc);
	return res;
}

__attribute__((noinline)) void disable_SAU(void)
{
	unsigned int tmp = read_memory(SAU_CTRL);
	tmp = tmp & 0xFFFFFFFC;
	write_memory(SAU_CTRL, tmp);
	return;
}

__attribute__((noinline)) unsigned int set_RNR(unsigned int region)
{
	unsigned int tmp = read_memory(SAU_RNR);
	tmp = tmp & 0xFFFFFF00;
	/* My understanding is that each memory region is accessible by setting exactly
	 * one bit of the 8 region bits. It is implied due to the fact that the
	 * documentation mentions only 8 regions.*/
	unsigned int region_mask = 1 << (region-1);
	tmp = tmp | region_mask;
	write_memory(SAU_RNR, tmp);
	return tmp;
}

__attribute__((noinline)) unsigned int set_RBAR(unsigned int str)
{
	str = str & 0xFFFFFFE0;
	write_memory(SAU_RBAR, str);
	return str;
}

__attribute__((noinline)) unsigned int __attribute__((noinline)) set_RLAR(unsigned int end, unsigned int nsc)
{
	end = end & 0xFFFFFFF0;
	if(nsc){
		end = end | 0x2;
	}
	end = end | 0x1;
	write_memory(SAU_RLAR, end);
	end = end | 0x1F;
	return end;
}	
