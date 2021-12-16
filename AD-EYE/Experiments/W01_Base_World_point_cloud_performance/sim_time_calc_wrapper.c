
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

#ifdef _WIN32
#include <simstruc.h>
int begin, end;
#else
#include <stdio.h>
#include <sys/time.h>
struct timeval begin, end;
#endif


double total_duration, step_duration, previous_total_duration, max_step, second_max_step, min_step;
int nb_steps;
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
previous_total_duration = 0;
max_step = 0;
second_max_step = 0;
min_step = 1000000 ;
nb_steps = 0;

#ifdef _WIN32
ssPrintf("Simulation starts here\n");
begin = GetTickCount();
#else
printf("Simulation starts here\n");
gettimeofday(&begin, 0);
#endif



GetTickCount();
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void sim_time_calc_Outputs_wrapper(void)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
long elapsed_seconds = 0;
long elapsed_microseconds = 0;
#ifdef _WIN32
end = GetTickCount();
elapsed_microseconds = (end - begin) / 1000
#else
gettimeofday(&end, 0);
elapsed_seconds = end.tv_sec - begin.tv_sec;
elapsed_microseconds = end.tv_usec - begin.tv_usec;
#endif




total_duration = elapsed_seconds + elapsed_microseconds * 1e-6; // in seconds

step_duration = total_duration - previous_total_duration;
previous_total_duration = total_duration;
nb_steps++;

#ifdef _WIN32
ssPrintf("step %d: %.3f\n", nb_steps, step_duration);
#else
printf("step %d: %.3f\n", nb_steps, step_duration);
#endif

if (step_duration > max_step){
    max_step = step_duration;
}
else if(step_duration > second_max_step){
    second_max_step = step_duration;
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
ssPrintf("Number of steps: %d \n", nb_steps);
ssPrintf("Total experiment duration: %.3f seconds.\n", total_duration);
ssPrintf("Average step duration: %.3f\n", total_duration / nb_steps);
ssPrintf("Max step duration: %.3f\n", max_step);
ssPrintf("Second max step duration: %.3f\n", second_max_step);
ssPrintf("Min step duration: %.3f\n", min_step);
#else
printf("Simulation ends here\n");
printf("Total experiment duration: %.3f seconds.\n", total_duration);
printf("Average step duration: %.3f\n", total_duration / nb_steps);
printf("Max step duration: %.3f\n", max_step);
printf("Second max step duration: %.3f\n", second_max_step);
printf("Min step duration: %.3f\n", min_step);
#endif
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}

