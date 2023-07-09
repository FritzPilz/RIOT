#include "bpf.h"
#include "ks_test.h"
#include "utility/utility_ks.h"

int32_t expected_function[function_size];
int32_t empirical_function[function_size];

int main(void){
    bpf_init();
    launch_test_case();
}