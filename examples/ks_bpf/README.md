# Benchmarks using ks_test

This project contains two benchmarks for the femtocontainer implementation using the kolmogorov-smirnov-test to determine whether a generated data set follows an expected distribution on the data.
The project is written to control some parameters of the benchmark from within the console. These parameters are:

- TESTCASE:         Determines which benchmark is run. The value following the TESTCASE argument most be one of subdirectories in this directory excluding utility and bin (Default: nrf52_temp_read_bpf.c)
- FUNCTIONS_SIZE:   Determines the size of the expected and empiricl function and is responsible for the amount of data shown in the table (Default: 32)
- VERBOSE_DEBUG:    Determines that a list with the results of the benchmark_runs is printed, if the value equals 1. Otherwise these logs a omitted (Default: 0)
