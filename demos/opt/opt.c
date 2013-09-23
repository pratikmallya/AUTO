#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   opt :    A model algebraic optimization problem */
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
  doublereal x1, x2, x3, x4, x5;

  dfdp_dim1 = ndim;
  dfdu_dim1 = ndim;

  x1 = u[0];
  x2 = par[1];
  x3 = par[2];
  x4 = par[3];
  x5 = par[4];

  f[0] = x1 * x1 + x2 * x2 + x3 * x3 + x4 * x4 + x5 * x5 - 1;

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = x1 * 2;

  if (ijac == 1) {
    return 0;
  }
/*      *Parameter derivatives */
  ARRAY2D(dfdp,0,1) = x2 * 2;
  ARRAY2D(dfdp,0,2) = x3 * 2;
  ARRAY2D(dfdp,0,3) = x4 * 2;
  ARRAY2D(dfdp,0,4) = x5 * 2;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  doublereal x1, x2, x3, x4, x5;
  x1 = (doublereal)1.;
  x2 = (doublereal)0.;
  x3 = (doublereal)0.;
  x4 = (doublereal)0.;
  x5 = (doublereal)0.;

  u[0] = x1;

  par[1] = x2;
  par[2] = x3;
  par[3] = x4;
  par[4] = x5;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int fopt (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *fs, doublereal *dfdu, doublereal *dfdp)
{
  doublereal x1, x2, x3, x4, x5;

  x1 = u[0];
  x2 = par[1];
  x3 = par[2];
  x4 = par[3];
  x5 = par[4];

  *fs = x1 + x2 + x3 + x4 + x5;

  if (ijac == 0) {
    return 0;
  }

  dfdu[0] = (doublereal)1.;

  if (ijac == 1) {
    return 0;
  }
/*      *Parameter derivatives */
  dfdp[1] = (doublereal)1.;
  dfdp[2] = (doublereal)1.;
  dfdp[3] = (doublereal)1.;
  dfdp[4] = (doublereal)1.;

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

