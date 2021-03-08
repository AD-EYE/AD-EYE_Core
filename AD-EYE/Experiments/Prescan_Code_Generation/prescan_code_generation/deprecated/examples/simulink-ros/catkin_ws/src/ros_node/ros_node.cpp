/*
 * ros_node.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "ros_node".
 *
 * Model version              : 1.6
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C++ source code generated on : Sat Dec 12 09:39:45 2020
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ros_node.h"
#include "ros_node_private.h"

void ros_nodeModelClass::matlabCodegenHandle_matlabCodeg
  (robotics_slros_internal_block_T *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
  }
}

/* Model step function */
void ros_nodeModelClass::step()
{
  /* local block i/o variables */
  real_T rtb_Switch;
  SL_Bus_ros_node_std_msgs_UInt8 rtb_BusAssignment;
  real_T tmp;

  /* Sum: '<Root>/Add' incorporates:
   *  Delay: '<Root>/Delay'
   *  Delay: '<Root>/Delay1'
   */
  rtb_Switch = ros_node_DW.Delay1_DSTATE + ros_node_DW.Delay_DSTATE;

  /* Switch: '<Root>/Switch' incorporates:
   *  Constant: '<Root>/Constant1'
   */
  if (rtb_Switch >= ros_node_P.Switch_Threshold) {
    rtb_Switch = ros_node_P.Constant1_Value;
  }

  /* End of Switch: '<Root>/Switch' */

  /* DataTypeConversion: '<Root>/Data Type Conversion' */
  tmp = floor(rtb_Switch);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 256.0);
  }

  /* BusAssignment: '<Root>/Bus Assignment' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   */
  rtb_BusAssignment.Data = static_cast<uint8_T>((tmp < 0.0 ? static_cast<int32_T>
    (static_cast<uint8_T>(-static_cast<int8_T>(static_cast<uint8_T>(-tmp)))) :
    static_cast<int32_T>(static_cast<uint8_T>(tmp))));

  /* Outputs for Atomic SubSystem: '<Root>/Publish' */
  /* MATLABSystem: '<S2>/SinkBlock' */
  Pub_ros_node_2.publish(&rtb_BusAssignment);

  /* End of Outputs for SubSystem: '<Root>/Publish' */
  /* Update for Delay: '<Root>/Delay1' incorporates:
   *  Constant: '<Root>/Constant'
   */
  ros_node_DW.Delay1_DSTATE = ros_node_P.Constant_Value_a;

  /* Update for Delay: '<Root>/Delay' */
  ros_node_DW.Delay_DSTATE = rtb_Switch;
}

/* Model initialize function */
void ros_nodeModelClass::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus((&ros_node_M), (NULL));

  /* states (dwork) */
  (void) memset((void *)&ros_node_DW, 0,
                sizeof(DW_ros_node_T));

  {
    static const char_T tmp[8] = { '/', 'c', 'o', 'u', 'n', 't', 'e', 'r' };

    char_T tmp_0[9];
    int32_T i;

    /* Start for Atomic SubSystem: '<Root>/Publish' */
    /* Start for MATLABSystem: '<S2>/SinkBlock' */
    ros_node_DW.obj.matlabCodegenIsDeleted = true;
    ros_node_DW.obj.isInitialized = 0;
    ros_node_DW.obj.matlabCodegenIsDeleted = false;
    ros_node_DW.objisempty = true;
    ros_node_DW.obj.isSetupComplete = false;
    ros_node_DW.obj.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      tmp_0[i] = tmp[i];
    }

    tmp_0[8] = '\x00';
    Pub_ros_node_2.createPublisher(tmp_0, 1);
    ros_node_DW.obj.isSetupComplete = true;

    /* End of Start for MATLABSystem: '<S2>/SinkBlock' */
    /* End of Start for SubSystem: '<Root>/Publish' */
  }

  /* InitializeConditions for Delay: '<Root>/Delay1' */
  ros_node_DW.Delay1_DSTATE = ros_node_P.Delay1_InitialCondition;

  /* InitializeConditions for Delay: '<Root>/Delay' */
  ros_node_DW.Delay_DSTATE = ros_node_P.Delay_InitialCondition;
}

/* Model terminate function */
void ros_nodeModelClass::terminate()
{
  /* Terminate for Atomic SubSystem: '<Root>/Publish' */
  /* Terminate for MATLABSystem: '<S2>/SinkBlock' */
  matlabCodegenHandle_matlabCodeg(&ros_node_DW.obj);

  /* End of Terminate for SubSystem: '<Root>/Publish' */
}

/* Constructor */
ros_nodeModelClass::ros_nodeModelClass()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
ros_nodeModelClass::~ros_nodeModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_ros_node_T * ros_nodeModelClass::getRTM()
{
  return (&ros_node_M);
}
