#include "bpf/shared.h"

float average(float* observations, int32_t values);
float variance(float* observations, int32_t values);
float covariance(float* observations_x, float* observations_y, int32_t values);
float linear_function(float a, float b, float x);