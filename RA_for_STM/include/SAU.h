/* This file contains all the definitions required to operate the SAU
 * The SAU must be accessed from priviliged mode
 * Please note that configuring the SAU to declare memory as secure or
 * non-secure requires to know the configuration oft the IDAU
 * Also note that secure and non-secure state have a different view on the
 * system. You can read more in TODO add source
 * According to the STM documentation there are 8 memory regions which can be configured.
 * You can read about them in AN5347 at the stm website. (*)
 * When SAU is enabled, memory that is covered by the SAU is secure. Memory is enabled by
 * using SAU_RLAR:
 * NS: SAU_RLAR & 0x1 = 1 and SAU_RLAR & 0x2 = 0
 * S: SAU_RLAR & 0x1 = 1 and SAU_RLAR & 0x2 = 1
 * TODO: Add information about the way the flash controller operates */

/* Question:
 * Should we use CMSIS, or would that be too much overhead? */

/*
 * How to configure a SAU-Region:
 * 1. Switch to a SAU region by writing the desired region to SAU_RNR
 * 2. Write the base address in SAU_RBAR and the limit address in SAU_RLAR 
 * 3. Enable SAU through SAU_CTRL register and declare all ALLNS
 * Note: Once the SAU is started every Memory region that is not being tracked by the SAU is secure */

/* (*)
 * ||==============================================||
 * ||           0x0000 0000 - 0x07FF FFFF          ||	<-- IDAU: NS, code, external memories if remapped
 * ||==============================================||
 * ||           0x0800 0000 - 0x0BFF FFFF          ||   <-- IDAU: NS, code in Flash Memory and SRAM
 * ||==============================================||
 * ||           0x0C00 0000 - 0x0FFF FFFF          ||   <-- IDAU: NSC, code in Flash Memory and SRAM
 * ||==============================================||
 * ||           0x1000 0000 - 0x1FFF FFFF          ||   <-- IDAU: NS, code, external memory when remapped
 * ||==============================================||
 * ||           0x2000 0000 - 0x2FFF FFFF          ||   <-- IDAU: NS, SRAM
 * ||==============================================||
 * ||           0x3000 0000 - 0x3FFF FFFF          ||   <-- IDAU: NSC, SRAM
 * ||==============================================||
 * ||           0x4000 0000 - 0x4FFF FFFF          ||   <-- IDAU: NS, Peripherals
 * ||==============================================||
 * ||           0x5000 0000 - 0x5FFF FFFF          ||   <-- IDAU: NSC, Peripherals
 * ||==============================================||
 * ||           0x6000 0000 - 0xDFFF FFFF          ||   <-- IDAU: NS, external memory
 * ||==============================================||
 *
 * Source: AN5347 ARM TrustZone features for STM32L5 and STM32U5 Series p. 6
 * */

#define SAU_CTRL 0xE000EDD0			// SAU Control Register: must be written with a word, 0x1 enables the SAU, 0x2 sets the entire memory to ns
#define SAU_TYPE 0xE000EDD4			// SAU Type Register: determines how many SAU regions are implemented
#define SAU_RNR 0xE000EDD8			// SAU Region Number Register: selects currently accessed SAU region, usage from bit 0 to 7 possible
#define SAU_RBAR 0xE000EDDC			// SAU Region Base register: base address of current SAU region, bits 0 to 4 are reserved
#define SAU_RLAR 0xE000EDE0			// SAU Region Limit Register: limit address of current SAU regions, used to define an area as nsc

//Reads the memory at a specific location
__attribute__((section(".secure"))) unsigned int read_memory(unsigned int location);

//Writes a value to a specific location
 __attribute__((section(".secure"))) void write_memory(unsigned int location, unsigned int value);

//Enable SAU. To be called, after regions are declared as NS
 __attribute__((section(".secure"))) void enable_SAU(void);

/* Expects a start address, an end address and a number n, 0 <= n < 8 and a bool nsc
 * If nsc == 0 the region is not defined as NSC, otherwise it is
 * If this function is called multiple times with the same region number, previous calls are
 * overwritten.*/
 __attribute__((section(".secure"))) unsigned int* declare_NS(unsigned int str, unsigned int end, unsigned int region, unsigned int nsc, unsigned int* res);

 __attribute__((section(".secure"))) void disable_SAU(void);
