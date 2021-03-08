
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
void PoseArray_publisher_Start_wrapper(void **pW,
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
void PoseArray_publisher_Outputs_wrapper(const uint32_T *seq,
			const uint8_T *frameId,
			const uint32_T *frameId_length,
			const real_T *positionX,
			const real_T *positionY,
			const real_T *positionZ,
			const real_T *orientationW,
			const real_T *orientationX,
			const real_T *orientationY,
			const real_T *orientationZ,
			const uint32_T *poses_length,
			const uint32_T *seq1,
			const uint8_T *frameId1,
			const uint32_T *frameId_length1,
			const real_T *positionX1,
			const real_T *positionY1,
			const real_T *positionZ1,
			const real_T *orientationW1,
			const real_T *orientationX1,
			const real_T *orientationY1,
			const real_T *orientationZ1,
			const uint32_T *poses_length1,
			const uint32_T *seq2,
			const uint8_T *frameId2,
			const uint32_T *frameId_length2,
			const real_T *positionX2,
			const real_T *positionY2,
			const real_T *positionZ2,
			const real_T *orientationW2,
			const real_T *orientationX2,
			const real_T *orientationY2,
			const real_T *orientationZ2,
			const uint32_T *poses_length2,
			void **pW,
			const int8_T *topic, const int_T p_width0,
			const int8_T *message_type, const int_T p_width1,
			const real_T *port, const int_T p_width2,
			const real_T *timeout, const int_T p_width3)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
char topic_str[60];
sprintf(topic_str, "%.*s", p_width0, topic);

publish_to_topic_posearray(pW[0], topic_str, seq[0], frameId[0], frameId_length[0], positionX[0], positionY[0], positionZ[0], orientationW[0], orientationX[0], orientationY[0], orientationZ[0], poses_length[0], positionX1[0], positionY1[0], positionZ1[0], orientationW1[0], orientationX1[0], orientationY1[0], orientationZ1[0], positionX2[0], positionY2[0], positionZ2[0], orientationW2[0], orientationX2[0], orientationY2[0], orientationZ2[0]);
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
 * Terminate function
 *
 */
void PoseArray_publisher_Terminate_wrapper(void **pW,
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

