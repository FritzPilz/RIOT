#include "kolmogorov_smirnov_test.h"
//#include "bpf/bpfapi/helpers.h"

//static const char* enter_msg = "Entered bpf-function\n";

uint32_t delta_kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx){
//	bpf_printf(enter_msg);
	for(int i = 0; i < STEPS; ++i){
		if(ctx->kolmogorov_ctx->value < i*STEP){
			continue;
		}else{
			++ctx->kolmogorov_ctx->empiricalFunction[i];
		}
	}
	uint32_t result = 0;
	for(uint32_t i = 0; i < STEPS; ++i){
		int32_t diff = ctx->kolmogorov_ctx->expectedFunction[i] - ctx->kolmogorov_ctx->empiricalFunction[i];
		if(diff < 0){
			diff = -diff;
		}
		result = (diff > result) ? diff : result;
	}
	ctx->kolmogorov_ctx->result = result;

	return 0;
}
