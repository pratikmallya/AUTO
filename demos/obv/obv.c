#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   obv :    Optimization in a boundary value problem */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  doublereal e, p;

  p = u[0] + par[2] * (u[0] * u[0]) + par[3] * (u[0] * u[0] * u[0] * u[0]);
  e = exp(p);

  f[0] = u[1];
  f[1] = -par[1] * e;
  f[2] = par[1] * e * (par[2] * 2 * u[0] + 1 + par[3] * 4 * 
		       (u[0] * (u[0] * u[0]))) * 
    u[3] + par[14] * 2 * (u[0] - (doublereal)1.);
  f[3] = -u[2];

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  par[1] = (doublereal).001;
  par[9] = (doublereal)1.;

  u[0] = (doublereal)0.;
  u[1] = (doublereal)0.;
  u[2] = (doublereal)0.;
  u[3] = (doublereal)0.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublereal *u0, const doublereal *u1, integer ijac,
          doublereal *fb, doublereal *dbc)
{
  fb[0] = u0[0];
  fb[1] = u1[0];
  fb[2] = u0[2] - par[12];
  fb[3] = u0[3];
  fb[4] = u1[2] + par[13];
  fb[5] = u1[3];

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int icnd (integer ndim, const doublereal *par, const integer *icp,
          integer nint, const doublereal *u, const doublereal *uold,
          const doublereal *udot, const doublereal *upold, integer ijac,
          doublereal *fi, doublereal *dint)
{
  doublereal e, p;
  p = u[0] + par[2] * (u[0] * u[0]) + par[3] * (u[0] * u[0] * u[0] * u[0]);
  e = exp(p);

  fi[0] = u[2] * u[2] - par[15];
  fi[1] = par[9] - (u[0] - (doublereal)1.) * (u[0] - (doublereal)1.) - 
    (par[1] * par[1] + par[2] * par[2] + par[3] * par[3]) 
    * (doublereal).1;
  fi[2] = -e * u[3] - par[14] * (doublereal).2 * par[1];
  if (nint == 3) {
    return 0;
  }
  fi[3] = -par[1] * e * (u[0] * u[0]) * u[3] - par[14] 
    * (doublereal).2 * par[2] - par[16];
  if (nint == 4) {
    return 0;
  }
  fi[4] = -par[1] * e * (u[0] * u[0] * u[0] * u[0]) * 
    u[3] - par[14] * (doublereal).2 * par[3] - par[17];

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

