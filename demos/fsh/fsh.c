#include "auto_f2c.h"
/* Common Block Declarations */

struct {
  integer ifrst;
} frst_;

#define frst_1 frst_

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   fsh :     Heteroclinic orbits : a saddle-node copnnection */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* Parameter assignment: */

/*           PAR(1)           :                   (unused) */
/*           PAR(2)           : c                 (wave speed) */
/*           PAR(4)           : eps-1        1    (radius) */
/*           PAR(11)          : period */
/*           PAR(12)          : mu-1              (eigenvalue  at 1) */
/*           PAR(13) , PAR(14): v(1)    , v(2)    (eigenvector at 1) */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  integer i;
  doublereal dummy, period;

  ffff(2, u, icp, par, ijac, f, &dummy);
  period = par[10];
  for (i = 0; i < ndim; ++i) {
    f[i] = period * f[i];
  }

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int ffff (integer ndm, const doublereal *u, const integer *icp, const doublereal *par, integer ijac, doublereal *f, doublereal *dfdu)
{
  /* System generated locals */
integer dfdu_dim1;

  dfdu_dim1 = ndm;

  f[0] = u[1];
  f[1] = par[2] * u[1] - u[0] * (1 - u[0]);

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = 0.;
  ARRAY2D(dfdu,0,1) = 1.;

  ARRAY2D(dfdu,1,0) = u[0] * 2 - 1;
  ARRAY2D(dfdu,1,1) = par[2];

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  /* Local variables */
  doublereal c, d, v11, v12, period, ep1, rmu1;
  if (frst_1.ifrst != 1) {
    frst_1.ifrst = 1;
    /*       Set the starting period, wave speed, and radius */
    period = (doublereal).01;
    c = (doublereal)11.;
    ep1 = (doublereal).001;
    d = sqrt(c * c + 4);
    par[2] = c;
    par[4] = ep1;
    par[10] = period;
    par[11] = (c - d) / 2;
    par[12] = (doublereal)1. / sqrt(par[11] * par[11] + 1);
    par[13] = par[11] / sqrt(par[11] * par[11] + 1);
  }

  c = par[2];
  ep1 = par[4];
  period = par[10];
  d = sqrt(c * c + 4);
  rmu1 = (c - d) / 2;
  v11 = (doublereal)1. / sqrt(rmu1 * rmu1 + 1);
  v12 = rmu1 / sqrt(rmu1 * rmu1 + 1);

  u[0] = 1 - ep1 * v11;
  u[1] = -ep1 * v12;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublereal *u0, const doublereal *u1, integer ijac,
          doublereal *fb, doublereal *dbc)
{
  doublereal dgdu1[4], g1[2], v1[2];

  v1[0] = u1[0] + par[4] * par[12];
  v1[1] = u1[1] + par[4] * par[13];

  ffff(2, v1, icp, par, 1, g1, dgdu1);

  fb[0] = dgdu1[0] * par[12] + dgdu1[2] * par[13] - par[11] * par[12];
  fb[1] = dgdu1[1] * par[12] + dgdu1[3] * par[13] - par[11] * par[13];
  fb[2] = par[12] * par[12] + par[13] * par[13] - 1;
  fb[3] = g1[0];
  fb[4] = g1[1];

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int icnd (integer ndim, const doublereal *par, const integer *icp,
          integer nint, const doublereal *u, const doublereal *uold,
          const doublereal *udot, const doublereal *upold, integer ijac,
          doublereal *fi, doublereal *dint)
{
  doublereal dfdu[4], f[2], f0[2], dummy;

  ffff(2, u, icp, par, 1, f, dfdu);
  ffff(2, uold, icp, par, 0, f0, &dummy);

  fi[0] = (f[0] - f0[0]) * (dfdu[0] * f[0] + dfdu[2] * f[1]) + 
    (f[1] - f0[1]) * (dfdu[1] * f[0] + dfdu[3] * f[1]);

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
