#include "../../utility/include/shared_ks.h"
#include "bpf/bpfapi/helpers.h"

uint32_t kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx){
	volatile int x = 0;
	for(int i = 0; i < ctx->kolmogorov_ctx->value; ++i){
		++x;
	}
	ctx->kolmogorov_ctx->value = x;

	return ctx->kolmogorov_ctx->value;
}