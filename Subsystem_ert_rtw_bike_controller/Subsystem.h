//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Subsystem.h
//
// Code generated for Simulink model 'Subsystem'.
//
// Model version                  : 1.20
// Simulink Coder version         : 25.2 (R2025b) 28-Jul-2025
// C/C++ source code generated on : Thu Jun 25 10:22:40 2026
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef Subsystem_h_
#define Subsystem_h_
#include <cmath>
#include "rtwtypes.h"
#include "rt_nonfinite.h"
#include "Subsystem_types.h"

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

// Class declaration for model Subsystem
class Subsystem final
{
  // public data and function members
 public:
  // Block signals (default storage)
  struct B_Subsystem_T {
    real_T Q_bar[6400];
  };

  // Block states (default storage) for system '<Root>'
  struct DW_Subsystem_T {
    real_T UnitDelay1_DSTATE[16];      // '<S1>/Unit Delay1'
    real_T UnitDelay_DSTATE[4];        // '<S1>/Unit Delay'
    boolean_T iA0_prev[10];            // '<S1>/MATLAB Function1'
  };

  // Constant parameters (default storage)
  struct ConstP_Subsystem_T {
    // Expression: Ad
    //  Referenced by: '<S1>/MATLAB Function'

    real_T MATLABFunction_Ad[16];

    // Expression: Bd
    //  Referenced by: '<S1>/MATLAB Function'

    real_T MATLABFunction_Bd[4];

    // Expression: Ed
    //  Referenced by: '<S1>/MATLAB Function'

    real_T MATLABFunction_Ed[4];

    // Expression: H
    //  Referenced by: '<S1>/MATLAB Function'

    real_T MATLABFunction_H[8];

    // Expression: Q_kf
    //  Referenced by: '<S1>/MATLAB Function'

    real_T MATLABFunction_Q_kf[16];

    // Expression: R_kf
    //  Referenced by: '<S1>/MATLAB Function'

    real_T MATLABFunction_R_kf[4];

    // Expression: F
    //  Referenced by: '<S1>/MATLAB Function1'

    real_T MATLABFunction1_F[320];

    // Expression: Gamma
    //  Referenced by: '<S1>/MATLAB Function1'

    real_T MATLABFunction1_Gamma[1600];

    // Expression: Phi
    //  Referenced by: '<S1>/MATLAB Function1'

    real_T MATLABFunction1_Phi[400];

    // Expression: Q
    //  Referenced by: '<S1>/MATLAB Function1'

    real_T MATLABFunction1_Q[16];

    // Expression: P_hat_0
    //  Referenced by: '<S1>/Unit Delay1'

    real_T UnitDelay1_InitialCondition[16];
  };

  // External inputs (root inport signals with default storage)
  struct ExtU_Subsystem_T {
    real_T roadcurvelookahead[20];     // '<Root>/rho_preview'
    real_T roadcurvedisturbance;       // '<Root>/rho'
    real_T noisyprocesssensore1e2[2];  // '<Root>/x_meas'
  };

  // External outputs (root outports fed by signals with default storage)
  struct ExtY_Subsystem_T {
    real_T mpccontrolinput;            // '<Root>/mpc control input'
    real_T u_horizon[5];               // '<Root>/u_horizon'
    real_T x_hat[4];                   // '<Root>/x_hat'
  };

  // Real-time Model Data Structure
  struct RT_MODEL_Subsystem_T {
    const char_T * volatile errorStatus;
    const char_T* getErrorStatus() const;
    void setErrorStatus(const char_T* const volatile aErrorStatus);
  };

  // Copy Constructor
  Subsystem(Subsystem const&) = delete;

  // Assignment Operator
  Subsystem& operator= (Subsystem const&) & = delete;

  // Move Constructor
  Subsystem(Subsystem &&) = delete;

  // Move Assignment Operator
  Subsystem& operator= (Subsystem &&) = delete;

  // Real-Time Model get method
  Subsystem::RT_MODEL_Subsystem_T * getRTM();

  // Root inports set method
  void setExternalInputs(const ExtU_Subsystem_T *pExtU_Subsystem_T)
  {
    Subsystem_U = *pExtU_Subsystem_T;
  }

  // Root outports get method
  const ExtY_Subsystem_T &getExternalOutputs() const
  {
    return Subsystem_Y;
  }

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  static void terminate();

  // Constructor
  Subsystem();

  // Destructor
  ~Subsystem();

  // private data and function members
 private:
  // External inputs
  ExtU_Subsystem_T Subsystem_U;

  // External outputs
  ExtY_Subsystem_T Subsystem_Y;

  // Block signals
  B_Subsystem_T Subsystem_B;

  // Block states
  DW_Subsystem_T Subsystem_DW;

  // private member function(s) for subsystem '<Root>'
  void Subsystem_trisolve(const real_T A[25], real_T B[25]);
  real_T Subsystem_norm(const real_T x[5]);
  real_T Subsystem_maximum(const real_T x[5]);
  real_T Subsystem_xnrm2(int32_T n, const real_T x[25], int32_T ix0);
  void Subsystem_xgemv(int32_T m, int32_T n, const real_T A[25], int32_T ia0,
                       const real_T x[25], int32_T ix0, real_T y[5]);
  void Subsystem_xgerc(int32_T m, int32_T n, real_T alpha1, int32_T ix0, const
                       real_T y[5], real_T A[25], int32_T ia0);
  real_T Subsystem_KWIKfactor(const real_T Ac[50], const int32_T iC[10], int32_T
    nA, const real_T Linv[25], real_T RLinv[25], real_T D[25], real_T H[25],
    int32_T n);
  void Subsystem_DropConstraint(int32_T kDrop, boolean_T iA[10], int32_T *nA,
    int32_T iC[10]);
  void Subsystem_qpkwik(const real_T Linv[25], const real_T Hinv[25], const
                        real_T f[5], const real_T Ac[50], const real_T b[10],
                        boolean_T iA[10], int32_T maxiter, real_T FeasTol,
                        real_T x[5], real_T lambda[10], int32_T *status);

  // Real-Time Model
  RT_MODEL_Subsystem_T Subsystem_M;
};

// Constant parameters (default storage)
extern const Subsystem::ConstP_Subsystem_T Subsystem_ConstP;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Note that this particular code originates from a subsystem build,
//  and has its own system numbers different from the parent model.
//  Refer to the system hierarchy for this subsystem below, and use the
//  MATLAB hilite_system command to trace the generated code back
//  to the parent model.  For example,
//
//  hilite_system('bike_lane_keeper_mpc/Subsystem')    - opens subsystem bike_lane_keeper_mpc/Subsystem
//  hilite_system('bike_lane_keeper_mpc/Subsystem/Kp') - opens and selects block Kp
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'bike_lane_keeper_mpc'
//  '<S1>'   : 'bike_lane_keeper_mpc/Subsystem'
//  '<S2>'   : 'bike_lane_keeper_mpc/Subsystem/MATLAB Function'
//  '<S3>'   : 'bike_lane_keeper_mpc/Subsystem/MATLAB Function1'

#endif                                 // Subsystem_h_

//
// File trailer for generated code.
//
// [EOF]
//
