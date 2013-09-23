#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   1cl :    A one-cell, two-substrate enzyme model */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  /* System generated locals */
integer dfdu_dim1, dfdp_dim1;

    /* Local variables */
  doublereal drda, drdk, drds, a, d, r, s, a0, s0, al, rh, rk;

  dfdp_dim1 = ndim;
  dfdu_dim1 = ndim;

  s = u[0];
  a = u[1];

  s0 = par[1];
  a0 = par[2];
  al = par[3];
  rh = par[4];
  rk = par[5];

  d = s + 1 + rk * (s * s);
  r = s * a / d;

  f[0] = s0 - s - rh * r;
  f[1] = al * (a0 - a) - rh * r;

  if (ijac == 0) {
    return 0;
  }

  drds = (a * d - s * a * (rk * 2 * s + 1)) / (d * d);
  drda = s / d;
  drdk = -(s * (s * s)) * a / (d * d);

  ARRAY2D(dfdu,0,0) = -1 - rh * drds;
  ARRAY2D(dfdu,0,1) = -rh * drda;
  ARRAY2D(dfdu,1,0) = -rh * drds;
  ARRAY2D(dfdu,1,1) = -al - rh * drda;

  if (ijac == 1) {
    return 0;
  }
/*      *Parameter derivatives */

  ARRAY2D(dfdp,0,1) = 1.;
  ARRAY2D(dfdp,0,2) = 0.;
  ARRAY2D(dfdp,0,3) = 0.;
  ARRAY2D(dfdp,0,4) = -r;
  ARRAY2D(dfdp,0,5) = -rh * drdk;

  ARRAY2D(dfdp,1,1) = 0.;
  ARRAY2D(dfdp,1,2) = al;
  ARRAY2D(dfdp,1,3) = a0 - a;
  ARRAY2D(dfdp,1,4) = -r;
  ARRAY2D(dfdp,1,5) = -rh * drdk;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  par[1] = (doublereal)110.;
  par[2] = (doublereal)500.;
  par[3] = (doublereal).2;
  par[4] = (doublereal)2.021628;
  par[5] = (doublereal).1;

  u[0] = (doublereal)45.55974;
  u[1] = (doublereal)177.7987;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublereal *u0, const doublereal *u1, integer ijac,
          doublereal *fb, doublereal *dbc)
{
  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int icnd (integer ndim, const doublereal *par, const integer *icp,
          integer nint, const doublereal *u, const doublereal *uold,
          const doublereal *udot, const doublereal *upold, integer ijac,
          doublereal *fi, doublereal *dint)
{
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
