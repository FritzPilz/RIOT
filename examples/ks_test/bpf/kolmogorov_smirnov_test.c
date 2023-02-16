#include "kolmogorov_smirnov_test.h"

KS_Test_Results* kolmogorov_smirnov_test(KS_Context* ctx){
	int F_s1[STEPS]; int F_s2[STEPS]; int observations1 = 0.0; int observations2 = 0.0; int max = 0.0;
    //get the occurences within i*STEP > x >= (i+1)*STEP from the first array and save them in function F_s1
	for(int i = 1; i <= STEPS; ++i){
		while(i*STEP <= ctx->setup->arr1[(int)observations1] && observations1 < ctx->setup->len1){
			++observations1;
		}
		F_s1[i-1] = observations1;
	}
    //get the occurences within i*STEP > x >= (i+1)*STEP from the second array and save them in function F_s2
	for(int i = 1; i <= STEPS; ++i){
		while(i*STEP <= ctx->setup->arr2[(int)observations2] && observations2 < ctx->setup->len2){
			++observations2;
		}
		F_s2[i-1] = observations2;
	}
    //check for highest difference
	for(int i = 0; i < STEPS; ++i){
		int diff = F_s1[i]-F_s2[i];
		diff = (diff > 0) ? diff : -diff;
		max = (diff > max) ?  diff : max;
	}
	ctx->result->max_diff = max;
	ctx->result->p_value = 0;
	return 0;
}