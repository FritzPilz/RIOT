#include "kolmogorov_smirnov_test.h"
//#include "bpf/bpfapi/helpers.h"

//static const char* enter_msg = "Entered bpf-function\n";

uint32_t delta_kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx){
//	bpf_printf(enter_msg);
	for(int i = 0; i < STEPS; ++i){
		if(ctx->kolmogorov_ctx->value < (i+1)*STEPS){
			continue;
		}else{
			++ctx->kolmogorov_ctx->empiricalFunction[i];
		}
	}
	ctx->kolmogorov_ctx->result = 0;
	for(int i = 0; i < STEPS; ++i){
		int32_t tmp = (ctx->kolmogorov_ctx->expectedFunction[i]) - (ctx->kolmogorov_ctx->empiricalFunction[i]);
		if(tmp < 0){
			tmp = -tmp;
		}
		if(tmp > ctx->kolmogorov_ctx->result){
			ctx->kolmogorov_ctx->result = tmp;
		}	
	}

	return 0;
}
