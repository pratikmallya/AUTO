#include "auto_f2c.h"
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*  pen :    Coupled pendula (or rotations in coupled Josephson junctions)*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  doublereal gamma, ri, ph1, ph2, ps1, ps2, eps;
  gamma = par[1];
  eps = par[2];
  ri = par[3];

  ph1 = u[0];
  ph2 = u[1];
  ps1 = u[2];
  ps2 = u[3];

  f[0] = ps1;
  f[1] = ps2;
  f[2] = -eps * ps1 - sin(ph1) + ri + gamma * (ph2 - ph1);
  f[3] = -eps * ps2 - sin(ph2) + ri + gamma * (ph1 - ph2);

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  doublereal gamma, ri, eps;

  gamma = (doublereal).175;
  eps = (doublereal).1;
  ri = (doublereal).4;
  par[1] = gamma;
  par[2] = eps;
  par[3] = ri;

  /*Set the actual period (since the data in pen.dat have scaled time variab
    le)*/
  par[10] = (doublereal)1.5738797205;

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

