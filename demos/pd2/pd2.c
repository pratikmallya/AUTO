#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   pd1 :    Time integration of a scalar nonlinear parabolic PDE */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  /*      *Set the nonlinear term */
  f[0] = par[1] * u[0] * ((doublereal)1. - u[0]) - u[0] * u[1];
  f[1] = -u[1] + u[0] * u[1];

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  doublereal pi;
  pi = atan(1.) * 4;

  /*      *Set the (constant) parameter */
  par[1] = (doublereal)12.;

  /*      *Set the actual width of the space interval [0,PAR(11)] */
  par[10] = (doublereal)1.;

  /*      *Set the initial data in the (scaled) interval [0,1] */
  u[0] = sin(pi * t);
  u[1] = (doublereal)1.;

  /*      *Also set the space-derivative of the initial data */
  /*      *Note the scaling by 1/PAR(11) ! */
  u[2] = pi * cos(pi * t) / par[10];
  u[3] = (doublereal)0. / par[10];

  /*      *Set the diffusion constants */
  par[14] = (doublereal)1.;
  par[15] = (doublereal)1.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublereal *u0, const doublereal *u1, integer ijac,
          doublereal *fb, doublereal *dbc)
{
  /*      *Define the boundary conditions. */

  fb[0] = u0[0];
  fb[1] = u0[1] - (doublereal)1.;
  fb[2] = u1[0];
  fb[3] = u1[1] - (doublereal)1.;

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
