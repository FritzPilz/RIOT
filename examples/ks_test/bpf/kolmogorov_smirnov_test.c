#include "kolmogorov_smirnov_test.h"
#include "bpf/bpfapi/helpers.h"

KS_Test_Results* kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx){
	uint32_t F_s1[STEPS]; uint32_t F_s2[STEPS]; uint32_t observations = 0; uint32_t max = 0;
    //get the occurences within i*STEP > x >= (i+1)*STEP from the first array and save them in function F_s1
	for(uint32_t i = 1; i <= STEPS; ++i){
		// TODO: Fix condition in for-loop to take previous iterations of the outer loop uint32_to account (i.e. the new length)
		for(uint32_t j = 0; j < ctx->kolmogorov_ctx->setup->len1; ++j){
			if(i*STEP <= ctx->kolmogorov_ctx->setup->arr1[observations]){
				break;
			}
			++observations;
		}
		F_s1[i-1] = observations;
	}
	observations = 0;
    //get the occurences within i*STEP > x >= (i+1)*STEP from the second array and save them in function F_s2
	for(uint32_t i = 1; i <= STEPS; ++i){
		for(uint32_t j = 0; j < ctx->kolmogorov_ctx->setup->len2; ++j){
			if(i*STEP <= ctx->kolmogorov_ctx->setup->arr2[observations]){
				break;
			}
			++observations;
		}
		F_s2[i-1] = observations;
	}
    //check for highest difference
	for(uint32_t i = 0; i < STEPS; ++i){
		uint32_t diff = F_s1[i]-F_s2[i];
		diff = (diff > 0) ? diff : -diff;
		max = (diff > max) ?  diff : max;
	}
	static const char print_str[] = "Max difference: %i\n";
	bpf_printf(print_str, max);
	ctx->kolmogorov_ctx->result->max_diff = max;
	ctx->kolmogorov_ctx->result->p_value = 0;
	return 0;
}