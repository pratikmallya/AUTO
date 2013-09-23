#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   kar :       The Von Karman swirling flow */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp) {
  doublereal zinf, gamma, u1, u2, u3, u4, u5;
  u1 = u[0];
  u2 = u[1];
  u3 = u[2];
  u4 = u[3];
  u5 = u[4];

  gamma = par[1];
  zinf = par[3];

  f[0] = zinf * u2;
  f[1] = zinf * u3;
  f[2] = zinf * (gamma * -2 * u4 + u2 * u2 - u1 * 2 * u3 - u4 * u4);
  f[3] = zinf * u5;
  f[4] = zinf * (gamma * 2 * u2 + u2 * 2 * u4 - u1 * 2 * u5);

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  doublereal finf, zinf, gamma;
  gamma = (doublereal)1.;
  finf = (doublereal)0.;
  zinf = (doublereal)500.;

  par[1] = gamma;
  par[2] = -finf;
  par[3] = zinf;

  u[0] = (doublereal)0.;
  u[1] = (doublereal)0.;
  u[2] = (doublereal)0.;
  u[3] = (doublereal)0.;
  u[4] = (doublereal)0.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublereal *u0, const doublereal *u1, integer ijac,
          doublereal *fb, doublereal *dbc) {
  doublereal finf, a, b, c, gamma;

  gamma = par[1];
  finf = -par[2];

  c = sqrt(finf * finf * finf * finf + gamma * gamma * 4);
  a = sqrt(c + finf * finf) / sqrt(2.);
  b = sqrt(c - finf * finf) / sqrt(2.);

  fb[0] = u0[0];
  fb[1] = u0[1];
  fb[2] = u0[3] - 1 + gamma;
  fb[3] = (finf + a) * u1[1] + u1[2] - gamma * u1[3] / a;
  fb[4] = a * (b * b) * u1[1] / gamma + (finf + a) * u1[3] + u1[4];
  fb[5] = u1[0] - finf;

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
