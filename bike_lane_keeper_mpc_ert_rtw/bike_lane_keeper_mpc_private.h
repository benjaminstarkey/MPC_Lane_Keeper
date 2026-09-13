//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: bike_lane_keeper_mpc_private.h
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
#ifndef bike_lane_keeper_mpc_private_h_
#define bike_lane_keeper_mpc_private_h_
#include "rtwtypes.h"
#include "bike_lane_keeper_mpc_types.h"
#include "bike_lane_keeper_mpc.h"

// Used by FromWorkspace Block: '<Root>/From Workspace'
#ifndef rtInterpolate
# define rtInterpolate(v1,v2,f1,f2)    (((v1)==(v2))?((double)(v1)): (((f1)*((double)(v1)))+((f2)*((double)(v2)))))
#endif

#ifndef rtRound
# define rtRound(v)                    ( ((v) >= 0) ? std::floor((v) + 0.5) : std::ceil((v) - 0.5) )
#endif

extern real_T rt_hypotd_snf(real_T u0, real_T u1);
extern real_T rt_urand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern real_T rt_nrand_Upu32_Yd_f_pw_snf(uint32_T *u);
extern int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator);

#endif                                 // bike_lane_keeper_mpc_private_h_

//
// File trailer for generated code.
//
// [EOF]
//
