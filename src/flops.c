#include <R.h>
#include <Rinternals.h>

#include <stdio.h>
#include <stdlib.h>
#include "papi.h"

/***********************************************************************
 * if PAPI_FP_OPS is a derived event in your platform, then your       * 
 * platform must have at least three counters to support PAPI_flops,   *
 * because PAPI needs one counter to cycles. So in UltraSparcIII, even *
 * the platform supports PAPI_FP_OPS, but UltraSparcIII only has  two  *
 * available hardware counters and PAPI_FP_OPS is a derived event in   *
 * this platform, so PAPI_flops returns an error.                      *
 ***********************************************************************/

#define OFF 0
#define ON 1

SEXP papi_get_flops(SEXP onoff)
{ 
  float real_time, proc_time,mflops;
  long long flpops;
  float ireal_time, iproc_time, imflops;
  long long iflpops;
  int retval;
  
  if (INTEGER(onoff)[0] == ON)
  {
    retval = PAPI_flops(&ireal_time, &iproc_time, &iflpops, &imflops);
    
    if (retval < PAPI_OK)
    { 
      printf("Could not initialise PAPI_flops \n");
      printf("Your platform may not support floating point operation event.\n"); 
      printf("retval: %d\n", retval);
      exit(1);
    }
  }
  else
  {
    retval = PAPI_flops(&real_time, &proc_time, &flpops, &mflops);
    
    if (retval < PAPI_OK)
    {    
      printf("retval: %d\n", retval);
      exit(1);
    }
    printf("Real_time: %f Proc_time: %f Total flpops: %lld MFLOPS: %f\n", 
           real_time, proc_time, flpops, mflops);
    
    int Events[3] = {PAPI_TOT_CYC, PAPI_FP_INS, PAPI_FP_OPS};
    long_long values[3];
/*    retval = */
    PAPI_stop_counters(values, 3);
/*    if (retval != PAPI_OK)*/
/*      handle_error(1);*/
  }
  
  return R_NilValue;
}
