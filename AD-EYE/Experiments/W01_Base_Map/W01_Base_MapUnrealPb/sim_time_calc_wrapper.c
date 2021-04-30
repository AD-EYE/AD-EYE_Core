
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

struct timeval begin, end;
double current_time, step_duration, tot_time, prev_time, max_step, min_step;
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
void sim_time_calc_Start_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
gettimeofday(&begin, 0);

prev_time = 0;
max_step = 0;
min_step = 10000;
tot_time = 0;

#ifdef _WIN32
ssPrintf("Simulation starts here\n");
#else
printf("Simulation starts here\n");
#endif
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void sim_time_calc_Outputs_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
gettimeofday(&end, 0);

long seconds = end.tv_sec - begin.tv_sec;
long microseconds = end.tv_usec - begin.tv_usec;
current_time = seconds + microseconds*1e-6;

step_duration = current_time - prev_time;
prev_time = current_time;
tot_time += step_duration;

#ifdef _WIN32
ssPrintf("%.3f\n", step_duration);
#else
printf("%.3f\n", step_duration);
#endif

if (step_duration > max_step){
    max_step = step_duration;
}

if (step_duration < min_step){
    min_step = step_duration;
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Terminate function
 *
 */
void sim_time_calc_Terminate_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_BEGIN --- EDIT HERE TO _END */
#ifdef _WIN32
ssPrintf("Simulation ends here\n");
ssPrintf("S function simulation time measured: %.3f seconds.\n", current_time);
ssPrintf("Total step: %.3f\n", tot_time);
ssPrintf("Max step: %.3f\n", max_step);
ssPrintf("Min step: %.3f\n", min_step);
#else
printf("Simulation ends here\n");
printf("S function simulation time measured: %.3f seconds.\n", current_time);
printf("Total step: %.3f\n", tot_time);
printf("Max step: %.3f\n", max_step);
printf("Min step: %.3f\n", min_step);
#endif
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}

