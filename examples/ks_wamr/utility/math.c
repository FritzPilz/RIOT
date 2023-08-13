#include "include/math.h"

float average(float* observations, int32_t values){
    float sum = 0.0;
    for(int i = 0; i < values; ++i){
        sum += observations[i];
    }
    return sum/values;
}

float variance(float* observations, int32_t values){
    float average_x = average(observations, values);
    float sum = 0;
    for(int i = 0; i < values; ++i){
        sum += (observations[i] - average_x)*(observations[i] - average_x);
    }
    return sum;
}

float covariance(float* observations_x, float* observations_y, int32_t values){
    float average_x = average(observations_x, values); float average_y = average(observations_y, values);
    float sum = 0;
    for(int i = 0; i < values; ++i){
        sum += (observations_x[i] - average_x)*(observations_y[i] - average_y);
    }
    return sum;
}

float linear_function(float a, float b, float x){
    return a+b*x;
}