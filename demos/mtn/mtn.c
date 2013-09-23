#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   mtn : Homoclinic bifurcations in M. Scheffer's preditor-prey model */
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
  doublereal psif, psiz, psifu2, psizu1, dem;

  dfdp_dim1 = ndim;
  dfdu_dim1 = ndim;

  /* Function Body */
  dem = u[1] * u[1] + par[4] * par[4];
  psiz = u[0] * .4 / (u[0] + .6);
  psif = par[2] * (u[1] * u[1]) / dem;
  psizu1 = (1 / (u[0] + .6) - u[0] / ((u[0] + .6) * (u[0] + .6))) * .4;
  psifu2 = par[2] * 2 * (u[1] / dem - u[1] * (u[1] * u[1]) / (dem * dem));

  f[0] = u[0] * .5 * (1. - u[0] / par[1]) - u[1] * psiz + par[3] * par[1];
  f[1] = psiz * .6 * u[1] - u[1] * .15 - psif;

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = .5 - u[0] / par[1] - u[1] * psizu1;
  ARRAY2D(dfdu,0,1) = -psiz;

  ARRAY2D(dfdu,1,0) = psizu1 * .6 * u[1];
  ARRAY2D(dfdu,1,1) = psiz * .6 - .15 - psifu2;

  if (ijac == 1) {
    return 0;
  }

  ARRAY2D(dfdp,0,1) = par[3];
  ARRAY2D(dfdp,1,1) = 0.;

  ARRAY2D(dfdp,0,2) = 0.;
  ARRAY2D(dfdp,1,2) = -(u[1] * u[1]) / dem;

  ARRAY2D(dfdp,0,3) = par[1];
  ARRAY2D(dfdp,1,3) = 0.;

  ARRAY2D(dfdp,0,4) = 0.;
  ARRAY2D(dfdp,1,4) = par[4] * 2 * par[2] * (u[1] * u[1]) / (dem * dem);

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  /*     ---------------- */

  /* Sets parameter values for homoclinic bifurcation analysis (IPS=9). */


/* ---------------------------------------------------------------------- 
*/
/* Problem parameters (only PAR(1-9) are available to the user) : */
/*     PAR(11) is the trunction interval or `PERIOD' */
  par[1] = 6.;
  /* K */
  par[2] = .06729762;
  /* GF */
  par[3] = .01;
  /* D */
  par[4] = .5;
  /* HZ */
  par[10] = 1046.178;
  /* ---------------------------------------------------------------------- 
*/
/* Since IEQUIB>0 put the equilibrium in PAR(11+i), i=1,...,NDIM : */
/* truncated time interval */
  par[11] = 5.738626;
  par[12] = .5108401;
  /* ---------------------------------------------------------------------- 
   */

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

