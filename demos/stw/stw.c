#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   stw :         Sharp traveling waves */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* Parameter assignment: ( Components of PAR(.) ) */

/*      PAR :             (1)  : homotopy parameter */
/*                   (2)  (3)  : A0, A1, A2      (problem parameters) */
/*              (4)  (5)  (6)  : B0, B1, B2      (problem parameters) */
/*              (7)  (8)  (9)  : C0, C1, C2      (problem parameters) */
/*                       (10)  :         c       (wave speed) */
/*                       (11)  :         T       (period) */
/*                  (12) (13)  : eps-0, eps-1    (radii) */
/*                  (14) (15)  : mu-0 , mu-1     (eigenvalues) */
/*                  (16) (17)  : v-0(1), v-0(2)  (eigenvector) */
/*                  (18) (19)  : v-1(1), v-1(2)  (eigenvector) */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  doublereal period;

  period = par[10];
  ffff(ndim, &u[0], icp, par, ijac, &f[0], dfdu);
  f[0] = period * f[0];
  f[1] = period * f[1];

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int ffff (integer ndim, const doublereal *u, const integer *icp, const doublereal *par, integer ijac, doublereal *f, doublereal *dfdu)
{
  /* System generated locals */
  integer dfdu_dim1;

  /* Local variables */
  doublereal c, fa, fb, fc, dfa, dfb, dfc;

  doublereal tmp[9];
  /*The reduced system for traveling waves is defined here. */
  /*A separate subroutine is used because the system and the Jacobian are also needed in the subroutines*/
  /*BCND and ICND below. The computation should be done with JAC=0. The derivatives*/
  /* below are for use in BCND and ICND only. */


/* A0, A1, A2: */
  dfdu_dim1 = ndim;

  tmp[1] = (1 - par[1]) * 2 + par[1] * 2;
  tmp[2] = par[1];

  /* B0, B1, B2: */
  tmp[3] = (1 - par[1]) * 2;
  tmp[4] = par[1];
  tmp[5] = 0.;

  /* C0, C1, C2: */
  tmp[6] = 0.;
  tmp[7] = 1 - par[1] + par[1];
  tmp[8] = -(1 - par[1]) + (-par[1]);

  fa = tmp[1] * u[0] + tmp[2] * (u[0] * u[0]);
  fb = tmp[3] + tmp[4] * u[0] + tmp[5] * (u[0] * u[0]);
  fc = tmp[6] + tmp[7] * u[0] + tmp[8] * (u[0] * u[0]);

  c = par[9];

  f[0] = fa * u[1];
  f[1] = -c * u[1] - fb * (u[1] * u[1]) - fc;

  if (ijac == 0) {
    return 0;
  }

  dfa = tmp[1] + tmp[2] * 2 * u[0];
  dfb = tmp[4] + tmp[5] * 2 * u[0];
  dfc = tmp[7] + tmp[8] * 2 * u[0];

  ARRAY2D(dfdu,0,0) = dfa * u[1];
  ARRAY2D(dfdu,0,1) = fa;

  ARRAY2D(dfdu,1,0) = -dfb * (u[1] * u[1]) - dfc;
  ARRAY2D(dfdu,1,1) = -c - fb * 2 * u[1];

  return 0;
}
/* ffff_ */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  doublereal e, period, tsc;

  /* homotopy parameter : */
  par[1] = 0.;

  /* starting period */
  period = (doublereal)100.;

  /* c, T: */
  par[9] = 1.;
  par[10] = period;

  /* eps-0, eps-1: */
  par[11] = sqrt(5.) * (doublereal).5 / (exp(period * (doublereal).5) + 1);
  par[12] = par[11];

  /*  mu-0,  mu-1: */
  par[13] = 1.;
  par[14] = -1.;

  /* v-0(1), v-0(2): */
  par[15] = 2 / sqrt(5.);
  par[16] = 1 / sqrt(5.);

  /* v-1(1), v-1(2): */
  par[17] = 1.;
  par[18] = 0.;

  /* Exact solution */
  tsc = period * (t - (doublereal).5);
  e = exp(tsc);
  u[0] = 1 / (e + 1);
  u[1] = e * (doublereal)-.5 / (e + 1);

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublereal *u0, const doublereal *u1, integer ijac,
          doublereal *fb, doublereal *dbc)
{
  /* System generated locals */
integer dbc_dim1;
  doublereal dgdu0[4], dgdu1[4], g0[2], g1[2], v0[2], v1[2];

  dbc_dim1 = nbc;

  v0[0] = u0[0] - par[11] * par[15];
  v0[1] = u0[1] - par[11] * par[16];
  v1[0] = u1[0] - par[12] * par[17];
  v1[1] = u1[1] - par[12] * par[18];

  ffff(ndim, v0, &icp[0], par, 1, g0, dgdu0);
  ffff(ndim, v1, &icp[0], par, 1, g1, dgdu1);

/* Define eigenvalues and eigenvectors at t=0: */
  fb[0] = dgdu0[0] * par[15] + dgdu0[2] * par[16] - par[13] * par[15];
  fb[1] = dgdu0[1] * par[15] + dgdu0[3] * par[16] - par[13] * par[16];

/* Define eigenvalues and eigenvectors at t=1: */
  fb[2] = dgdu1[0] * par[17] + dgdu1[2] * par[18] - par[14] * par[17];
  fb[3] = dgdu1[1] * par[17] + dgdu1[3] * par[18] - par[14] * par[18];

/* Normalize the eigenvectors: */
  fb[4] = par[15] * par[15] + par[16] * par[16] - 1;
  fb[5] = par[17] * par[17] + par[18] * par[18] - 1;

/* Boundary condition at t=0: */
  fb[6] = g0[0];
  fb[7] = g0[1];

/* Boundary condition at t=1: */
  fb[8] = g1[0];
  fb[9] = g1[1];

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int icnd (integer ndim, const doublereal *par, const integer *icp,
          integer nint, const doublereal *u, const doublereal *uold,
          const doublereal *udot, const doublereal *upold, integer ijac,
          doublereal *fi, doublereal *dint)
{
  /* System generated locals */
integer dint_dim1;

    /* Local variables */
  doublereal dfdu[4], dgdu0, f[2], f0[2];

  dint_dim1 = nint;

  ffff(ndim, u, icp, par, 1, f, dfdu);
  ffff(ndim, uold, icp, par, 0, f0, &dgdu0);

/* The integral phase condition is defined here: */
  fi[0] = (f[0] - f0[0]) * (dfdu[0] * f[0] + dfdu[2] * f[1]) + 
    (f[1] - f0[1]) * (dfdu[1] * f[0] + dfdu[3] * f[1]);

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int fopt (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *fs, doublereal *dfdu, doublereal *dfdp)
{
  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int pvls (integer ndim, const doublereal *u,
          doublereal *par)
{
  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */


