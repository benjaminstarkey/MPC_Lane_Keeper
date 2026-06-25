//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Subsystem.cpp
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
#include "Subsystem.h"
#include "rtwtypes.h"
#include <cmath>
#include <emmintrin.h>
#include <cstring>
#include "Subsystem_private.h"
#include "cmath"

int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
void Subsystem::Subsystem_trisolve(const real_T A[25], real_T B[25])
{
  for (int32_T j{0}; j < 5; j++) {
    int32_T jBcol;
    jBcol = 5 * j;
    for (int32_T b_k{0}; b_k < 5; b_k++) {
      real_T B_0;
      int32_T B_tmp;
      int32_T kAcol;
      kAcol = 5 * b_k;
      B_tmp = b_k + jBcol;
      B_0 = B[B_tmp];
      if (B_0 != 0.0) {
        B[B_tmp] = B_0 / A[b_k + kAcol];
        for (int32_T i{b_k + 2}; i < 6; i++) {
          int32_T tmp;
          tmp = (i + jBcol) - 1;
          B[tmp] -= A[(i + kAcol) - 1] * B[B_tmp];
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
real_T Subsystem::Subsystem_norm(const real_T x[5])
{
  real_T scale;
  real_T y;
  int32_T k;
  y = 0.0;
  scale = 3.3121686421112381E-170;
  for (k = 0; k < 5; k++) {
    real_T absxk;
    absxk = std::abs(x[k]);
    if (absxk > scale) {
      real_T t;
      t = scale / absxk;
      y = y * t * t + 1.0;
      scale = absxk;
    } else {
      real_T t;
      t = absxk / scale;
      y += t * t;
    }
  }

  y = scale * std::sqrt(y);
  if (std::isnan(y)) {
    k = 0;
    int32_T exitg1;
    do {
      exitg1 = 0;
      if (k < 5) {
        if (std::isnan(x[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        y = (rtInf);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return y;
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
real_T Subsystem::Subsystem_maximum(const real_T x[5])
{
  real_T ex;
  int32_T idx;
  int32_T k;
  if (!std::isnan(x[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 6)) {
      if (!std::isnan(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    ex = x[0];
  } else {
    ex = x[idx - 1];
    for (k = idx + 1; k < 6; k++) {
      real_T x_0;
      x_0 = x[k - 1];
      if (ex < x_0) {
        ex = x_0;
      }
    }
  }

  return ex;
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
real_T Subsystem::Subsystem_xnrm2(int32_T n, const real_T x[25], int32_T ix0)
{
  real_T y;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = std::abs(x[ix0 - 1]);
    } else {
      real_T scale;
      int32_T k;
      int32_T kend;
      scale = 3.3121686421112381E-170;
      kend = (ix0 + n) - 1;
      for (k = ix0; k <= kend; k++) {
        real_T absxk;
        absxk = std::abs(x[k - 1]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * std::sqrt(y);
      if (std::isnan(y)) {
        k = ix0;
        int32_T exitg1;
        do {
          exitg1 = 0;
          if (k <= kend) {
            if (std::isnan(x[k - 1])) {
              exitg1 = 1;
            } else {
              k++;
            }
          } else {
            y = (rtInf);
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
    }
  }

  return y;
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T a;
  real_T b;
  real_T y;
  a = std::abs(u0);
  b = std::abs(u1);
  if (a < b) {
    a /= b;
    y = std::sqrt(a * a + 1.0) * b;
  } else if (a > b) {
    b /= a;
    y = std::sqrt(b * b + 1.0) * a;
  } else if (std::isnan(b)) {
    y = (rtNaN);
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
void Subsystem::Subsystem_xgemv(int32_T m, int32_T n, const real_T A[25],
  int32_T ia0, const real_T x[25], int32_T ix0, real_T y[5])
{
  if ((m != 0) && (n != 0)) {
    int32_T b;
    if (n - 1 >= 0) {
      std::memset(&y[0], 0, static_cast<uint32_T>(n) * sizeof(real_T));
    }

    b = (n - 1) * 5 + ia0;
    for (int32_T b_iy{ia0}; b_iy <= b; b_iy += 5) {
      real_T c;
      int32_T d;
      int32_T ia;
      c = 0.0;
      d = b_iy + m;
      for (ia = b_iy; ia < d; ia++) {
        c += x[((ix0 + ia) - b_iy) - 1] * A[ia - 1];
      }

      ia = div_nde_s32_floor(b_iy - ia0, 5);
      y[ia] += c;
    }
  }
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
void Subsystem::Subsystem_xgerc(int32_T m, int32_T n, real_T alpha1, int32_T ix0,
  const real_T y[5], real_T A[25], int32_T ia0)
{
  if (!(alpha1 == 0.0)) {
    int32_T jA;
    jA = ia0;
    for (int32_T j{0}; j < n; j++) {
      real_T temp;
      temp = y[j];
      if (temp != 0.0) {
        int32_T b;
        temp *= alpha1;
        b = m + jA;
        for (int32_T ijA{jA}; ijA < b; ijA++) {
          A[ijA - 1] += A[((ix0 + ijA) - jA) - 1] * temp;
        }
      }

      jA += 5;
    }
  }
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
real_T Subsystem::Subsystem_KWIKfactor(const real_T Ac[50], const int32_T iC[10],
  int32_T nA, const real_T Linv[25], real_T RLinv[25], real_T D[25], real_T H[25],
  int32_T n)
{
  __m128d tmp;
  real_T A[25];
  real_T TL[25];
  real_T b_R[25];
  real_T tau[5];
  real_T work[5];
  real_T A_0;
  real_T Status;
  real_T atmp;
  real_T xnorm;
  int32_T b_coltop;
  int32_T b_lastv;
  int32_T c_lastc;
  int32_T exitg1;
  int32_T f;
  int32_T h_k;
  int32_T i;
  int32_T ii;
  int32_T knt;
  int32_T qY;
  boolean_T exitg2;
  Status = 1.0;
  std::memset(&RLinv[0], 0, 25U * sizeof(real_T));
  for (b_lastv = 0; b_lastv < nA; b_lastv++) {
    b_coltop = iC[b_lastv];
    for (i = 0; i < 5; i++) {
      RLinv[i + 5 * b_lastv] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      xnorm = Ac[(10 * i + b_coltop) - 1];
      for (ii = 0; ii < 5; ii++) {
        c_lastc = 5 * b_lastv + ii;
        RLinv[c_lastc] += Linv[5 * i + ii] * xnorm;
      }
    }
  }

  std::memcpy(&A[0], &RLinv[0], 25U * sizeof(real_T));
  for (i = 0; i < 5; i++) {
    tau[i] = 0.0;
    work[i] = 0.0;
  }

  for (i = 0; i < 5; i++) {
    ii = i * 5 + i;
    if (i + 1 < 5) {
      atmp = A[ii];
      b_coltop = ii + 2;
      tau[i] = 0.0;
      xnorm = Subsystem_xnrm2(4 - i, A, ii + 2);
      if (xnorm != 0.0) {
        A_0 = A[ii];
        xnorm = rt_hypotd_snf(A_0, xnorm);
        if (A_0 >= 0.0) {
          xnorm = -xnorm;
        }

        if (std::abs(xnorm) < 1.0020841800044864E-292) {
          knt = 0;
          f = (ii - i) + 5;
          do {
            knt++;
            b_lastv = (((((f - ii) - 1) / 2) << 1) + ii) + 2;
            c_lastc = b_lastv - 2;
            for (h_k = b_coltop; h_k <= c_lastc; h_k += 2) {
              tmp = _mm_loadu_pd(&A[h_k - 1]);
              _mm_storeu_pd(&A[h_k - 1], _mm_mul_pd(tmp, _mm_set1_pd
                (9.9792015476736E+291)));
            }

            for (h_k = b_lastv; h_k <= f; h_k++) {
              A[h_k - 1] *= 9.9792015476736E+291;
            }

            xnorm *= 9.9792015476736E+291;
            atmp *= 9.9792015476736E+291;
          } while ((std::abs(xnorm) < 1.0020841800044864E-292) && (knt < 20));

          xnorm = rt_hypotd_snf(atmp, Subsystem_xnrm2(4 - i, A, ii + 2));
          if (atmp >= 0.0) {
            xnorm = -xnorm;
          }

          tau[i] = (xnorm - atmp) / xnorm;
          atmp = 1.0 / (atmp - xnorm);
          c_lastc = b_lastv - 2;
          for (h_k = b_coltop; h_k <= c_lastc; h_k += 2) {
            tmp = _mm_loadu_pd(&A[h_k - 1]);
            _mm_storeu_pd(&A[h_k - 1], _mm_mul_pd(tmp, _mm_set1_pd(atmp)));
          }

          for (h_k = b_lastv; h_k <= f; h_k++) {
            A[h_k - 1] *= atmp;
          }

          for (b_lastv = 0; b_lastv < knt; b_lastv++) {
            xnorm *= 1.0020841800044864E-292;
          }

          atmp = xnorm;
        } else {
          tau[i] = (xnorm - A_0) / xnorm;
          atmp = 1.0 / (A_0 - xnorm);
          knt = (ii - i) + 5;
          b_lastv = (((((knt - ii) - 1) / 2) << 1) + ii) + 2;
          c_lastc = b_lastv - 2;
          for (h_k = b_coltop; h_k <= c_lastc; h_k += 2) {
            tmp = _mm_loadu_pd(&A[h_k - 1]);
            _mm_storeu_pd(&A[h_k - 1], _mm_mul_pd(tmp, _mm_set1_pd(atmp)));
          }

          for (h_k = b_lastv; h_k <= knt; h_k++) {
            A[h_k - 1] *= atmp;
          }

          atmp = xnorm;
        }
      }

      A[ii] = 1.0;
      if (tau[i] != 0.0) {
        b_lastv = 5 - i;
        c_lastc = (ii - i) + 4;
        while ((b_lastv > 0) && (A[c_lastc] == 0.0)) {
          b_lastv--;
          c_lastc--;
        }

        c_lastc = 4 - i;
        exitg2 = false;
        while ((!exitg2) && (c_lastc > 0)) {
          b_coltop = ((c_lastc - 1) * 5 + ii) + 5;
          h_k = b_coltop;
          do {
            exitg1 = 0;
            if (h_k + 1 <= b_coltop + b_lastv) {
              if (A[h_k] != 0.0) {
                exitg1 = 1;
              } else {
                h_k++;
              }
            } else {
              c_lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        b_lastv = 0;
        c_lastc = 0;
      }

      if (b_lastv > 0) {
        Subsystem_xgemv(b_lastv, c_lastc, A, ii + 6, A, ii + 1, work);
        Subsystem_xgerc(b_lastv, c_lastc, -tau[i], ii + 1, work, A, ii + 6);
      }

      A[ii] = atmp;
    } else {
      tau[4] = 0.0;
    }
  }

  for (i = 0; i < 5; i++) {
    for (ii = 0; ii <= i; ii++) {
      b_R[ii + 5 * i] = A[5 * i + ii];
    }

    for (ii = i + 2; ii < 6; ii++) {
      b_R[(ii + 5 * i) - 1] = 0.0;
    }

    work[i] = 0.0;
  }

  for (i = 4; i >= 0; i--) {
    ii = i * 5 + i;
    if (i + 1 < 5) {
      A[ii] = 1.0;
      if (tau[i] != 0.0) {
        b_lastv = 5 - i;
        c_lastc = (ii - i) + 4;
        while ((b_lastv > 0) && (A[c_lastc] == 0.0)) {
          b_lastv--;
          c_lastc--;
        }

        c_lastc = 4 - i;
        exitg2 = false;
        while ((!exitg2) && (c_lastc > 0)) {
          b_coltop = ((c_lastc - 1) * 5 + ii) + 5;
          h_k = b_coltop;
          do {
            exitg1 = 0;
            if (h_k + 1 <= b_coltop + b_lastv) {
              if (A[h_k] != 0.0) {
                exitg1 = 1;
              } else {
                h_k++;
              }
            } else {
              c_lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        b_lastv = 0;
        c_lastc = 0;
      }

      if (b_lastv > 0) {
        Subsystem_xgemv(b_lastv, c_lastc, A, ii + 6, A, ii + 1, work);
        Subsystem_xgerc(b_lastv, c_lastc, -tau[i], ii + 1, work, A, ii + 6);
      }

      h_k = (ii - i) + 5;
      b_lastv = (((((h_k - ii) - 1) / 2) << 1) + ii) + 2;
      c_lastc = b_lastv - 2;
      for (b_coltop = ii + 2; b_coltop <= c_lastc; b_coltop += 2) {
        tmp = _mm_loadu_pd(&A[b_coltop - 1]);
        _mm_storeu_pd(&A[b_coltop - 1], _mm_mul_pd(tmp, _mm_set1_pd(-tau[i])));
      }

      for (b_coltop = b_lastv; b_coltop <= h_k; b_coltop++) {
        A[b_coltop - 1] *= -tau[i];
      }
    }

    A[ii] = 1.0 - tau[i];
    for (b_lastv = 0; b_lastv < i; b_lastv++) {
      A[(ii - b_lastv) - 1] = 0.0;
    }
  }

  i = 0;
  do {
    exitg1 = 0;
    if (i <= nA - 1) {
      if (std::abs(b_R[5 * i + i]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        i++;
      }
    } else {
      for (ii = 0; ii < n; ii++) {
        for (b_lastv = 0; b_lastv < n; b_lastv++) {
          xnorm = 0.0;
          for (i = 0; i < 5; i++) {
            xnorm += Linv[5 * ii + i] * A[5 * b_lastv + i];
          }

          TL[ii + 5 * b_lastv] = xnorm;
        }
      }

      std::memset(&RLinv[0], 0, 25U * sizeof(real_T));
      for (b_lastv = nA; b_lastv >= 1; b_lastv--) {
        i = (b_lastv - 1) * 5;
        ii = (b_lastv + i) - 1;
        RLinv[ii] = 1.0;
        for (b_coltop = b_lastv; b_coltop <= nA; b_coltop++) {
          c_lastc = ((b_coltop - 1) * 5 + b_lastv) - 1;
          RLinv[c_lastc] /= b_R[ii];
        }

        if (b_lastv > 1) {
          for (b_coltop = 0; b_coltop <= b_lastv - 2; b_coltop++) {
            for (h_k = b_lastv; h_k <= nA; h_k++) {
              ii = (h_k - 1) * 5;
              c_lastc = ii + b_coltop;
              RLinv[c_lastc] -= RLinv[(ii + b_lastv) - 1] * b_R[i + b_coltop];
            }
          }
        }
      }

      for (b_lastv = 0; b_lastv < n; b_lastv++) {
        if (b_lastv + 1 <= n) {
          if (nA > 2147483646) {
            qY = MAX_int32_T;
          } else {
            qY = nA + 1;
          }
        }

        for (c_lastc = b_lastv + 1; c_lastc <= n; c_lastc++) {
          i = (c_lastc - 1) * 5 + b_lastv;
          H[i] = 0.0;
          for (b_coltop = qY; b_coltop <= n; b_coltop++) {
            ii = (b_coltop - 1) * 5;
            H[i] -= TL[(ii + c_lastc) - 1] * TL[ii + b_lastv];
          }

          H[(c_lastc + 5 * b_lastv) - 1] = H[i];
        }
      }

      for (qY = 0; qY < nA; qY++) {
        for (b_lastv = 0; b_lastv < n; b_lastv++) {
          i = 5 * qY + b_lastv;
          D[i] = 0.0;
          for (c_lastc = qY + 1; c_lastc <= nA; c_lastc++) {
            ii = (c_lastc - 1) * 5;
            D[i] += TL[ii + b_lastv] * RLinv[ii + qY];
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
void Subsystem::Subsystem_DropConstraint(int32_T kDrop, boolean_T iA[10],
  int32_T *nA, int32_T iC[10])
{
  if (kDrop > 0) {
    iA[iC[kDrop - 1] - 1] = false;
    if (kDrop < *nA) {
      int32_T b;
      int32_T i;
      if (*nA < -2147483647) {
        i = MIN_int32_T;
      } else {
        i = *nA - 1;
      }

      b = i + 1;
      for (i = kDrop; i < b; i++) {
        iC[i - 1] = iC[i];
      }
    }

    iC[*nA - 1] = 0;
    if (*nA < -2147483647) {
      *nA = MIN_int32_T;
    } else {
      (*nA)--;
    }
  }
}

// Function for MATLAB Function: '<S1>/MATLAB Function1'
void Subsystem::Subsystem_qpkwik(const real_T Linv[25], const real_T Hinv[25],
  const real_T f[5], const real_T Ac[50], const real_T b[10], boolean_T iA[10],
  int32_T maxiter, real_T FeasTol, real_T x[5], real_T lambda[10], int32_T
  *status)
{
  __m128d tmp_0;
  __m128d tmp_1;
  real_T D[25];
  real_T H[25];
  real_T RLinv[25];
  real_T U[25];
  real_T Opt[10];
  real_T Rhs[10];
  real_T cTol[10];
  real_T r[5];
  real_T z[5];
  real_T Xnorm0;
  real_T cMin;
  real_T cVal;
  real_T rMin;
  real_T t;
  int32_T iC[10];
  int32_T U_tmp;
  int32_T b_exponent;
  int32_T exitg1;
  int32_T exitg3;
  int32_T exponent;
  int32_T i;
  int32_T iSave;
  int32_T kDrop;
  int32_T kNext;
  int32_T nA;
  int32_T tmp;
  boolean_T ColdReset;
  boolean_T DualFeasible;
  boolean_T cTolComputed;
  boolean_T exitg2;
  boolean_T exitg4;
  boolean_T guard1;
  boolean_T guard2;
  for (i = 0; i < 5; i++) {
    x[i] = 0.0;
  }

  std::memset(&lambda[0], 0, 10U * sizeof(real_T));
  *status = 1;
  for (i = 0; i < 5; i++) {
    r[i] = 0.0;
  }

  rMin = 0.0;
  cTolComputed = false;
  for (i = 0; i < 10; i++) {
    cTol[i] = 1.0;
    iC[i] = 0;
  }

  nA = 0;
  for (i = 0; i < 10; i++) {
    if (iA[i]) {
      nA++;
      iC[nA - 1] = i + 1;
    }
  }

  guard1 = false;
  if (nA > 0) {
    std::memset(&Opt[0], 0, 10U * sizeof(real_T));
    for (i = 0; i < 5; i++) {
      Rhs[i] = f[i];
      Rhs[i + 5] = 0.0;
    }

    DualFeasible = false;
    ColdReset = false;
    do {
      exitg3 = 0;
      if ((!DualFeasible) && (nA > 0) && (*status <= maxiter)) {
        Xnorm0 = Subsystem_KWIKfactor(Ac, iC, nA, Linv, RLinv, D, H, 5);
        if (Xnorm0 < 0.0) {
          if (ColdReset) {
            *status = -2;
            exitg3 = 2;
          } else {
            nA = 0;
            for (i = 0; i < 10; i++) {
              iA[i] = false;
              iC[i] = 0;
            }

            ColdReset = true;
          }
        } else {
          for (kDrop = 0; kDrop < nA; kDrop++) {
            if (kDrop + 1 > 2147483642) {
              i = MAX_int32_T;
            } else {
              i = kDrop + 6;
            }

            Rhs[i - 1] = b[iC[kDrop] - 1];
            for (i = kDrop + 1; i <= nA; i++) {
              U_tmp = (5 * kDrop + i) - 1;
              U[U_tmp] = 0.0;
              for (iSave = 0; iSave < nA; iSave++) {
                U[U_tmp] += RLinv[(5 * iSave + i) - 1] * RLinv[5 * iSave + kDrop];
              }

              U[kDrop + 5 * (i - 1)] = U[U_tmp];
            }
          }

          for (kDrop = 0; kDrop < 5; kDrop++) {
            Xnorm0 = 0.0;
            for (i = 0; i < 5; i++) {
              Xnorm0 += H[5 * i + kDrop] * Rhs[i];
            }

            Opt[kDrop] = Xnorm0;
            for (iSave = 0; iSave < nA; iSave++) {
              if (iSave + 1 > 2147483642) {
                i = MAX_int32_T;
              } else {
                i = iSave + 6;
              }

              Opt[kDrop] += D[5 * iSave + kDrop] * Rhs[i - 1];
            }
          }

          for (iSave = 0; iSave < nA; iSave++) {
            Xnorm0 = 0.0;
            for (i = 0; i < 5; i++) {
              Xnorm0 += D[5 * iSave + i] * Rhs[i];
            }

            if (iSave + 1 > 2147483642) {
              i = MAX_int32_T;
            } else {
              i = iSave + 6;
            }

            Opt[i - 1] = Xnorm0;
            if (iSave + 1 > 2147483642) {
              i = MAX_int32_T;
              kDrop = MAX_int32_T;
            } else {
              i = iSave + 6;
              kDrop = iSave + 6;
            }

            for (U_tmp = 0; U_tmp < nA; U_tmp++) {
              if (U_tmp + 1 > 2147483642) {
                tmp = MAX_int32_T;
              } else {
                tmp = U_tmp + 6;
              }

              Opt[i - 1] = U[5 * U_tmp + iSave] * Rhs[tmp - 1] + Opt[kDrop - 1];
            }
          }

          Xnorm0 = -1.0E-12;
          kDrop = -1;
          for (iSave = 0; iSave < nA; iSave++) {
            if (iSave + 1 > 2147483642) {
              i = MAX_int32_T;
            } else {
              i = iSave + 6;
            }

            lambda[iC[iSave] - 1] = Opt[i - 1];
            if (iSave + 1 > 2147483642) {
              // out-of-bounds matrix access would cause program termination and was eliminated 
            } else {
              kNext = iSave + 6;
            }

            if ((Opt[kNext - 1] < Xnorm0) && (iSave + 1 <= nA)) {
              kDrop = iSave;
              if (iSave + 1 > 2147483642) {
                i = MAX_int32_T;
              } else {
                i = iSave + 6;
              }

              Xnorm0 = Opt[i - 1];
            }
          }

          if (kDrop + 1 <= 0) {
            DualFeasible = true;
            for (i = 0; i < 5; i++) {
              x[i] = Opt[i];
            }
          } else {
            if (*status > 2147483646) {
              *status = MAX_int32_T;
            } else {
              (*status)++;
            }

            if (*status > 5) {
              nA = 0;
              for (i = 0; i < 10; i++) {
                iA[i] = false;
                iC[i] = 0;
              }

              ColdReset = true;
            } else {
              lambda[iC[kDrop] - 1] = 0.0;
              Subsystem_DropConstraint(kDrop + 1, iA, &nA, iC);
            }
          }
        }
      } else {
        if (nA <= 0) {
          std::memset(&lambda[0], 0, 10U * sizeof(real_T));
          for (kNext = 0; kNext < 5; kNext++) {
            Xnorm0 = 0.0;
            for (i = 0; i < 5; i++) {
              Xnorm0 += -Hinv[5 * i + kNext] * f[i];
            }

            x[kNext] = Xnorm0;
          }
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    for (kNext = 0; kNext < 5; kNext++) {
      Xnorm0 = 0.0;
      for (i = 0; i < 5; i++) {
        Xnorm0 += -Hinv[5 * i + kNext] * f[i];
      }

      x[kNext] = Xnorm0;
    }

    guard1 = true;
  }

  if (guard1) {
    Xnorm0 = Subsystem_norm(x);
    exitg2 = false;
    while ((!exitg2) && (*status <= maxiter)) {
      cMin = -FeasTol;
      kNext = -1;
      for (kDrop = 0; kDrop < 10; kDrop++) {
        if (!cTolComputed) {
          for (i = 0; i < 5; i++) {
            z[i] = std::abs(Ac[10 * i + kDrop] * x[i]);
          }

          cTol[kDrop] = std::fmax(cTol[kDrop], Subsystem_maximum(z));
        }

        if (!iA[kDrop]) {
          cVal = 0.0;
          for (i = 0; i < 5; i++) {
            cVal += Ac[10 * i + kDrop] * x[i];
          }

          cVal = (cVal - b[kDrop]) / cTol[kDrop];
          if (cVal < cMin) {
            cMin = cVal;
            kNext = kDrop;
          }
        }
      }

      cTolComputed = true;
      if (kNext + 1 <= 0) {
        exitg2 = true;
      } else if (*status == maxiter) {
        *status = 0;
        exitg2 = true;
      } else {
        do {
          exitg1 = 0;
          if ((kNext + 1 > 0) && (*status < maxiter)) {
            guard2 = false;
            if (nA == 0) {
              for (i = 0; i < 5; i++) {
                z[i] = 0.0;
              }

              for (i = 0; i < 5; i++) {
                cMin = Ac[10 * i + kNext];
                for (kDrop = 0; kDrop <= 2; kDrop += 2) {
                  tmp_1 = _mm_loadu_pd(&z[kDrop]);
                  _mm_storeu_pd(&z[kDrop], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
                    (&Hinv[5 * i + kDrop]), _mm_set1_pd(cMin)), tmp_1));
                }

                for (kDrop = 4; kDrop < 5; kDrop++) {
                  z[kDrop] += Hinv[5 * i + kDrop] * cMin;
                }
              }

              guard2 = true;
            } else {
              cMin = Subsystem_KWIKfactor(Ac, iC, nA, Linv, RLinv, D, H, 5);
              if (cMin <= 0.0) {
                *status = -2;
                exitg1 = 1;
              } else {
                for (i = 0; i <= 22; i += 2) {
                  tmp_1 = _mm_loadu_pd(&H[i]);
                  _mm_storeu_pd(&U[i], _mm_mul_pd(tmp_1, _mm_set1_pd(-1.0)));
                }

                for (i = 24; i < 25; i++) {
                  U[i] = -H[i];
                }

                for (i = 0; i < 5; i++) {
                  z[i] = 0.0;
                }

                for (i = 0; i < 5; i++) {
                  cMin = Ac[10 * i + kNext];
                  for (kDrop = 0; kDrop <= 2; kDrop += 2) {
                    tmp_1 = _mm_loadu_pd(&U[5 * i + kDrop]);
                    tmp_0 = _mm_loadu_pd(&z[kDrop]);
                    _mm_storeu_pd(&z[kDrop], _mm_add_pd(_mm_mul_pd(tmp_1,
                      _mm_set1_pd(cMin)), tmp_0));
                  }

                  for (kDrop = 4; kDrop < 5; kDrop++) {
                    z[kDrop] += U[5 * i + kDrop] * cMin;
                  }
                }

                for (kDrop = 0; kDrop < nA; kDrop++) {
                  cVal = 0.0;
                  for (i = 0; i < 5; i++) {
                    cVal += Ac[10 * i + kNext] * D[5 * kDrop + i];
                  }

                  r[kDrop] = cVal;
                }

                guard2 = true;
              }
            }

            if (guard2) {
              kDrop = 0;
              cMin = 0.0;
              DualFeasible = true;
              ColdReset = true;
              if (nA > 0) {
                i = 0;
                exitg4 = false;
                while ((!exitg4) && (i <= nA - 1)) {
                  if (r[i] >= 1.0E-12) {
                    ColdReset = false;
                    exitg4 = true;
                  } else {
                    i++;
                  }
                }
              }

              if ((nA != 0) && (!ColdReset)) {
                for (i = 0; i < nA; i++) {
                  cVal = r[i];
                  if (cVal > 1.0E-12) {
                    cVal = lambda[iC[i] - 1] / cVal;
                    if ((kDrop == 0) || (cVal < rMin)) {
                      rMin = cVal;
                      kDrop = i + 1;
                    }
                  }
                }

                if (kDrop > 0) {
                  cMin = rMin;
                  DualFeasible = false;
                }
              }

              t = 0.0;
              for (i = 0; i < 5; i++) {
                t += Ac[10 * i + kNext] * z[i];
              }

              if (t <= 0.0) {
                cVal = 0.0;
                ColdReset = true;
              } else {
                cVal = 0.0;
                for (i = 0; i < 5; i++) {
                  cVal += Ac[10 * i + kNext] * x[i];
                }

                cVal = (b[kNext] - cVal) / t;
                ColdReset = false;
              }

              if (DualFeasible && ColdReset) {
                *status = -1;
                exitg1 = 1;
              } else {
                if (ColdReset) {
                  t = cMin;
                } else if (DualFeasible) {
                  t = cVal;
                } else if (cMin < cVal) {
                  t = cMin;
                } else {
                  t = cVal;
                }

                for (i = 0; i < nA; i++) {
                  iSave = iC[i];
                  lambda[iSave - 1] -= t * r[i];
                  if ((iSave <= 10) && (lambda[iSave - 1] < 0.0)) {
                    lambda[iSave - 1] = 0.0;
                  }
                }

                lambda[kNext] += t;
                std::frexp(1.0, &exponent);
                if (std::abs(t - cMin) < 2.2204460492503131E-16) {
                  Subsystem_DropConstraint(kDrop, iA, &nA, iC);
                }

                if (!ColdReset) {
                  for (i = 0; i <= 2; i += 2) {
                    tmp_1 = _mm_loadu_pd(&z[i]);
                    tmp_0 = _mm_loadu_pd(&x[i]);
                    _mm_storeu_pd(&x[i], _mm_add_pd(_mm_mul_pd(_mm_set1_pd(t),
                      tmp_1), tmp_0));
                  }

                  for (i = 4; i < 5; i++) {
                    x[i] += t * z[i];
                  }

                  std::frexp(1.0, &b_exponent);
                  if (std::abs(t - cVal) < 2.2204460492503131E-16) {
                    if (nA == 5) {
                      *status = -1;
                      exitg1 = 1;
                    } else {
                      if (nA > 2147483646) {
                        nA = MAX_int32_T;
                      } else {
                        nA++;
                      }

                      iC[nA - 1] = kNext + 1;
                      kDrop = nA - 1;
                      exitg4 = false;
                      while ((!exitg4) && (kDrop + 1 > 1)) {
                        i = iC[kDrop - 1];
                        if (iC[kDrop] > i) {
                          exitg4 = true;
                        } else {
                          iSave = iC[kDrop];
                          iC[kDrop] = i;
                          iC[kDrop - 1] = iSave;
                          kDrop--;
                        }
                      }

                      iA[kNext] = true;
                      kNext = -1;
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                } else {
                  (*status)++;
                }
              }
            }
          } else {
            cMin = Subsystem_norm(x);
            if (std::abs(cMin - Xnorm0) > 0.001) {
              Xnorm0 = cMin;
              for (i = 0; i < 10; i++) {
                cTol[i] = std::fmax(std::abs(b[i]), 1.0);
              }

              cTolComputed = false;
            }

            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    }
  }
}

// Model step function
void Subsystem::step()
{
  __m128d tmp_6;
  __m128d tmp_8;
  __m128d tmp_9;
  real_T H_qp_tmp[400];
  real_T H_qp_tmp_0[400];
  real_T tmp_1[80];
  real_T tmp_2[80];
  real_T tmp_3[80];
  real_T H_qp_tmp_1[25];
  real_T R_bar[25];
  real_T P_hat_m[16];
  real_T P_hat_p[16];
  real_T b_I_0[16];
  real_T lam[10];
  real_T tmp_5[10];
  real_T B[8];
  real_T B_tmp[8];
  real_T tmp[8];
  real_T tmp_4[5];
  real_T A[4];
  real_T x_hat_m[4];
  real_T tmp_0[2];
  real_T tmp_7[2];
  real_T B_0;
  real_T a21;
  real_T a22;
  real_T c;
  int32_T B_tmp_tmp;
  int32_T d;
  int32_T e;
  int32_T ia;
  int32_T iac;
  int32_T idxAjj;
  int32_T r1;
  int32_T r2;
  int8_T b_I[16];
  int8_T c_A;
  static const int8_T b_A[25]{ 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 1 };

  static const int8_T c_A_0[400]{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 };

  static const real_T g[50]{ -1.0, -0.0, -0.0, -0.0, -0.0, 1.0, 0.0, 0.0, 0.0,
    0.0, -0.0, -1.0, -0.0, -0.0, -0.0, 0.0, 1.0, 0.0, 0.0, 0.0, -0.0, -0.0, -1.0,
    -0.0, -0.0, 0.0, 0.0, 1.0, 0.0, 0.0, -0.0, -0.0, -0.0, -1.0, -0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, -0.0, -0.0, -0.0, -0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

  boolean_T exitg1;

  // Outputs for Atomic SubSystem: '<Root>/Subsystem'
  // MATLAB Function: '<S1>/MATLAB Function' incorporates:
  //   Inport: '<Root>/rho'
  //   Inport: '<Root>/x_meas'
  //   UnitDelay: '<S1>/Unit Delay'
  //   UnitDelay: '<S1>/Unit Delay1'
  //   UnitDelay: '<S1>/Unit Delay2'

  for (r1 = 0; r1 < 4; r1++) {
    x_hat_m[r1] = ((((Subsystem_ConstP.MATLABFunction_Ad[r1 + 4] *
                      Subsystem_DW.UnitDelay_DSTATE[1] +
                      Subsystem_ConstP.MATLABFunction_Ad[r1] *
                      Subsystem_DW.UnitDelay_DSTATE[0]) +
                     Subsystem_ConstP.MATLABFunction_Ad[r1 + 8] *
                     Subsystem_DW.UnitDelay_DSTATE[2]) +
                    Subsystem_ConstP.MATLABFunction_Ad[r1 + 12] *
                    Subsystem_DW.UnitDelay_DSTATE[3]) +
                   Subsystem_ConstP.MATLABFunction_Bd[r1] *
                   Subsystem_Y.mpccontrolinput) +
      Subsystem_ConstP.MATLABFunction_Ed[r1] * Subsystem_U.roadcurvedisturbance;
    a21 = 0.0;
    c = 0.0;
    a22 = 0.0;
    B_0 = 0.0;
    for (r2 = 0; r2 < 4; r2++) {
      idxAjj = r2 << 2;
      tmp_9 = _mm_set1_pd(Subsystem_DW.UnitDelay1_DSTATE[(r1 << 2) + r2]);
      _mm_storeu_pd(&tmp_7[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Subsystem_ConstP.MATLABFunction_Ad[idxAjj]), tmp_9), _mm_set_pd(c, a21)));
      a21 = tmp_7[0];
      c = tmp_7[1];
      _mm_storeu_pd(&tmp_7[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Subsystem_ConstP.MATLABFunction_Ad[idxAjj + 2]), tmp_9), _mm_set_pd
        (B_0, a22)));
      a22 = tmp_7[0];
      B_0 = tmp_7[1];
    }

    r2 = r1 << 2;
    P_hat_p[r2 + 3] = B_0;
    P_hat_p[r2 + 2] = a22;
    P_hat_p[r2 + 1] = c;
    P_hat_p[r2] = a21;
  }

  for (r1 = 0; r1 < 4; r1++) {
    a21 = P_hat_p[r1 + 4];
    c = P_hat_p[r1];
    a22 = P_hat_p[r1 + 8];
    B_0 = P_hat_p[r1 + 12];
    for (r2 = 0; r2 <= 2; r2 += 2) {
      idxAjj = (r2 << 2) + r1;
      B_tmp_tmp = ((r2 + 1) << 2) + r1;
      _mm_storeu_pd(&tmp_7[0], _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd
        (_mm_mul_pd(_mm_set1_pd(a21), _mm_loadu_pd
                    (&Subsystem_ConstP.MATLABFunction_Ad[r2 + 4])), _mm_mul_pd
         (_mm_set1_pd(c), _mm_loadu_pd(&Subsystem_ConstP.MATLABFunction_Ad[r2]))),
        _mm_mul_pd(_mm_set1_pd(a22), _mm_loadu_pd
                   (&Subsystem_ConstP.MATLABFunction_Ad[r2 + 8]))), _mm_mul_pd
        (_mm_set1_pd(B_0), _mm_loadu_pd(&Subsystem_ConstP.MATLABFunction_Ad[r2 +
        12]))), _mm_set_pd(Subsystem_ConstP.MATLABFunction_Q_kf[B_tmp_tmp],
                           Subsystem_ConstP.MATLABFunction_Q_kf[idxAjj])));
      P_hat_m[idxAjj] = tmp_7[0];
      P_hat_m[B_tmp_tmp] = tmp_7[1];
    }
  }

  for (r1 = 0; r1 < 2; r1++) {
    B_tmp_tmp = r1 << 2;
    B_tmp[B_tmp_tmp] = Subsystem_ConstP.MATLABFunction_H[r1];
    B_tmp[B_tmp_tmp + 1] = Subsystem_ConstP.MATLABFunction_H[r1 + 2];
    B_tmp[B_tmp_tmp + 2] = Subsystem_ConstP.MATLABFunction_H[r1 + 4];
    B_tmp[B_tmp_tmp + 3] = Subsystem_ConstP.MATLABFunction_H[r1 + 6];
    a21 = 0.0;
    c = 0.0;
    a22 = 0.0;
    B_0 = 0.0;
    for (r2 = 0; r2 < 4; r2++) {
      idxAjj = r2 << 2;
      tmp_9 = _mm_set1_pd(B_tmp[B_tmp_tmp + r2]);
      tmp_8 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&P_hat_m[idxAjj]), tmp_9),
                         _mm_set_pd(c, a21));
      _mm_storeu_pd(&tmp_7[0], tmp_8);
      a21 = tmp_7[0];
      c = tmp_7[1];
      tmp_9 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&P_hat_m[idxAjj + 2]), tmp_9),
                         _mm_set_pd(B_0, a22));
      _mm_storeu_pd(&tmp_7[0], tmp_9);
      a22 = tmp_7[0];
      B_0 = tmp_7[1];
    }

    B[B_tmp_tmp + 3] = B_0;
    B[B_tmp_tmp + 2] = a22;
    B[B_tmp_tmp + 1] = c;
    B[B_tmp_tmp] = a21;
  }

  for (r1 = 0; r1 < 4; r1++) {
    a21 = 0.0;
    c = 0.0;
    for (r2 = 0; r2 < 4; r2++) {
      _mm_storeu_pd(&tmp_7[0], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Subsystem_ConstP.MATLABFunction_H[r2 << 1]), _mm_set1_pd(P_hat_m[(r1 <<
        2) + r2])), _mm_set_pd(c, a21)));
      a21 = tmp_7[0];
      c = tmp_7[1];
    }

    r2 = r1 << 1;
    tmp[r2 + 1] = c;
    tmp[r2] = a21;
  }

  for (r1 = 0; r1 < 2; r1++) {
    a21 = tmp[r1 + 2];
    c = tmp[r1];
    a22 = tmp[r1 + 4];
    B_0 = tmp[r1 + 6];
    for (r2 = 0; r2 <= 0; r2 += 2) {
      idxAjj = (r2 + 1) << 2;
      B_tmp_tmp = r2 << 2;
      d = (r2 << 1) + r1;
      iac = ((r2 + 1) << 1) + r1;
      _mm_storeu_pd(&tmp_7[0], _mm_add_pd(_mm_add_pd(_mm_add_pd(_mm_add_pd
        (_mm_mul_pd(_mm_set_pd(B_tmp[idxAjj + 1], B_tmp[B_tmp_tmp + 1]),
                    _mm_set1_pd(a21)), _mm_mul_pd(_mm_set_pd(B_tmp[idxAjj],
        B_tmp[B_tmp_tmp]), _mm_set1_pd(c))), _mm_mul_pd(_mm_set_pd(B_tmp[idxAjj
        + 2], B_tmp[B_tmp_tmp + 2]), _mm_set1_pd(a22))), _mm_mul_pd(_mm_set_pd
        (B_tmp[idxAjj + 3], B_tmp[B_tmp_tmp + 3]), _mm_set1_pd(B_0))),
        _mm_set_pd(Subsystem_ConstP.MATLABFunction_R_kf[iac],
                   Subsystem_ConstP.MATLABFunction_R_kf[d])));
      A[d] = tmp_7[0];
      A[iac] = tmp_7[1];
    }
  }

  if (std::abs(A[1]) > std::abs(A[0])) {
    r1 = 1;
    r2 = 0;
  } else {
    r1 = 0;
    r2 = 1;
  }

  a21 = A[r2] / A[r1];
  c = A[r1 + 2];
  a22 = A[r2 + 2] - c * a21;
  B_tmp_tmp = r1 << 2;
  B_tmp[B_tmp_tmp] = B[0] / A[r1];
  r2 <<= 2;
  B_tmp[r2] = (B[4] - B_tmp[B_tmp_tmp] * c) / a22;
  B_tmp[B_tmp_tmp] -= B_tmp[r2] * a21;
  B_tmp[B_tmp_tmp + 1] = B[1] / A[r1];
  B_tmp[r2 + 1] = (B[5] - B_tmp[B_tmp_tmp + 1] * c) / a22;
  B_tmp[B_tmp_tmp + 1] -= B_tmp[r2 + 1] * a21;
  B_tmp[B_tmp_tmp + 2] = B[2] / A[r1];
  B_tmp[r2 + 2] = (B[6] - B_tmp[B_tmp_tmp + 2] * c) / a22;
  B_tmp[B_tmp_tmp + 2] -= B_tmp[r2 + 2] * a21;
  B_tmp[B_tmp_tmp + 3] = B[3] / A[r1];
  B_tmp[r2 + 3] = (B[7] - B_tmp[B_tmp_tmp + 3] * c) / a22;
  B_tmp[B_tmp_tmp + 3] -= B_tmp[r2 + 3] * a21;
  a21 = x_hat_m[1];
  c = x_hat_m[0];
  a22 = x_hat_m[2];
  B_0 = x_hat_m[3];
  for (r1 = 0; r1 <= 0; r1 += 2) {
    _mm_storeu_pd(&tmp_0[r1], _mm_sub_pd(_mm_loadu_pd
      (&Subsystem_U.noisyprocesssensore1e2[r1]), _mm_add_pd(_mm_add_pd
      (_mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&Subsystem_ConstP.MATLABFunction_H[r1
      + 2]), _mm_set1_pd(a21)), _mm_mul_pd(_mm_loadu_pd
      (&Subsystem_ConstP.MATLABFunction_H[r1]), _mm_set1_pd(c))), _mm_mul_pd
       (_mm_loadu_pd(&Subsystem_ConstP.MATLABFunction_H[r1 + 4]), _mm_set1_pd
        (a22))), _mm_mul_pd(_mm_loadu_pd(&Subsystem_ConstP.MATLABFunction_H[r1 +
      6]), _mm_set1_pd(B_0)))));
  }

  a21 = tmp_0[1];
  c = tmp_0[0];
  for (r1 = 0; r1 <= 2; r1 += 2) {
    tmp_9 = _mm_loadu_pd(&B_tmp[r1 + 4]);
    tmp_8 = _mm_loadu_pd(&B_tmp[r1]);
    tmp_6 = _mm_loadu_pd(&x_hat_m[r1]);
    _mm_storeu_pd(&Subsystem_DW.UnitDelay_DSTATE[r1], _mm_add_pd(_mm_add_pd
      (_mm_mul_pd(tmp_9, _mm_set1_pd(a21)), _mm_mul_pd(tmp_8, _mm_set1_pd(c))),
      tmp_6));
  }

  for (r1 = 0; r1 < 16; r1++) {
    b_I[r1] = 0;
  }

  b_I[0] = 1;
  b_I[5] = 1;
  b_I[10] = 1;
  b_I[15] = 1;
  for (r1 = 0; r1 < 4; r1++) {
    a21 = B_tmp[r1 + 4];
    c = B_tmp[r1];
    for (r2 = 0; r2 < 4; r2++) {
      idxAjj = r2 << 1;
      B_tmp_tmp = (r2 << 2) + r1;
      b_I_0[B_tmp_tmp] = static_cast<real_T>(b_I[B_tmp_tmp]) -
        (Subsystem_ConstP.MATLABFunction_H[idxAjj + 1] * a21 +
         Subsystem_ConstP.MATLABFunction_H[idxAjj] * c);
      P_hat_p[r2 + (r1 << 2)] = 0.0;
    }
  }

  for (r1 = 0; r1 < 4; r1++) {
    B_tmp_tmp = r1 << 2;
    a21 = P_hat_p[B_tmp_tmp];
    c = P_hat_p[B_tmp_tmp + 1];
    a22 = P_hat_p[B_tmp_tmp + 2];
    B_0 = P_hat_p[B_tmp_tmp + 3];
    for (r2 = 0; r2 < 4; r2++) {
      idxAjj = r2 << 2;
      tmp_9 = _mm_set1_pd(P_hat_m[B_tmp_tmp + r2]);
      tmp_8 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&b_I_0[idxAjj]), tmp_9),
                         _mm_set_pd(c, a21));
      _mm_storeu_pd(&tmp_7[0], tmp_8);
      a21 = tmp_7[0];
      c = tmp_7[1];
      tmp_9 = _mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&b_I_0[idxAjj + 2]), tmp_9),
                         _mm_set_pd(B_0, a22));
      _mm_storeu_pd(&tmp_7[0], tmp_9);
      a22 = tmp_7[0];
      B_0 = tmp_7[1];
    }

    P_hat_p[B_tmp_tmp + 3] = B_0;
    P_hat_p[B_tmp_tmp + 2] = a22;
    P_hat_p[B_tmp_tmp + 1] = c;
    P_hat_p[B_tmp_tmp] = a21;
  }

  for (r1 = 0; r1 <= 2; r1 += 2) {
    r2 = r1 << 2;
    idxAjj = (r1 + 1) << 2;
    tmp_9 = _mm_set1_pd(2.0);
    tmp_8 = _mm_div_pd(_mm_add_pd(_mm_set_pd(P_hat_p[idxAjj], P_hat_p[r2]),
      _mm_loadu_pd(&P_hat_p[r1])), tmp_9);
    _mm_storeu_pd(&tmp_7[0], tmp_8);
    Subsystem_DW.UnitDelay1_DSTATE[r2] = tmp_7[0];
    Subsystem_DW.UnitDelay1_DSTATE[idxAjj] = tmp_7[1];
    tmp_8 = _mm_div_pd(_mm_add_pd(_mm_set_pd(P_hat_p[idxAjj + 1], P_hat_p[r2 + 1]),
      _mm_loadu_pd(&P_hat_p[r1 + 4])), tmp_9);
    _mm_storeu_pd(&tmp_7[0], tmp_8);
    Subsystem_DW.UnitDelay1_DSTATE[r2 + 1] = tmp_7[0];
    Subsystem_DW.UnitDelay1_DSTATE[idxAjj + 1] = tmp_7[1];
    tmp_8 = _mm_div_pd(_mm_add_pd(_mm_set_pd(P_hat_p[idxAjj + 2], P_hat_p[r2 + 2]),
      _mm_loadu_pd(&P_hat_p[r1 + 8])), tmp_9);
    _mm_storeu_pd(&tmp_7[0], tmp_8);
    Subsystem_DW.UnitDelay1_DSTATE[r2 + 2] = tmp_7[0];
    Subsystem_DW.UnitDelay1_DSTATE[idxAjj + 2] = tmp_7[1];
    tmp_9 = _mm_div_pd(_mm_add_pd(_mm_set_pd(P_hat_p[idxAjj + 3], P_hat_p[r2 + 3]),
      _mm_loadu_pd(&P_hat_p[r1 + 12])), tmp_9);
    _mm_storeu_pd(&tmp_7[0], tmp_9);
    Subsystem_DW.UnitDelay1_DSTATE[r2 + 3] = tmp_7[0];
    Subsystem_DW.UnitDelay1_DSTATE[idxAjj + 3] = tmp_7[1];
  }

  // End of MATLAB Function: '<S1>/MATLAB Function'

  // MATLAB Function: '<S1>/MATLAB Function1' incorporates:
  //   Inport: '<Root>/rho_preview'
  //   UnitDelay: '<S1>/Unit Delay2'

  r1 = -1;
  for (r2 = 0; r2 < 20; r2++) {
    for (idxAjj = 0; idxAjj < 4; idxAjj++) {
      B_tmp_tmp = idxAjj << 2;
      a21 = Subsystem_ConstP.MATLABFunction1_Q[B_tmp_tmp];
      c = Subsystem_ConstP.MATLABFunction1_Q[B_tmp_tmp + 1];
      a22 = Subsystem_ConstP.MATLABFunction1_Q[B_tmp_tmp + 2];
      B_0 = Subsystem_ConstP.MATLABFunction1_Q[B_tmp_tmp + 3];
      for (B_tmp_tmp = 0; B_tmp_tmp < 20; B_tmp_tmp++) {
        c_A = c_A_0[20 * r2 + B_tmp_tmp];
        Subsystem_B.Q_bar[r1 + 1] = static_cast<real_T>(c_A) * a21;
        Subsystem_B.Q_bar[r1 + 2] = static_cast<real_T>(c_A) * c;
        Subsystem_B.Q_bar[r1 + 3] = static_cast<real_T>(c_A) * a22;
        Subsystem_B.Q_bar[r1 + 4] = static_cast<real_T>(c_A) * B_0;
        r1 += 4;
      }
    }
  }

  r2 = -1;
  for (idxAjj = 0; idxAjj < 5; idxAjj++) {
    for (B_tmp_tmp = 0; B_tmp_tmp <= 2; B_tmp_tmp += 2) {
      r1 = 5 * idxAjj + B_tmp_tmp;
      _mm_storeu_pd(&R_bar[(r2 + B_tmp_tmp) + 1], _mm_mul_pd(_mm_set_pd(
        static_cast<real_T>(b_A[r1 + 1]), static_cast<real_T>(b_A[r1])),
        _mm_set1_pd(0.1)));
    }

    for (B_tmp_tmp = 4; B_tmp_tmp < 5; B_tmp_tmp++) {
      R_bar[(r2 + B_tmp_tmp) + 1] = static_cast<real_T>(b_A[5 * idxAjj +
        B_tmp_tmp]) * 0.1;
    }

    r2 += 5;
  }

  for (r1 = 0; r1 < 80; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      B_tmp_tmp = 5 * r1 + r2;
      H_qp_tmp[B_tmp_tmp] = Subsystem_ConstP.MATLABFunction1_Phi[80 * r2 + r1];
      H_qp_tmp_0[B_tmp_tmp] = 0.0;
    }
  }

  for (r1 = 0; r1 < 80; r1++) {
    for (r2 = 0; r2 < 80; r2++) {
      a21 = Subsystem_B.Q_bar[80 * r1 + r2];
      for (idxAjj = 0; idxAjj <= 2; idxAjj += 2) {
        tmp_9 = _mm_loadu_pd(&H_qp_tmp[5 * r2 + idxAjj]);
        B_tmp_tmp = 5 * r1 + idxAjj;
        tmp_8 = _mm_loadu_pd(&H_qp_tmp_0[B_tmp_tmp]);
        _mm_storeu_pd(&H_qp_tmp_0[B_tmp_tmp], _mm_add_pd(_mm_mul_pd(tmp_9,
          _mm_set1_pd(a21)), tmp_8));
      }

      for (idxAjj = 4; idxAjj < 5; idxAjj++) {
        B_tmp_tmp = 5 * r1 + idxAjj;
        H_qp_tmp_0[B_tmp_tmp] += H_qp_tmp[5 * r2 + idxAjj] * a21;
      }
    }
  }

  for (r1 = 0; r1 < 5; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      a21 = 0.0;
      for (idxAjj = 0; idxAjj < 80; idxAjj++) {
        a21 += H_qp_tmp_0[5 * idxAjj + r1] *
          Subsystem_ConstP.MATLABFunction1_Phi[80 * r2 + idxAjj];
      }

      B_tmp_tmp = 5 * r2 + r1;
      H_qp_tmp_1[B_tmp_tmp] = R_bar[B_tmp_tmp] + a21;
    }
  }

  for (r1 = 0; r1 <= 22; r1 += 2) {
    tmp_9 = _mm_loadu_pd(&H_qp_tmp_1[r1]);
    _mm_storeu_pd(&R_bar[r1], _mm_mul_pd(_mm_set1_pd(2.0), tmp_9));
  }

  for (r1 = 24; r1 < 25; r1++) {
    R_bar[r1] = 2.0 * H_qp_tmp_1[r1];
  }

  for (r1 = 0; r1 < 5; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      B_tmp_tmp = 5 * r1 + r2;
      H_qp_tmp_1[B_tmp_tmp] = (R_bar[5 * r2 + r1] + R_bar[B_tmp_tmp]) / 2.0;
    }
  }

  r1 = 0;
  r2 = 0;
  exitg1 = false;
  while ((!exitg1) && (r2 < 5)) {
    idxAjj = r2 * 5 + r2;
    a21 = 0.0;
    if (r2 >= 1) {
      for (B_tmp_tmp = 0; B_tmp_tmp < r2; B_tmp_tmp++) {
        c = H_qp_tmp_1[B_tmp_tmp * 5 + r2];
        a21 += c * c;
      }
    }

    a21 = H_qp_tmp_1[idxAjj] - a21;
    if (a21 > 0.0) {
      a21 = std::sqrt(a21);
      H_qp_tmp_1[idxAjj] = a21;
      if (r2 + 1 < 5) {
        if (r2 != 0) {
          d = ((r2 - 1) * 5 + r2) + 2;
          for (iac = r2 + 2; iac <= d; iac += 5) {
            B_tmp_tmp = iac - r2;
            c = -H_qp_tmp_1[div_nde_s32_floor(B_tmp_tmp - 2, 5) * 5 + r2];
            e = B_tmp_tmp + 3;
            for (ia = iac; ia <= e; ia++) {
              B_tmp_tmp = ((idxAjj + ia) - iac) + 1;
              H_qp_tmp_1[B_tmp_tmp] += H_qp_tmp_1[ia - 1] * c;
            }
          }
        }

        a21 = 1.0 / a21;
        B_tmp_tmp = (idxAjj - r2) + 5;
        d = (((((B_tmp_tmp - idxAjj) - 1) / 2) << 1) + idxAjj) + 2;
        iac = d - 2;
        for (e = idxAjj + 2; e <= iac; e += 2) {
          tmp_9 = _mm_loadu_pd(&H_qp_tmp_1[e - 1]);
          _mm_storeu_pd(&H_qp_tmp_1[e - 1], _mm_mul_pd(tmp_9, _mm_set1_pd(a21)));
        }

        for (e = d; e <= B_tmp_tmp; e++) {
          H_qp_tmp_1[e - 1] *= a21;
        }
      }

      r2++;
    } else {
      H_qp_tmp_1[idxAjj] = a21;
      r1 = r2 + 1;
      exitg1 = true;
    }
  }

  if (r1 == 0) {
    r1 = 6;
  }

  for (r2 = 2; r2 < r1; r2++) {
    for (idxAjj = 0; idxAjj <= r2 - 2; idxAjj++) {
      H_qp_tmp_1[idxAjj + 5 * (r2 - 1)] = 0.0;
    }
  }

  for (r1 = 0; r1 < 25; r1++) {
    R_bar[r1] = b_A[r1];
  }

  Subsystem_trisolve(H_qp_tmp_1, R_bar);
  std::memset(&tmp_1[0], 0, 80U * sizeof(real_T));
  for (r1 = 0; r1 < 4; r1++) {
    a21 = Subsystem_DW.UnitDelay_DSTATE[r1];
    for (r2 = 0; r2 <= 78; r2 += 2) {
      tmp_9 = _mm_loadu_pd(&tmp_1[r2]);
      _mm_storeu_pd(&tmp_1[r2], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Subsystem_ConstP.MATLABFunction1_F[80 * r1 + r2]), _mm_set1_pd(a21)),
        tmp_9));
    }
  }

  std::memset(&tmp_2[0], 0, 80U * sizeof(real_T));
  for (r1 = 0; r1 < 20; r1++) {
    a21 = Subsystem_U.roadcurvelookahead[r1];
    for (r2 = 0; r2 <= 78; r2 += 2) {
      tmp_9 = _mm_loadu_pd(&tmp_2[r2]);
      _mm_storeu_pd(&tmp_2[r2], _mm_add_pd(_mm_mul_pd(_mm_loadu_pd
        (&Subsystem_ConstP.MATLABFunction1_Gamma[80 * r1 + r2]), _mm_set1_pd(a21)),
        tmp_9));
    }
  }

  for (r1 = 0; r1 < 80; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      H_qp_tmp_0[r2 + 5 * r1] = 0.0;
    }

    for (r2 = 0; r2 < 80; r2++) {
      a21 = Subsystem_B.Q_bar[80 * r1 + r2];
      for (idxAjj = 0; idxAjj <= 2; idxAjj += 2) {
        tmp_9 = _mm_loadu_pd(&H_qp_tmp[5 * r2 + idxAjj]);
        B_tmp_tmp = 5 * r1 + idxAjj;
        tmp_8 = _mm_loadu_pd(&H_qp_tmp_0[B_tmp_tmp]);
        _mm_storeu_pd(&H_qp_tmp_0[B_tmp_tmp], _mm_add_pd(_mm_mul_pd(_mm_mul_pd
          (tmp_9, _mm_set1_pd(2.0)), _mm_set1_pd(a21)), tmp_8));
      }

      for (idxAjj = 4; idxAjj < 5; idxAjj++) {
        B_tmp_tmp = 5 * r1 + idxAjj;
        H_qp_tmp_0[B_tmp_tmp] += H_qp_tmp[5 * r2 + idxAjj] * 2.0 * a21;
      }
    }

    tmp_3[r1] = tmp_1[r1] + tmp_2[r1];
  }

  for (r1 = 0; r1 < 5; r1++) {
    for (r2 = 0; r2 < 5; r2++) {
      a21 = 0.0;
      for (idxAjj = 0; idxAjj < 5; idxAjj++) {
        a21 += R_bar[5 * r2 + idxAjj] * R_bar[5 * r1 + idxAjj];
      }

      H_qp_tmp_1[r2 + 5 * r1] = a21;
    }

    tmp_4[r1] = 0.0;
  }

  for (r1 = 0; r1 < 80; r1++) {
    a21 = tmp_3[r1];
    for (r2 = 0; r2 <= 2; r2 += 2) {
      tmp_9 = _mm_loadu_pd(&H_qp_tmp_0[5 * r1 + r2]);
      tmp_8 = _mm_loadu_pd(&tmp_4[r2]);
      _mm_storeu_pd(&tmp_4[r2], _mm_add_pd(_mm_mul_pd(tmp_9, _mm_set1_pd(a21)),
        tmp_8));
    }

    for (r2 = 4; r2 < 5; r2++) {
      tmp_4[r2] += H_qp_tmp_0[5 * r1 + r2] * a21;
    }
  }

  for (r1 = 0; r1 < 5; r1++) {
    tmp_5[r1] = -0.43633231299858238;
    tmp_5[r1 + 5] = -0.43633231299858238;
  }

  Subsystem_qpkwik(R_bar, H_qp_tmp_1, tmp_4, g, tmp_5, Subsystem_DW.iA0_prev,
                   120, 1.0E-6, Subsystem_Y.u_horizon, lam, &r1);
  if (r1 <= 0) {
    for (idxAjj = 0; idxAjj < 5; idxAjj++) {
      Subsystem_Y.u_horizon[idxAjj] = 0.0;
    }
  }

  Subsystem_Y.mpccontrolinput = Subsystem_Y.u_horizon[0];

  // End of MATLAB Function: '<S1>/MATLAB Function1'
  // End of Outputs for SubSystem: '<Root>/Subsystem'

  // Outport: '<Root>/x_hat'
  Subsystem_Y.x_hat[0] = Subsystem_DW.UnitDelay_DSTATE[0];
  Subsystem_Y.x_hat[1] = Subsystem_DW.UnitDelay_DSTATE[1];
  Subsystem_Y.x_hat[2] = Subsystem_DW.UnitDelay_DSTATE[2];
  Subsystem_Y.x_hat[3] = Subsystem_DW.UnitDelay_DSTATE[3];
}

// Model initialize function
void Subsystem::initialize()
{
  // SystemInitialize for Atomic SubSystem: '<Root>/Subsystem'
  // InitializeConditions for UnitDelay: '<S1>/Unit Delay1'
  std::memcpy(&Subsystem_DW.UnitDelay1_DSTATE[0],
              &Subsystem_ConstP.UnitDelay1_InitialCondition[0], sizeof(real_T) <<
              4U);

  // InitializeConditions for UnitDelay: '<S1>/Unit Delay'
  Subsystem_DW.UnitDelay_DSTATE[0] = 1.0;
  Subsystem_DW.UnitDelay_DSTATE[1] = 0.0;
  Subsystem_DW.UnitDelay_DSTATE[2] = 0.0087266462599716477;
  Subsystem_DW.UnitDelay_DSTATE[3] = 0.0;

  // End of SystemInitialize for SubSystem: '<Root>/Subsystem'
}

// Model terminate function
void Subsystem::terminate()
{
  // (no terminate code required)
}

const char_T* Subsystem::RT_MODEL_Subsystem_T::getErrorStatus() const
{
  return (errorStatus);
}

void Subsystem::RT_MODEL_Subsystem_T::setErrorStatus(const char_T* const
  volatile aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

// Constructor
Subsystem::Subsystem() :
  Subsystem_U(),
  Subsystem_Y(),
  Subsystem_B(),
  Subsystem_DW(),
  Subsystem_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
// Currently there is no destructor body generated.
Subsystem::~Subsystem() = default;

// Real-Time Model get method
Subsystem::RT_MODEL_Subsystem_T * Subsystem::getRTM()
{
  return (&Subsystem_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
