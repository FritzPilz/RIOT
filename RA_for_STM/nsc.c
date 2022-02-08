#include "include/nsc.h"
#include "include/ns.h"

__attribute((section(".nsc"))) void veneer_func(void)
//Should be executed in NSC
{
	__asm
	(	"SG			\n\t"
		"b secure_test		\n\t"
	);
}
