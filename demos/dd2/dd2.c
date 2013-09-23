#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   dd2 :    Basic computations for discrete dynamical systems */
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

  dfdp_dim1 = ndim;
  dfdu_dim1 = ndim;

  f[0] = par[1] * u[0] * (1 - u[0]) - par[2] * u[0] * u[1];
  f[1] = (1 - par[3]) * u[1] + par[2] * u[0] * u[1];

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = par[1] * (1 - u[0] * 2) - par[2] * u[1];
  ARRAY2D(dfdu,0,1) = -par[2] * u[0];
  ARRAY2D(dfdu,1,0) = par[2] * u[1];
  ARRAY2D(dfdu,1,1) = 1 - par[3] + par[2] * u[0];

  if (ijac == 1) {
    return 0;
  }

  ARRAY2D(dfdp,0,1) = u[0] * (1 - u[0]);
  ARRAY2D(dfdp,1,1) = (doublereal)0.;
  ARRAY2D(dfdp,0,2) = -u[0] * u[1];
  ARRAY2D(dfdp,1,2) = u[0] * u[1];

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  par[1] = (doublereal)0.;
  par[2] = (doublereal).2;
  par[3] = (doublereal).1;

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

