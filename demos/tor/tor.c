#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   tor :    Torus Bifurcation in an Electronic Oscillator */
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
  doublereal r, x, y, z, a3, b3, be, ga, rn;

  dfdp_dim1 = ndim;
  dfdu_dim1 = ndim;

  rn = par[1];
  be = par[2];
  ga = par[3];
  r = par[4];
  a3 = par[5];
  b3 = par[6];

  x = u[0];
  y = u[1];
  z = u[2];

  f[0] = (-(be + rn) * x + be * y - a3 * (x * (x * x)) + b3 * 
	  ((y-x) * ((y-x) * (y-x)))) / r;
  f[1] = be * x - (be + ga) * y - z - b3 * ((y-x) * ((y-x) * (y-x)));
  f[2] = y;

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = (-(be + rn) - a3 * 3 * (x * x) - b3 * 3 * 
		       ((y-x) * (y-x))) / r;
  ARRAY2D(dfdu,0,1) = (be + b3 * 3 * ((y-x) * (y-x))) / r;
  ARRAY2D(dfdu,0,2) = 0.;

  ARRAY2D(dfdu,1,0) = be + b3 * 3 * ((y-x) * (y-x));
  ARRAY2D(dfdu,1,1) = -(be + ga) - b3 * 3 * ((y-x) * (y-x));
  ARRAY2D(dfdu,1,2) = -1.;

  ARRAY2D(dfdu,2,0) = 0.;
  ARRAY2D(dfdu,2,1) = 1.;
  ARRAY2D(dfdu,2,2) = 0.;

  if (ijac == 1) {
    return 0;
  }
/*      *Parameter derivatives */
  ARRAY2D(dfdp,0,1) = -x / r;
  ARRAY2D(dfdp,1,1) = 0.;
  ARRAY2D(dfdp,2,1) = 0.;

  ARRAY2D(dfdp,0,2) = (-x + y) / r;
  ARRAY2D(dfdp,1,2) = x - y;
  ARRAY2D(dfdp,2,2) = 0.;

  ARRAY2D(dfdp,0,3) = 0.;
  ARRAY2D(dfdp,1,3) = -y;
  ARRAY2D(dfdp,2,3) = 0.;

  ARRAY2D(dfdp,0,4) = -f[0] / r;
  ARRAY2D(dfdp,1,4) = 0.;
  ARRAY2D(dfdp,2,4) = 0.;

  ARRAY2D(dfdp,0,5) = x * (x * x) / r;
  ARRAY2D(dfdp,1,5) = 0.;
  ARRAY2D(dfdp,2,5) = 0.;

  ARRAY2D(dfdp,0,6) = (y-x) * ((y-x) * (y-x)) / r;
  ARRAY2D(dfdp,1,6) = -((y-x) * ((y-x) * (y-x)));
  ARRAY2D(dfdp,2,6) = 0.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  par[1] = (doublereal)-.9;
  par[2] = (doublereal).5;
  par[3] = (doublereal)-.6;
  par[4] = (doublereal).6;
  par[5] = (doublereal).328578;
  par[6] = (doublereal).933578;

  u[0] = (doublereal)0.;
  u[1] = (doublereal)0.;
  u[2] = (doublereal)0.;

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

