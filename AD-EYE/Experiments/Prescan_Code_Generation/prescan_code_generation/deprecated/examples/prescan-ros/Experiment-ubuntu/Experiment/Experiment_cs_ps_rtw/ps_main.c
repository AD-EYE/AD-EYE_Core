/* PreScan PS Target Main File
 * Based on classic_main.c
 *
 * Copyright 1994-2012 The MathWorks, Inc.
 *
 * File    : classic_main.c
 *
 * Abstract:
 *      A Generic "Real-Time (single tasking or pseudo-multitasking,
 *      statically allocated data)" main that runs under most
 *      operating systems.
 *
 *      This file may be a useful starting point when targeting a new
 *      processor or microcontroller.
 *
 *
 * Compiler specified defines:
 *	RT              - Required.
 *      MODEL=modelname - Required.
 *	NUMST=#         - Required. Number of sample times.
 *	NCSTATES=#      - Required. Number of continuous states.
 *      TID01EQ=1 or 0  - Optional. Only define to 1 if sample time task
 *                        id's 0 and 1 have equal rates.
 *      MULTITASKING    - Optional. (use MT for a synonym).
 *	SAVEFILE        - Optional (non-quoted) name of .mat file to create.
 *			  Default is <MODEL>.mat
 */

#include "rtwtypes.h"

extern int_T modelMain(int_T argc, const char *argv[]);

/* Function: main =============================================================
 *
 * Abstract:
 *      Execute model on a generic target such as a workstation.
 */
int_T main(int_T argc, const char *argv[])
{
 

    return modelMain(argc, argv);

} /* end main */



/* EOF: ps_main.c */
