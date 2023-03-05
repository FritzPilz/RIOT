#include "kolmogorov_smirnov_test.h"
#include "bpf/bpfapi/helpers.h"

static const char enter_msg[] = "Entered bpf-application\n";
static const char count_msg[] = "Loop: %i, Count: %i\n";
static const char diff_msg[] = "%i - %i = %i\n";
static const char find_msg[] = "Compared samples, search for maximum difference\n";
static const char break_msg[] = "Check where program breaks\n";

KS_Test_Results* kolmogorov_smirnov_test(kolmogorov_ctx_t* ctx){
	bpf_printf(enter_msg);
	int32_t F_s1[STEPS]; int32_t F_s2[STEPS]; int32_t observations = 0; int32_t max = 0;
    //get the occurences within i*STEP > x >= (i+1)*STEP from the first array and save them in function F_s1
	for(uint32_t i = 0; i < STEPS; ++i){
		for(uint32_t j = observations; j < ctx->kolmogorov_ctx->setup->len1; ++j){
			bpf_printf(count_msg, 1, j);
			if(ctx->kolmogorov_ctx->setup->arr1[j] > (i+1)*STEP){
				break;
			}
			++observations;
		}
		F_s1[i] = observations;
	}
	observations = 0;
    //get the occurences within i*STEP > x >= (i+1)*STEP from the second array and save them in function F_s2
	for(uint32_t i = 0; i < STEPS; ++i){
		for(uint32_t j = observations; j < ctx->kolmogorov_ctx->setup->len2; ++j){
			bpf_printf(count_msg, 2, j);
			if(ctx->kolmogorov_ctx->setup->arr2[j] > (i+1)*STEP){
				break;
			}
			++observations;
		}
		F_s2[i] = observations;
	}
	bpf_printf(find_msg);
    //check for highest difference
	for(uint32_t i = 0; i < STEPS; ++i){
		int32_t diff = F_s1[i]-F_s2[i];
		if(diff < 0){
			diff = -diff;
		}
		bpf_printf(diff_msg, F_s1[i], F_s2[i], diff);
		max = (diff > max) ? diff : max;
	}
	static const char print_str[] = "Max difference: %i\n";
	bpf_printf(print_str, max);
	ctx->kolmogorov_ctx->result->max_diff = max;
	ctx->kolmogorov_ctx->result->p_value = 0;
	return 0;
}
