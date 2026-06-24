//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: bike_lane_keeper_mpc.h
//
// Code generated for Simulink model 'bike_lane_keeper_mpc'.
//
// Model version                  : 1.8
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Wed Jun 24 10:35:04 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef bike_lane_keeper_mpc_h_
#define bike_lane_keeper_mpc_h_
#include <cmath>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "bike_lane_keeper_mpc_types.h"
#include <cstring>

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

// Class declaration for model bike_lane_keeper_mpc
class bike_lane_keeper_mpc final
{
  // public data and function members
 public:
  // Block signals (default storage)
  struct B_bike_lane_keeper_mpc_T {
    real_T Q_bar[6400];
  };

  // Block states (default storage) for system '<Root>'
  struct DW_bike_lane_keeper_mpc_T {
    real_T DiscreteStateSpace_DSTATE[4];// '<Root>/Discrete State-Space'
    real_T UnitDelay2_DSTATE;          // '<Root>/Unit Delay2'
    real_T UnitDelay_DSTATE[4];        // '<Root>/Unit Delay'
    real_T UnitDelay1_DSTATE[16];      // '<Root>/Unit Delay1'
    real_T NextOutput;                 // '<S2>/White Noise'
    real_T NextOutput_l;               // '<S1>/White Noise'
    struct {
      void *TimePtr;
      void *DataPtr;
      void *RSimInfoPtr;
    } FromWorkspace_PWORK;             // '<Root>/From Workspace'

    struct {
      void *TimePtr;
      void *DataPtr;
      void *RSimInfoPtr;
    } FromWorkspace1_PWORK;            // '<Root>/From Workspace1'

    uint32_T RandSeed;                 // '<S2>/White Noise'
    uint32_T RandSeed_l;               // '<S1>/White Noise'
    struct {
      int_T PrevIndex;
    } FromWorkspace_IWORK;             // '<Root>/From Workspace'

    struct {
      int_T PrevIndex;
    } FromWorkspace1_IWORK;            // '<Root>/From Workspace1'

    boolean_T iA0_prev[10];            // '<Root>/MATLAB Function1'
  };

  // Constant parameters (default storage)
  struct ConstP_bike_lane_keeper_mpc_T {
    // Expression: Ad
    //  Referenced by: '<Root>/MATLAB Function'

    real_T MATLABFunction_Ad[16];

    // Expression: Bd
    //  Referenced by: '<Root>/MATLAB Function'

    real_T MATLABFunction_Bd[4];

    // Expression: Ed
    //  Referenced by: '<Root>/MATLAB Function'

    real_T MATLABFunction_Ed[4];

    // Expression: H
    //  Referenced by: '<Root>/MATLAB Function'

    real_T MATLABFunction_H[8];

    // Expression: Q_kf
    //  Referenced by: '<Root>/MATLAB Function'

    real_T MATLABFunction_Q_kf[16];

    // Expression: R_kf
    //  Referenced by: '<Root>/MATLAB Function'

    real_T MATLABFunction_R_kf[4];

    // Expression: F
    //  Referenced by: '<Root>/MATLAB Function1'

    real_T MATLABFunction1_F[320];

    // Expression: Gamma
    //  Referenced by: '<Root>/MATLAB Function1'

    real_T MATLABFunction1_Gamma[1600];

    // Expression: Phi
    //  Referenced by: '<Root>/MATLAB Function1'

    real_T MATLABFunction1_Phi[400];

    // Expression: Q
    //  Referenced by: '<Root>/MATLAB Function1'

    real_T MATLABFunction1_Q[16];

    // Expression: P_hat_0
    //  Referenced by: '<Root>/Unit Delay1'

    real_T UnitDelay1_InitialCondition[16];
  };

  // Real-time Model Data Structure
  struct RT_MODEL_bike_lane_keeper_mpc_T {
    const char_T * volatile errorStatus;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      uint32_T clockTick0;
    } Timing;

    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const volatile aErrorStatus);
  };

  // Copy Constructor
  bike_lane_keeper_mpc(bike_lane_keeper_mpc const&) = delete;

  // Assignment Operator
  bike_lane_keeper_mpc& operator= (bike_lane_keeper_mpc const&) & = delete;

  // Move Constructor
  bike_lane_keeper_mpc(bike_lane_keeper_mpc &&) = delete;

  // Move Assignment Operator
  bike_lane_keeper_mpc& operator= (bike_lane_keeper_mpc &&) = delete;

  // Real-Time Model get method
  bike_lane_keeper_mpc::RT_MODEL_bike_lane_keeper_mpc_T * getRTM();

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  bike_lane_keeper_mpc();

  // Destructor
  ~bike_lane_keeper_mpc();

  // private data and function members
 private:
  // Block signals
  B_bike_lane_keeper_mpc_T bike_lane_keeper_mpc_B;

  // Block states
  DW_bike_lane_keeper_mpc_T bike_lane_keeper_mpc_DW;

  // private member function(s) for subsystem '<Root>'
  void bike_lane_keeper_mpc_trisolve(const real_T A[25], real_T B[25]);
  real_T bike_lane_keeper_mpc_norm(const real_T x[5]);
  real_T bike_lane_keeper_mpc_maximum(const real_T x[5]);
  real_T bike_lane_keeper_mpc_xnrm2(int32_T n, const real_T x[25], int32_T ix0);
  void bike_lane_keeper_mpc_xgemv(int32_T m, int32_T n, const real_T A[25],
    int32_T ia0, const real_T x[25], int32_T ix0, real_T y[5]);
  void bike_lane_keeper_mpc_xgerc(int32_T m, int32_T n, real_T alpha1, int32_T
    ix0, const real_T y[5], real_T A[25], int32_T ia0);
  real_T bike_lane_keeper_mpc_KWIKfactor(const real_T Ac[50], const int32_T iC
    [10], int32_T nA, const real_T Linv[25], real_T RLinv[25], real_T D[25],
    real_T H[25], int32_T n);
  void bike_lane_keeper_DropConstraint(int32_T kDrop, boolean_T iA[10], int32_T *
    nA, int32_T iC[10]);
  void bike_lane_keeper_mpc_qpkwik(const real_T Linv[25], const real_T Hinv[25],
    const real_T f[5], const real_T Ac[50], const real_T b[10], boolean_T iA[10],
    int32_T maxiter, real_T FeasTol, real_T x[5], real_T lambda[10], int32_T
    *status);

  // Real-Time Model
  RT_MODEL_bike_lane_keeper_mpc_T bike_lane_keeper_mpc_M;
};

// Constant parameters (default storage)
extern const bike_lane_keeper_mpc::ConstP_bike_lane_keeper_mpc_T
  bike_lane_keeper_mpc_ConstP;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Display' : Unused code path elimination
//  Block '<Root>/Display1' : Unused code path elimination
//  Block '<Root>/Scope' : Unused code path elimination
//  Block '<Root>/Scope1' : Unused code path elimination


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'bike_lane_keeper_mpc'
//  '<S1>'   : 'bike_lane_keeper_mpc/Band-Limited White Noise'
//  '<S2>'   : 'bike_lane_keeper_mpc/Band-Limited White Noise1'
//  '<S3>'   : 'bike_lane_keeper_mpc/MATLAB Function'
//  '<S4>'   : 'bike_lane_keeper_mpc/MATLAB Function1'

#endif                                 // bike_lane_keeper_mpc_h_

//
// File trailer for generated code.
//
// [EOF]
//
