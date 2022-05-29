#ifndef SAU_H
#define SAU_H

typedef struct __SAU_Region__
{
	unsigned int volatile region;
	unsigned int volatile base;
	unsigned int volatile limit;
	unsigned int volatile nsc;
}SAU_Region;

SAU_Region * configureSAU(int enable, SAU_Region* regions);

void printRegions(SAU_Region * regions);

#endif
