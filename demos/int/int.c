#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   int :    An ODE with boundary and integral constraints */
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
  doublereal e;

  dfdp_dim1 = ndim;
  dfdu_dim1 = ndim;

  e = exp(u[0]);
  f[0] = u[1];
  f[1] = -par[1] * e;

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = (doublereal)0.;
  ARRAY2D(dfdu,0,1) = 1.;
  ARRAY2D(dfdu,1,0) = -par[1] * e;
  ARRAY2D(dfdu,1,1) = (doublereal)0.;

  if (ijac == 1) {
    return 0;
  }
/*      *Parameter derivatives */
  ARRAY2D(dfdp,0,1) = (doublereal)0.;
  ARRAY2D(dfdp,1,1) = -e;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  par[1] = 0.;
  par[2] = 0.;
  par[3] = 0.;

  u[0] = (doublereal)0.;
  u[1] = (doublereal)0.;

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
  dbc_dim1 = nbc;

  fb[0] = u0[0] - u1[0] - par[2];

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dbc,0,0) = (doublereal)1.;
  ARRAY2D(dbc,0,1) = (doublereal)0.;

  ARRAY2D(dbc,0,2) = (doublereal)-1.;
  ARRAY2D(dbc,0,3) = (doublereal)0.;

  if (ijac == 1) {
    return 0;
  }
/*      *Parameter derivatives */
  ARRAY2D(dbc,0,5) = (doublereal)0.;
  ARRAY2D(dbc,0,6) = (doublereal)-1.;
  ARRAY2D(dbc,0,7) = (doublereal)0.;

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

  dint_dim1 = nint;

  fi[0] = u[0] - par[3];

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dint,0,0) = (doublereal)1.;
  ARRAY2D(dint,0,1) = (doublereal)0.;

  if (ijac == 1) {
    return 0;
  }
/*      *Parameter derivatives */
  ARRAY2D(dint,0,3) = (doublereal)0.;
  ARRAY2D(dint,0,4) = (doublereal)0.;
  ARRAY2D(dint,0,5) = (doublereal)-1.;

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
