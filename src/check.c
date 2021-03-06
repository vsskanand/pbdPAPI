/* This Source Code Form is subject to the terms of the BSD 2-Clause
 * License. If a copy of the this license was not distributed with this
 * file, you can obtain one from http://opensource.org/licenses/BSD-2-Clause. */

// Copyright 2014, Schmidt.  All rights reserved.


#include "pbdPAPI.h"

#define NO_COUNTERS -2
#define NOT_ENOUGH_COUNTERS -1

SEXP papi_check_counters(SEXP n)
{
  int ncounters = PAPI_num_counters();

  SEXP RET;
  PROTECT(RET = allocVector(INTSXP, 1));


  if (ncounters <= 0)
    INTEGER(RET)[0] = NO_COUNTERS;
  else if (ncounters < INTEGER(n)[0])
    INTEGER(RET)[0] = NOT_ENOUGH_COUNTERS;
  else
    INTEGER(RET)[0] = ncounters;


  UNPROTECT(1);
  return RET;
}
