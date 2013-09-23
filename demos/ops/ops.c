#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*       ops :    Optimization of periodic solutions */
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
integer i, j;
  doublereal x, y, z, p1, p2, p3, p4;

  dfdp_dim1 = ndim;
  dfdu_dim1 = ndim;

  x = u[0];
  y = u[1];
  z = u[2];

  p1 = par[1];
  p2 = par[2];
  p3 = par[3];
  p4 = par[4];

  f[0] = (-p4 * (x * (x * x) / 3 - x) + (z - x) / p2 - y) / p1;
  f[1] = x - p3;
  f[2] = -(z - x) / p2;

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = (-p4 * (x * x - 1) - 1 / p2) / p1;
  ARRAY2D(dfdu,0,1) = -1 / p1;
  ARRAY2D(dfdu,0,2) = 1 / (p2 * p1);

  ARRAY2D(dfdu,1,0) = 1.;
  ARRAY2D(dfdu,1,1) = 0.;
  ARRAY2D(dfdu,1,2) = 0.;

  ARRAY2D(dfdu,2,0) = 1 / p2;
  ARRAY2D(dfdu,2,1) = 0.;
  ARRAY2D(dfdu,2,2) = -1 / p2;

  if (ijac == 1) {
    return 0;
  }
/*      *Parameter derivatives */
  for (i = 0; i < 3; ++i) {
    for (j = 0; j < 9; ++j) {
      ARRAY2D(dfdp, i, j) = 0.;
    }
  }

  ARRAY2D(dfdp,0,1) = -(-p4 * (x * (x * x) / 3 - x) + 
			(z - x) / p2 - y) / (p1 * p1);
  ARRAY2D(dfdp,0,2) = -(z - x) / (p2 * p2 * p1);
  ARRAY2D(dfdp,0,3) = 0.;
  ARRAY2D(dfdp,0,4) = -(x * (x * x) / 3 - x) / p1;

  ARRAY2D(dfdp,1,1) = 0.;
  ARRAY2D(dfdp,1,2) = 0.;
  ARRAY2D(dfdp,1,3) = -1.;
  ARRAY2D(dfdp,1,4) = 0.;

  ARRAY2D(dfdp,2,1) = 0.;
  ARRAY2D(dfdp,2,2) = (z - x) / (p2 * p2);
  ARRAY2D(dfdp,2,3) = 0.;
  ARRAY2D(dfdp,2,4) = 0.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  doublereal p1, p2, p3, p4;

  p1 = (doublereal).5;
  p2 = 4.;
  p3 = (doublereal).9;
  p4 = (doublereal)2.;

  u[0] = p3;
  u[1] = -p4 * (p3 * (p3 * p3) / 3 - p3);
  u[2] = p3;

  par[1] = p1;
  par[2] = p2;
  par[3] = p3;
  par[4] = p4;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int fopt (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *fs, doublereal *dfdu, doublereal *dfdp)
{
  integer i;

  *fs = par[3];

  if (ijac == 0) {
    return 0;
  }

  for (i = 0; i < ndim; ++i) {
    dfdu[i] = 0.;
    /* L1: */
  }

  if (ijac == 1) {
    return 0;
  }
/*      *Parameter derivatives */
  for (i = 0; i < 9; ++i) {
    dfdp[i] = 0.;
    /* L2: */
  }

  dfdp[3] = 1.;

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
int pvls (integer ndim, const doublereal *u,
          doublereal *par)
{
  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */

