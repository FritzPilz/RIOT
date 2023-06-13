#include "kolmogorov_smirnov_test.h"
//#include "bpf/bpfapi/helpers.h"

//static const char* enter_msg = "Entered bpf-function\n";

uint32_t delta_kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx){
	//bpf_printf(enter_msg);
	for(int i = 0; i < STEPS; ++i){
		if(ctx->kolmogorov_ctx->value < i*STEP){
			continue;
		}else{
			++ctx->kolmogorov_ctx->empiricalFunction[i];
		}
	}
	int32_t result = 0;
	for(uint32_t i = 0; i < STEPS; ++i){
		int32_t F1 = ctx->kolmogorov_ctx->expectedFunction[i]; int32_t F2 = ctx->kolmogorov_ctx->empiricalFunction[i];
		int32_t diff = F1-F2;
		if(diff < 0){
			diff = -diff;
		}
		result = (diff > result) ? diff : result;
	}
	ctx->kolmogorov_ctx->result = (uint32_t)result;

	return 0;
}
