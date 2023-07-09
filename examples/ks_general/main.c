#include "bpf.h"
#include "utility/utility_ks.h"

int32_t expected_function[function_size];
int32_t empirical_function[function_size];

void launch_test_case(void);

int main(void){
    bpf_init();
    launch_test_case();
}