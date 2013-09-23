#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*                   chu :     Chua's circuit */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  /* System generated locals */
  doublereal d1, d2;

    /* Local variables */
  doublereal beta, alpha, x, y, z, a0, a1, pi, rk;

  pi = atan(1.) * 4;
  alpha = par[1];
  beta = par[2];
  rk = par[3];
  a0 = par[4];
  a1 = par[5];

  x = u[0];
  y = u[1];
  z = u[2];

  d1 = x + 1;
  d2 = x - 1;
  f[0] = alpha * (y - (a1 * x + (a0 - a1) * (doublereal).5 *
		       (d1 * 2 * atan(rk * d1) / pi - d2 * 2 * atan(rk * d2) / pi)));
  f[1] = x - y + z;
  f[2] = -beta * y;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  par[1] = -1.;
  par[2] = (doublereal)14.3;
  par[3] = (doublereal)10.;
  par[4] = (doublereal)-.14285714285714285;
  par[5] = (doublereal).2857142857142857;

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

