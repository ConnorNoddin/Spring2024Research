#include <papi.h>
#include <stdio.h>

/*
 * gcc -O2 -Wall -o papi_test papi_test.c -lpapi
 */

/* vscode test */

#define NUM_EVENTS 2

int main()
{
  int retval;
  int i;
  float rand = 1.363234643234;
  long long values[NUM_EVENTS];
  float IPC;

  /* Initialize Papi */
  retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT)
  {
    fprintf(stderr, "Error initializing PAPI! %s\n", PAPI_strerror(retval));
    return 0;
  }

  /* Create EventSet */
  int eventset = PAPI_NULL;

  retval = PAPI_create_eventset(&eventset);
  if (retval != PAPI_OK)
  {
    fprintf(stderr, "Error creating eventset! %s\n", PAPI_strerror(retval));
  }

  /* Add PAPI_TOT_CYC */
  retval = PAPI_add_named_event(eventset, "PAPI_TOT_CYC");
  if (retval != PAPI_OK)
  {
    printf("Trouble adding PAPI_TOT_CYC: %s\n", PAPI_strerror(retval));
  }

  /* Add PAPI_TOT_INS */
  retval = PAPI_add_named_event(eventset, "PAPI_TOT_INS");
  if (retval != PAPI_OK)
  {
    printf("Trouble adding PAPI_TOT_INS: %s\n", PAPI_strerror(retval));
  }

  /* Remove processor from idle state */
  for (i = 0; i < INT_MAX; i++)
  {
    rand = rand / 1.001;
  }

  /* Begin Measurement */
  PAPI_reset(eventset);
  retval = PAPI_start(eventset);
  if (retval != PAPI_OK)
  {
    fprintf(stderr, "Error starting CUDA: %s\n", PAPI_strerror(retval));
  }

  /* Do some computation here */
  for (i = 0; i < INT_MAX; i++)
  {
    rand = rand * 1.0001;
  }
  printf("Result is %f\n", rand);

  /* End Measurement */
  retval = PAPI_stop(eventset, values);
  if (retval != PAPI_OK)
  {
    fprintf(stderr, "Error stopping:  %s\n", PAPI_strerror(retval));
  }
  else
  {
    printf("Measured %lld cycles\n", values[0]);
    printf("Measured %lld instructions\n", values[1]);
  }

  IPC = (values[1] * 1.0) / (values[0] * 1.0);
  printf("Measured IPC is: %f\n", IPC);

  /* Cleanup */
  PAPI_cleanup_eventset(eventset);
  PAPI_destroy_eventset(&eventset);

  return 0;
}
