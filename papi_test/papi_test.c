#include <papi.h>
#include <stdio.h>

/*
 * gcc -O2 -Wall -o papi_test papi_test.c -lpapi 
*/

int main() {
  int retval;
  float rand = 1.363234643234;
  long long count;

  /* Initialize Papi */
  retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT) {
    fprintf(stderr, "Error initializing PAPI! %s\n", PAPI_strerror(retval));
    return 0;
  }

  /* Create EventSet */
  int eventset = PAPI_NULL;

  retval = PAPI_create_eventset(&eventset);
  if (retval != PAPI_OK) {
    fprintf(stderr, "Error creating eventset! %s\n", PAPI_strerror(retval));
  }

  /* Add our measurements Here */
  retval = PAPI_add_named_event(eventset, "PAPI_TOT_CYC");
  if (retval != PAPI_OK) {
    fprintf(stderr, "Error adding PAPI_TOT_CYC: %s\n", PAPI_strerror(retval));
  }
  
  retval = PAPI_add_named_event(eventset, "PAPI_TOT_INS");
  if (retval != PAPI_OK) {
    fprintf(stderr, "Error adding PAPI_TOT_INS: %s\n", PAPI_strerror(retval));
  }

  /* Begin Measurement */
  PAPI_reset(eventset);
  retval = PAPI_start(eventset);
  if (retval != PAPI_OK) {
    fprintf(stderr, "Error starting CUDA: %s\n", PAPI_strerror(retval));
  }
  
  /* Do some computation here */
  for (int i = 0; i < 10000000; i++) {
    rand = rand * 1.00000000001;
  }
  printf("Result is %f\n", rand);

  /* End Measurement */
  retval = PAPI_stop(eventset, &count);
  if (retval != PAPI_OK) {
    fprintf(stderr, "Error stopping:  %s\n", PAPI_strerror(retval));
  } else {
    printf("Measured %lld cycles\n", count);
  }

  /* Cleanup */
  PAPI_cleanup_eventset(eventset);
  PAPI_destroy_eventset(&eventset);

  return 0;
}
