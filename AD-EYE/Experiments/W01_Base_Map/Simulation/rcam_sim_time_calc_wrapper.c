
/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif



/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#include <math.h>
#include <sys/time.h>

#ifdef _WIN32
#include <simstruc.h>
#else
#include <stdio.h>
#endif

struct timeval rcam_begin, rcam_end;
double rcam_current_time, rcam_step_duration, rcam_tot_time, rcam_prev_time;
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void rcam_sim_time_calc_Start_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
gettimeofday(&rcam_begin, 0);

rcam_prev_time = 0;
rcam_tot_time = 0;
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void rcam_sim_time_calc_Outputs_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
gettimeofday(&rcam_end, 0);

long rcam_seconds = rcam_end.tv_sec - rcam_begin.tv_sec;
long rcam_micro_seconds = rcam_end.tv_usec - rcam_begin.tv_usec;
rcam_current_time = rcam_seconds + rcam_micro_seconds*1e-6;

rcam_step_duration = rcam_current_time - rcam_prev_time;
rcam_prev_time = rcam_current_time;
rcam_tot_time += rcam_step_duration;

#ifdef _WIN32
ssPrintf("Current time: %.3f\n", rcam_current_time);
ssPrintf("rcam step duration: %.3f\n", rcam_step_duration);
#else
printf("Current time: %.3f\n", rcam_current_time);
printf("rcam step duration: %.3f\n", rcam_step_duration);
#endif
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}


