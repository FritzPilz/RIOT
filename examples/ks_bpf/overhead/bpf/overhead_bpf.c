#include "../../utility/include/shared_ks.h"
#include "bpf/bpfapi/helpers.h"

uint32_t kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx){
	ctx->kolmogorov_ctx->value = 100;
	ctx->kolmogorov_ctx->result = 100;

	return ctx->kolmogorov_ctx->value;
}