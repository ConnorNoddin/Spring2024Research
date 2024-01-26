#include <stdio.h>
#include <stdlib.h>
#include "papi.h"

void handle_error (int retval)
{
    printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
    exit(1);
}

int main()
{ 
    float real_time, proc_time, mflops;
    long long flpops;
    int retval;
    float rand = 1.363234643234;

    retval = PAPI_flops_rate(PAPI_FP_OPS, &real_time, &proc_time, &flpops, &mflops);
    if (retval != PAPI_OK) { 
        printf("Could not initialize PAPI_flops.\n");
        printf("Your platform may not support floating point operation event.\n"); 
        handle_error(retval);
  }

  /* Do some computation here */
    

    for (int i = 0; i < 1000000; i++) {
        rand = rand*rand;
    }
    printf("Result is %f\n", rand);


  retval = PAPI_flops_rate(PAPI_FP_OPS, &real_time, &proc_time, &flpops, &mflops);
  if (retval != PAPI_OK)
      handle_error(retval);

  /* Print real time, proc time, flpops, and MFLOPS */
  printf("Real_time: %f, Proc_time: %f, flpops: %lld, MFLOPS: %f\n", 
         real_time, proc_time, flpops, mflops);

  exit(0);
}
