/*
 * W01_Base_Map_cs_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "W01_Base_Map_cs".
 *
 * Model version              : 1.290
 * Simulink Coder version : 9.1 (R2019a) 23-Nov-2018
 * C source code generated on : Thu Jan 21 23:46:14 2021
 *
 * Target selection: ps.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_W01_Base_Map_cs_private_h_
#define RTW_HEADER_W01_Base_Map_cs_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#include "W01_Base_Map_cs.h"
#ifdef __cplusplus

extern "C" {

#endif

  extern void Image_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const int8_T *frame_id, const int_T p_width2,
    const real_T *port, const int_T p_width3,
    const real_T *timeout, const int_T p_width4);
  extern void Image_publisher_Outputs_wrapper(const real_T *height,
    const real_T *width,
    const real_T *encoding_length,
    const real_T *step,
    const uint8_T *data,
    const real_T *data_length,
    const real_T *frameId_length,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const int8_T *frame_id, const int_T p_width2,
    const real_T *port, const int_T p_width3,
    const real_T *timeout, const int_T p_width4);
  extern void Image_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const int8_T *frame_id, const int_T p_width2,
    const real_T *port, const int_T p_width3,
    const real_T *timeout, const int_T p_width4);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void clock_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void clock_publisher_Outputs_wrapper(const real_T *secs,
    const real_T *nsecs,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void clock_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void Pose_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Pose_publisher_Outputs_wrapper(const real_T *positionX,
    const real_T *positionY,
    const real_T *positionZ,
    const real_T *orientationW,
    const real_T *orientationX,
    const real_T *orientationY,
    const real_T *orientationZ,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Pose_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void PoseStamped_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3,
    const uint8_T *frameId, const int_T p_width4);
  extern void PoseStamped_publisher_Outputs_wrapper(const real_T *seq,
    const real_T *frameId_length,
    const real_T *positionX,
    const real_T *positionY,
    const real_T *positionZ,
    const real_T *orientationW,
    const real_T *orientationX,
    const real_T *orientationY,
    const real_T *orientationZ,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3,
    const uint8_T *frameId, const int_T p_width4);
  extern void PoseStamped_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3,
    const uint8_T *frameId, const int_T p_width4);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void Imu_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Imu_publisher_Outputs_wrapper(const real_T *orientW,
    const real_T *orientX,
    const real_T *orientY,
    const real_T *orientZ,
    const real_T *angularZ,
    const real_T *linearAccX,
    const real_T *linearAccZ,
    const real_T *seq,
    const real_T *frameId_length,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Imu_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void Float32MultiArray_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Float32MultiArray_publisher_Outputs_wrapper(const real32_T *data,
    const real32_T *size,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Float32MultiArray_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void Odometry_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Odometry_publisher_Outputs_wrapper(const real_T *seq,
    const real_T *frameId_length,
    const real_T *childFrameId_length,
    const real_T *positionX,
    const real_T *positionY,
    const real_T *positionZ,
    const real_T *orientW,
    const real_T *orientX,
    const real_T *orientY,
    const real_T *orientZ,
    const real_T *linearX,
    const real_T *linearY,
    const real_T *linearZ,
    const real_T *angularX,
    const real_T *angularY,
    const real_T *angularZ,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Odometry_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void int32multiarray_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void int32multiarray_publisher_Outputs_wrapper(const real_T *data,
    const real_T *size,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void int32multiarray_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void Int32_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Int32_publisher_Outputs_wrapper(const real_T *data,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Int32_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void TwistStamped_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void TwistStamped_publisher_Outputs_wrapper(const real_T *seq,
    const real_T *frameId_length,
    const real_T *linearX,
    const real_T *linearY,
    const real_T *linearZ,
    const real_T *angularX,
    const real_T *angularY,
    const real_T *angularZ,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void TwistStamped_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void Float32MultiArray_radar_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Float32MultiArray_radar_publisher_Outputs_wrapper(const real32_T
    *data,
    const real32_T *size,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void Float32MultiArray_radar_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void PoseArray3_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void PoseArray3_publisher_Outputs_wrapper(const uint32_T *seq,
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
    const real_T *timeout, const int_T p_width3);
  extern void PoseArray3_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void twiststamped_subscriber_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void twiststamped_subscriber_Outputs_wrapper(real_T *linear_x,
    real_T *linear_y,
    real_T *linear_z,
    real_T *angular_x,
    real_T *angular_y,
    real_T *angular_z,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void twiststamped_subscriber_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void int16_subscriber_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void int16_subscriber_Outputs_wrapper(real_T *data,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void int16_subscriber_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

#ifdef __cplusplus

extern "C" {

#endif

  extern void bool_publisher_Start_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void bool_publisher_Outputs_wrapper(const boolean_T *data,
    void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);
  extern void bool_publisher_Terminate_wrapper(void **pW,
    const int8_T *topic, const int_T p_width0,
    const int8_T *message_type, const int_T p_width1,
    const real_T *port, const int_T p_width2,
    const real_T *timeout, const int_T p_width3);

#ifdef __cplusplus

}
#endif

extern void RandSrcInitState_U_64(const uint32_T seed[], real_T state[], int32_T
  nChans);
extern void RandSrc_U_D(real_T y[], const real_T minVec[], int32_T minLen, const
  real_T maxVec[], int32_T maxLen, real_T state[], int32_T nChans, int32_T
  nSamps);
extern void RandSrcCreateSeeds_64(uint32_T initSeed, uint32_T seedArray[],
  int32_T numSeeds);
extern void RandSrcInitState_GZ(const uint32_T seed[], uint32_T state[], int32_T
  nChans);
extern void RandSrc_GZ_D(real_T y[], const real_T mean[], int32_T meanLen, const
  real_T xstd[], int32_T xstdLen, uint32_T state[], int32_T nChans, int32_T
  nSamps);
extern void RandSrcInitState_U_32(const uint32_T seed[], real32_T state[],
  int32_T nChans);
extern void RandSrc_U_R(real32_T y[], const real32_T minVec[], int32_T minLen,
  const real32_T maxVec[], int32_T maxLen, real32_T state[], int32_T nChans,
  int32_T nSamps);
extern void RandSrcCreateSeeds_32(uint32_T initSeed, uint32_T seedArray[],
  int32_T numSeeds);
extern void RandSrc_GZ_R(real32_T y[], const real32_T mean[], int32_T meanLen,
  const real32_T xstd[], int32_T xstdLen, uint32_T state[], int32_T nChans,
  int32_T nSamps);
extern real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T rt_powd_snf(real_T u0, real_T u1);
extern void CoordinateTransformationC_Start(DW_CoordinateTransformationCo_T
  *localDW);
extern void CoordinateTransformationConvers(const real_T rtu_0[3],
  B_CoordinateTransformationCon_T *localB);
extern void W01_Base_Map_IfActionSubsystem1(const uint8_T rtu_In5[691200], const
  uint8_T rtu_In6[691200], const uint8_T rtu_In7[691200], uint8_T rty_Out2
  [691200], uint8_T rty_Out3[691200], uint8_T rty_Out4[691200], real_T rtp_idx,
  real_T rtp_idy);
extern void W01_Base_Map__IfActionSubsystem(const uint8_T rtu_In1[691200], const
  uint8_T rtu_In2[691200], const uint8_T rtu_In3[691200], uint8_T rty_Out1
  [691200], uint8_T rty_Out2[691200], uint8_T rty_Out3[691200]);
extern void W01_Base_Map_cs_RainModel_Start(DW_RainModel_W01_Base_Map_cs_T
  *localDW);
extern void W01_Base_Map_cs_RainModel(const real32_T rtu_z[3600], const real32_T
  rtu_intensity[3600], real_T rtu_a, const real32_T rtu_Theta[3600], const
  real32_T rtu_Phi[3600], real32_T rty_z_p[3600], real32_T rty_T[3600], real32_T
  rty_P[3600], real32_T rty_I[3600], B_RainModel_W01_Base_Map_cs_T *localB,
  const ConstB_RainModel_W01_Base_Map_T *localC, DW_RainModel_W01_Base_Map_cs_T *
  localDW);
extern void W01__IfActionSubsystem1_f_Start(DW_IfActionSubsystem1_W01_B_o_T
  *localDW);
extern void W01_Base_M_IfActionSubsystem1_i(const real32_T rtu_In1[3600], const
  real32_T rtu_In2[3600], const real32_T rtu_In3[3600], const real32_T rtu_In4
  [3600], real32_T rty_Out1[3600], real32_T rty_Out2[3600], real32_T rty_Out3
  [3600], real32_T rty_Out4[3600], DW_IfActionSubsystem1_W01_B_o_T *localDW);
extern void W01_Base_Ma_IfActionSubsystem_e(const real32_T rtu_In1[3600], const
  real32_T rtu_In2[3600], const real32_T rtu_In3[3600], const real32_T rtu_In4
  [3600], real32_T rty_Out1[3600], real32_T rty_Out2[3600], real32_T rty_Out3
  [3600], real32_T rty_Out4[3600]);

#endif                               /* RTW_HEADER_W01_Base_Map_cs_private_h_ */
