
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
#define y_width 1

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
void twiststamped_subscriber_Start_wrapper(void **pW,
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

subscribe_to_topic(pW[0], topic_str, message_type_str);
/* %%%-SFUNWIZ_wrapper_Start_Changes_END --- EDIT HERE TO _BEGIN */
}
/*
 * Output function
 *
 */
void twiststamped_subscriber_Outputs_wrapper(real_T *linear_x,
			real_T *linear_y,
			real_T *linear_z,
			real_T *angular_x,
			real_T *angular_y,
			real_T *angular_z,
			void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const real_T *port, const int_T p_width2,
			const real_T *timeout, const int_T p_width3)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
char topic_str[60];
sprintf(topic_str, "%.*s", p_width0, topic);

int buffer_size = 1024;
float numbers[] = {0, 0, 0, 0, 0, 0};

listen_to_topic_twiststamped(pW[0], buffer_size, numbers);

*linear_x = numbers[0];
*linear_y = numbers[1];
*linear_z = numbers[2];
*angular_x = numbers[3];
*angular_y = numbers[4];
*angular_z = numbers[5];
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Terminate function
 *
 */
void twiststamped_subscriber_Terminate_wrapper(void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const real_T *port, const int_T p_width2,
			const real_T *timeout, const int_T p_width3)
{
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_BEGIN --- EDIT HERE TO _END */
char topic_str[60];
sprintf(topic_str, "%.*s", p_width0, topic);

unsubscribe_from_topic(pW[0], topic_str);
close(pW[0]);
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}

