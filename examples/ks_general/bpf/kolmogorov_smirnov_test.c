#include "kolmogorov_smirnov_test.h"
#include "bpf/bpfapi/helpers.h"

//const char* begin = "In bpf...\n";
//const char* increment = "Increment\n";

inline uint64_t read_memory(volatile uint64_t address);
inline void write_memory(volatile uint64_t address, volatile uint64_t value);

uint32_t delta_kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx){
	//bpf_printf(begin);
	//Read value from sensor
	write_memory(TASKS_START, 1);
	
	while(read_memory(EVENTS_DATARDY)==0){}
	write_memory(EVENTS_DATARDY, 0);
	
	ctx->kolmogorov_ctx->value = read_memory(TEMP);
	write_memory(TASKS_STOP, 1);

	//Put the read value in the correct position of the read 
	for(int i = 0; i < ctx->kolmogorov_ctx->values; ++i){
		if(ctx->kolmogorov_ctx->value < i*ctx->kolmogorov_ctx->valueRange){
			continue;
		}else{
			//bpf_printf(increment);
			++ctx->kolmogorov_ctx->empirical_function[i];
		}
	}
	int32_t result = 0;
	for(uint32_t i = 0; i < ctx->kolmogorov_ctx->values; ++i){
		int32_t F1 = ctx->kolmogorov_ctx->expected_function[i]; int32_t F2 = ctx->kolmogorov_ctx->empirical_function[i];
		int32_t diff = F1-F2;
		if(diff < 0){
			diff = -diff;
		}
		result = (diff > result) ? diff : result;
	}
	ctx->kolmogorov_ctx->result = (uint32_t)result;

	return 0;
}

inline uint64_t read_memory(volatile uint64_t address){
	return *(volatile uint64_t*) address;
}

inline void write_memory(volatile uint64_t address, volatile uint64_t value){
	*(volatile uint64_t *) address = value;
}