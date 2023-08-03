#include "../../utility/utility_ks.h"
#include "nrf52_temp_read_only_bpf.h"

inline uint64_t read_memory(volatile uint64_t address);
inline void write_memory(volatile uint64_t address, volatile uint64_t value);

uint32_t delta_kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx){
	write_memory(TASKS_START, 1);
	while(read_memory(EVENTS_DATARDY)==0){}
	write_memory(EVENTS_DATARDY, 0);
	ctx->kolmogorov_ctx->value = read_memory(TEMP);
	write_memory(TASKS_STOP, 1);

	return ctx->kolmogorov_ctx->value;
}

inline uint64_t read_memory(volatile uint64_t address){
	return *(volatile uint64_t*) address;
}

inline void write_memory(volatile uint64_t address, volatile uint64_t value){
	*(volatile uint64_t *) address = value;
}