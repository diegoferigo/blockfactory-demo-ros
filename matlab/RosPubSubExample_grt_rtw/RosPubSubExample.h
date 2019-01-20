/*
 * RosPubSubExample.h
 *
 * Non-Degree Granting Education License -- for use at non-degree
 * granting, nonprofit, educational organizations only. Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "RosPubSubExample".
 *
 * Model version              : 1.30
 * Simulink Coder version : 8.14 (R2018a) 06-Feb-2018
 * C++ source code generated on : Tue Jan 15 12:19:20 2019
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_RosPubSubExample_h_
#define RTW_HEADER_RosPubSubExample_h_
#include <cmath>
#include <string.h>
#ifndef RosPubSubExample_COMMON_INCLUDES_
# define RosPubSubExample_COMMON_INCLUDES_
#include <cstdio>
#include <BlockFactory/Core/Block.h>
#include <BlockFactory/Core/Log.h>
#include <BlockFactory/Core/Parameter.h>
#include <BlockFactory/Core/Parameters.h>
#include <BlockFactory/Core/FactorySingleton.h>
#include <BlockFactory/SimulinkCoder/CoderBlockInformation.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* RosPubSubExample_COMMON_INCLUDES_ */

#include "RosPubSubExample_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T DataWrote[2];
  real_T DataRead[2];                  /* '<Root>/RosTopicSubscriber' */
} B_RosPubSubExample_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  struct {
    void *blockPWork[2];
  } RosTopicPublisher_PWORK;           /* '<Root>/RosTopicPublisher' */

  struct {
    void *blockPWork[2];
  } RosTopicSubscriber_PWORK;          /* '<Root>/RosTopicSubscriber' */
} DW_RosPubSubExample_T;

/* Parameters (default storage) */
struct P_RosPubSubExample_T_ {
  real_T Sine_Amp;                     /* Expression: 1
                                        * Referenced by: '<Root>/Sine'
                                        */
  real_T Sine_Bias;                    /* Expression: 0
                                        * Referenced by: '<Root>/Sine'
                                        */
  real_T Sine_Freq;                    /* Expression: 1
                                        * Referenced by: '<Root>/Sine'
                                        */
  real_T Sine_Phase;                   /* Expression: 0
                                        * Referenced by: '<Root>/Sine'
                                        */
  real_T Cosine_Amp;                   /* Expression: 1
                                        * Referenced by: '<Root>/Cosine'
                                        */
  real_T Cosine_Bias;                  /* Expression: 0
                                        * Referenced by: '<Root>/Cosine'
                                        */
  real_T Cosine_Freq;                  /* Expression: 1
                                        * Referenced by: '<Root>/Cosine'
                                        */
  real_T Cosine_Phase;                 /* Expression: pi/2
                                        * Referenced by: '<Root>/Cosine'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_RosPubSubExample_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    SimTimeStep simTimeStep;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Class declaration for model RosPubSubExample */
class RosPubSubExampleModelClass {
  /* public data and function members */
 public:
  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  RosPubSubExampleModelClass();

  /* Destructor */
  ~RosPubSubExampleModelClass();

  /* Real-Time Model get method */
  RT_MODEL_RosPubSubExample_T * getRTM();

  /* private data and function members */
 private:
  /* Tunable parameters */
  P_RosPubSubExample_T RosPubSubExample_P;

  /* Block signals */
  B_RosPubSubExample_T RosPubSubExample_B;

  /* Block states */
  DW_RosPubSubExample_T RosPubSubExample_DW;

  /* Real-Time Model */
  RT_MODEL_RosPubSubExample_T RosPubSubExample_M;
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'RosPubSubExample'
 */
#endif                                 /* RTW_HEADER_RosPubSubExample_h_ */
