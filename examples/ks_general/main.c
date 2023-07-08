#include "bpf.h"

void launch_test_case(void);

int main(void){
    bpf_init();
    launch_test_case();
}