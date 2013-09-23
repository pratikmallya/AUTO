#include "auto_f2c.h"
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/*   frc :      A periodically forced system */
/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  /* Local variables */
  doublereal a, b, d, r, v, w, x, y, ss, bet, eps;
  a = par[1];
  b = par[2];
  r = par[3];
  eps = par[4];
  bet = par[5];
  d = par[6];

  v = u[0];
  w = u[1];
  x = u[2];
  y = u[3];

  ss = x * x + y * y;

  f[0] = (v * (v - a) * (1 - v) - w) / eps;
  f[1] = v - d * w - (b + r * x);
  f[2] = x + bet * y - x * ss;
  f[3] = -bet * x + y - y * ss;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{

  /* Local variables */
  doublereal a, b, d, r, bet, eps, tpi;

  a = (doublereal).5;
  b = a;
  r = (doublereal)0.;
  eps = (doublereal).005;
  bet = 100.;
  d = (doublereal)1.;

  par[1] = a;
  par[2] = b;
  par[3] = r;
  par[4] = eps;
  par[5] = bet;
  par[6] = d;
  tpi = atan(1.) * 8;
  par[10] = tpi / bet;

  u[0] = b;
  u[1] = b * (b - a) * (1 - b);
  u[2] = sin(tpi * t);
  u[3] = cos(tpi * t);

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

