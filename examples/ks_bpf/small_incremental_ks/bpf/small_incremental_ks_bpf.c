#include "../../utility/include/shared_ks.h"
#include "bpf/bpfapi/helpers.h"

uint32_t kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx){
	volatile int x = 0;
	for(int i = 0; i < ctx->kolmogorov_ctx->value; ++i){
		++x;
	}
	ctx->kolmogorov_ctx->value = x;
	for(int i = 0; i < ctx->kolmogorov_ctx->values; ++i){
		if(ctx->kolmogorov_ctx->value < i*ctx->kolmogorov_ctx->value_range){
			continue;
		}else{
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

	return ctx->kolmogorov_ctx->value;
}