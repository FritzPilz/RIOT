ENTRY(ns_test)

MEMORY
{
	RAM (xrw)	: ORIGIN = 0x20018000, LENGTH = 96K
	ROM (rx)	: ORIGIN = 0x8040000, LENGTH = 256K
}

_NS_Stack_Size = 0x200;

SECTIONS
{
	.test_start:
	{
		. = ALIGN(32);
		KEEP(*(.test_start))
		. = ALIGN(32);
	} > ROM
	.test:
	{
		. = ALIGN(32);
		KEEP(*(.test))
		. = ALIGN(32);
	} > ROM
	.stack:
	{
		. = ALIGN(32);
		KEEP(*(.stack)	/* End of the stack */
		. += _NS_Stack_Size;
		PROVIDE(__NS_STACK_START__);
		. = ALIGN(32);
	} > RAM
}
