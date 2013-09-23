#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   ezp :    Complex bifurcation in a boundary value problem */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublecomplex *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublecomplex *f, doublecomplex *dfdu, doublecomplex *dfdp) {
  /* Local variables */
  doublecomplex e, u1, u2, rl;

  u1.r = u[0].r, u1.i = u[0].i;
  u2.r = u[1].r, u2.i = u[1].i;

  rl.r = par[1], rl.i = 0.;

  z_exp(&e, &u1);
  f[0].r = u2.r;
  f[0].i = u2.i;
  f[1].r = -rl.r * e.r + rl.i * e.i;
  f[1].i = -rl.r * e.i - rl.i * e.r;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublecomplex *u, doublereal *par) {
  u[0].r = 0., u[0].i = 0.;
  u[1].r = 0., u[1].i = 0.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublecomplex *u0, const doublecomplex *u1, integer ijac,
          doublecomplex *fb, doublecomplex *dbc) {
  fb[0].r = u0[0].r, fb[0].i = u0[0].i;
  fb[1].r = u1[0].r, fb[1].i = u1[0].i;

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
