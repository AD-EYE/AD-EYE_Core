
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
void Image_publisher_Start_wrapper(void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const int8_T *frame_id, const int_T p_width2,
			const real_T *port, const int_T p_width3,
			const real_T *timeout, const int_T p_width4)
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
void Image_publisher_Outputs_wrapper(const real_T *height,
			const real_T *width,
			const uint32_T *encoding_length,
			const uint32_T *step,
			const uint8_T *data,
			const uint32_T *data_length,
			const uint32_T *frameId_length,
			void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const int8_T *frame_id, const int_T p_width2,
			const real_T *port, const int_T p_width3,
			const real_T *timeout, const int_T p_width4)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
char topic_str[60];
sprintf(topic_str, "%.*s", p_width0, topic);

char frame_id_str[60];
sprintf(frame_id_str, "%.*s", p_width2, frame_id);

publish_to_topic_image(pW[0], topic_str, height[0], width[0], encoding_length[0], step[0], data, data_length[0], frame_id_str, frameId_length[0]);
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Terminate function
 *
 */
void Image_publisher_Terminate_wrapper(void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const int8_T *frame_id, const int_T p_width2,
			const real_T *port, const int_T p_width3,
			const real_T *timeout, const int_T p_width4)
{
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_BEGIN --- EDIT HERE TO _END */
char topic_str[60];
sprintf(topic_str, "%.*s", p_width0, topic);

unadvertise_topic(pW[0], topic_str);
close(pW[0]);
/* %%%-SFUNWIZ_wrapper_Terminate_Changes_END --- EDIT HERE TO _BEGIN */
}

