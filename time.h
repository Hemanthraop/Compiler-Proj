#include <time.h>

                clock_t    start_time, end_time;

                double total_CPU_time, total_CPU_time_in_seconds;

                start_time = clock();

                                                // invoke your lexer and parser here

                end_time = clock();

                total_CPU_time  =  (double) (end_time - start_time);

                total_CPU_time_in_seconds =   total_CPU_time / CLOCKS_PER_SEC;

             // Print both total_CPU_time and total_CPU_time_in_seconds