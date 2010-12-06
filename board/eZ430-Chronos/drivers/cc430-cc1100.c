#include <stdint.h>

#include <cpu.h>
#include <irq.h>
#include <arch_cc1100.h>

#warning CC430_CC1100 NOT WORKING
/* TODO: defines... */
#define CC1100_GDO0     (0)
#define CC1100_GDO1     (1)
#define CC1100_GDO2     (2)

int cc1100_get_gdo0(void) {
	return 	CC1100_GDO0;
}

int cc1100_get_gdo1(void) {
	return 	CC1100_GDO1;
}

int cc1100_get_gdo2(void) {
	return 	CC1100_GDO2;
}

void cc1100_before_send(void)
{
	// Disable GDO2 interrupt before sending packet
	cc1100_gdo2_disable();
}

void cc1100_after_send(void)
{
	// Enable GDO2 interrupt after sending packet
	cc1100_gdo2_enable();
}

void cc1100_gdo0_enable(void) {
}

void cc1100_gdo0_disable(void) {
}

void cc1100_gdo2_disable(void) {
}

void cc1100_gdo2_enable(void) {
}

void cc1100_init_interrupts(void) {
	uint8_t state = disableIRQ(); /* Disable all interrupts */
	restoreIRQ(state);  /* Enable all interrupts */
}

interrupt (PORT2_VECTOR) __attribute__ ((naked)) cc1100_isr(void){
    __enter_isr();
 	/* Check IFG */
    if (1 == 1) {
		cc1100_gdo2_irq();
    }
	else if (2 == 2) {
        cc1100_gdo0_irq();
	} else {
        puts("cc1100_isr(): unexpected IFG!");
	}
	__exit_isr();
}
