#include "auto_f2c.h"

struct {
  integer ifrst;
} frst_;

#define frst_1 frst_

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   nag :    Heteroclinic orbits : A saddle-saddle connection */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* Parameter assignment: */

/*           PAR(1) , PAR(2) : a      , c      (parameters) */
/*           PAR(3) , PAR(4) : eps-0  , eps-1  (radii) */
/*           PAR(5) , PAR(6) : mu-0   , mu-1   (eigenvalues) */
/*           PAR(7) , PAR(8) : v-0(1) , v-0(2) (eigenvector) */
/*           PAR(9) , PAR(10): v-1(1) , v-1(2) (eigenvector) */
/*           PAR(11)         : period */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  doublereal dummy, period;

  ffff(2, &u[0], icp, par, 0, &f[0], &dummy);

  period = par[11];
  f[0] = period * f[0];
  f[1] = period * f[1];

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int ffff (integer ndm, const doublereal *u, const integer *icp, const doublereal *par, integer ijac, doublereal *f, doublereal *dfdu)
{
  /* System generated locals */
integer dfdu_dim1;

    /* Local variables */
  doublereal a, c;

  dfdu_dim1 = ndm;

    /* Function Body */
  a = par[1];
  c = par[2];
  f[0] = u[1];
  f[1] = c * u[1] - u[0] * (1 - u[0]) * (u[0] - a);

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = 0.;
  ARRAY2D(dfdu,0,1) = 1.;

  ARRAY2D(dfdu,1,0) = -(1 - u[0]) * (u[0] - a) + 
    u[0] * (u[0] - a) - u[0] * (1 - u[0]);
  ARRAY2D(dfdu,1,1) = c;

  return 0;
}
/* ffff_ */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  doublereal sign, e, r, x, u0, v0, v1, v2, period, eps;

  /* The following initialization is done only in the first call */

  if (frst_1.ifrst != 1) {
    frst_1.ifrst = 1;
    /*        Select period and connection (read from the constants-file) 
     */
    period = (doublereal)100.;
    sign = (doublereal)1.;
    r = sqrt(2.) * (doublereal).5;
    v1 = (doublereal)1. / sqrt(r * r + 1);
    v2 = r / sqrt(r * r + 1);
    x = period * (doublereal)-.5;
    e = exp(x / sqrt(2.));
    u0 = e / (e + 1);
    v0 = e / ((e + 1) * (e + 1)) / sqrt(2.);
    eps = sqrt(u0 * u0 + v0 * v0);
    par[1] = (doublereal).5;
    par[2] = 0.;
    par[3] = eps;
    par[4] = eps;
    par[5] = r;
    par[6] = -r;
    par[7] = sign * v1;
    par[8] = sign * v2;
    par[9] = -sign * v1;
    par[10] = sign * v2;
    par[11] = period;
    par[12] = sign;
  }
/* Specify exact solution as starting point : */

  period = par[11];
  sign = par[12];

  x = period * sign * (t - (doublereal).5);
  e = exp(x / sqrt(2.));
  u[0] = e / (e + 1);
  u[1] = sign * e / ((e + 1) * (e + 1)) / sqrt(2.);

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublereal *u0, const doublereal *u1, integer ijac,
          doublereal *fb, doublereal *dbc)
{
  doublereal dgdu0[4], dgdu1[4], g0[2], g1[2], v0[2], v1[2];

  v0[0] = u0[0] - par[3] * par[7];
  v0[1] = u0[1] - par[3] * par[8];
  v1[0] = u1[0] - par[4] * par[9];
  v1[1] = u1[1] - par[4] * par[10];

  ffff(2, v0, &icp[0], &par[0], 1, g0, dgdu0);
  ffff(2, v1, &icp[0], &par[0], 1, g1, dgdu1);

  fb[0] = dgdu0[0] * par[7] + dgdu0[2] * par[8] - par[5] * par[7];
  fb[1] = dgdu0[1] * par[7] + dgdu0[3] * par[8] - par[5] * par[8];
  fb[2] = dgdu1[0] * par[9] + dgdu1[2] * par[10] - par[6] * par[9];
  fb[3] = dgdu1[1] * par[9] + dgdu1[3] * par[10] - par[6] * par[10];
  fb[4] = par[7] * par[7] + par[8] * par[8] - 1;
  fb[5] = par[9] * par[9] + par[10] * par[10] - 1;
  fb[6] = g0[0];
  fb[7] = g0[1];
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
  doublereal dfdu[4], f[2], f0[2], dummy;

  ffff(2, &u[0], &icp[0], par, 1, f, dfdu);
  ffff(2, &uold[0], &icp[0], par, 0, f0, &dummy);

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
