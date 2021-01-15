
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
#include "rosbridge_functions.h"
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1

/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
 
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Start function
 *
 */
void Int32_publisher_Start_wrapper(void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const real_T *port, const int_T p_width2,
			const real_T *timeout, const int_T p_width3)
{
/* %%%-SFUNWIZ_wrapper_Start_Changes_BEGIN --- EDIT HERE TO _END */
pW[0] = create_connection(port[0], timeout[0]);

char topic_str[60];
char message_type_str[60];
sprintf(topic_str, "%.*s", p_width0, topic);
sprintf(message_type_str, "%.*s", p_width1, message_type);

advertise_topic(pW[0], topic_str, message_type_str);
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void Int32_publisher_Outputs_wrapper(const real_T *data,
			void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const real_T *port, const int_T p_width2,
			const real_T *timeout, const int_T p_width3)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
char topic_str[60];
sprintf(topic_str, "%.*s", p_width0, topic);

publish_to_topic_int32(pW[0], topic_str, data[0]);
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Terminate function
 *
 */
void Int32_publisher_Terminate_wrapper(void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const real_T *port, const int_T p_width2,
			const real_T *timeout, const int_T p_width3)
{
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_BEGIN --- EDIT HERE TO _END */
char topic_str[60];
sprintf(topic_str, "%.*s", p_width0, topic);

unadvertise_topic(pW[0], topic_str);
close(pW[0]);
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}

