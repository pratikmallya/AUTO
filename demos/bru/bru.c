#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   bru :    Time integration of a scalar nonlinear parabolic PDE */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  /* Local variables */
  doublereal a, b, x, y;

  x = u[0];
  y = u[1];
  a = par[1];
  b = par[2];

/*      *Set the nonlinear term */
  f[0] = x * x * y - (b + 1) * x + a;
  f[1] = -(x * x) * y + b * x;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{

  /* Local variables */
  doublereal a, b, pi, dx, dy, rl;

  pi = atan(1.) * 4;

  /*      *Set the (constant) parameters */
  a = (doublereal)2.;
  b = (doublereal)5.45;
  dx = (doublereal).008;
  dy = (doublereal).004;
  rl = (doublereal).75;

  par[1] = a;
  par[2] = b;
  par[3] = rl;

  /*      *Set the actual width of the space interval [0,PAR(11)] */
  par[10] = (doublereal)1.;

  /*      *Set the initial data in the (scaled) interval [0,1] */
  u[0] = a - sin(pi * t) * (doublereal).5;
  u[1] = b / a + sin(pi * t) * (doublereal).7;

  /*      *Also set the space-derivative of the initial data */
  /*      *Note the scaling by PAR(11) */
  u[2] = pi * (doublereal)-.5 * cos(pi * t) / par[10];
  u[3] = pi * (doublereal).7 * cos(pi * t) / par[10];

  /*      *Set the diffusion constants */
  par[14] = dx / (rl * rl);
  par[15] = dy / (rl * rl);

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublereal *u0, const doublereal *u1, integer ijac,
          doublereal *fb, doublereal *dbc)
{
  /*      *Define the boundary conditions (Dirichlet, in this example). */

  fb[0] = u0[0] - par[1];
  fb[1] = u0[1] - par[2] / par[1];
  fb[2] = u1[0] - par[1];
  fb[3] = u1[1] - par[2] / par[1];

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
