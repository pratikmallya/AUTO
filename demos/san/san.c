#include "auto_f2c.h"

extern struct {
  integer itwist, istart, iequib, nfixed, npsi, nunstab, nstab;
} blhom_1;

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   hom : Homoclinic bifurcations in general test example equation */
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

  dfdp_dim1 = ndim;
  dfdu_dim1 = ndim;

  f[0] = par[1] * u[0] + par[2] * u[1] - par[1] * u[0] * u[0] + (par[8] - 
								 par[4] * u[2]) * u[0] * (2. - u[0] * 3.);
  f[1] = par[2] * u[0] + par[1] * u[1] - par[2] * 1.5 * u[0] * u[0] - par[1]
    * 1.5 * u[0] * u[1] - (par[8] - par[4] * u[2]) * 2. * u[1];
  f[2] = par[3] * u[2] + par[7] * u[0] + par[6] * u[0] * u[2] + par[4] * 
    par[5] * (u[0] * u[0] * (1. - u[0]) - u[1] * u[1]);

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = par[1] - par[1] * 2. * u[0] + (par[8] - par[4] * u[2]) * (2. - u[0] * 6.);
  ARRAY2D(dfdu,0,1) = par[2];
  ARRAY2D(dfdu,0,2) = -par[4] * u[0] * (2. - u[0] * 3.);

  ARRAY2D(dfdu,1,0) = par[2] - par[2] * 3. * u[0] - par[1] * 1.5 * u[1];
  ARRAY2D(dfdu,1,1) = par[1] - par[1] * 1.5 * u[0] - (par[8] - par[4] * u[2]) * 2.;
  ARRAY2D(dfdu,1,2) = par[4] * 2. * u[1];

  ARRAY2D(dfdu,2,0) = par[7] + par[6] * u[2] + par[4] * par[5] * u[0] * (2. - u[0] * 3.);
  ARRAY2D(dfdu,2,1) = par[4] * -2. * par[5] * u[1];
  ARRAY2D(dfdu,2,2) = par[3] + par[6] * u[0];

  if (ijac == 1) {
    return 0;
  }
/* No parameter derivatives are specified with this example */

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  doublereal s;

  /* Sets parameter values for homoclinic bifurcation analysis (IPS=9). */

  /* COMMON block needed if IPS=9 (homoclinic bifurcations) : */

  /* ---------------------------------------------------------------------- 
   */
  /* Problem parameters (only PAR(1-9) are available to the user) : */

  par[1] = 0.;
  /* a */
  par[2] = 1.;
  /* b */
  par[3] = -2.;
  /* c */
  par[4] = 0.;
  /* alpha */
  par[5] = 1.;
  /* beta */
  par[6] = 0.;
  /* gamma */
  par[7] = 0.;
  /* mu */
  par[8] = 0.;

  /* tilde mu */
  par[10] = 20.;
  /* ---------------------------------------------------------------------- 
   */
  /* If IEQUIB=1 then put initial equilibrium in PAR(11+i), i=1,...,NDIM : 
   */

  /* truncated time interval */
  if (blhom_1.iequib != 0) {
    par[11] = (doublereal)0.;
    par[12] = (doublereal)0.;
    par[13] = (doublereal)0.;
  }
/* ---------------------------------------------------------------------- 
   */
  /* IF ISTART=2 then put analytic homoclinic orbit here with T in the */
  /*   interval [0,1] */

  /* test example (a=0,b=1) */

  s = (t - (doublereal).5) * par[10];
  u[0] = 1. - ((1. - exp(s)) / (exp(s) + 1.)) * ((1. - exp(s)) / (exp(s) + 1.));
  u[1] = exp(s) * 4. * (1. - exp(s)) / ((exp(s) + 1.) * ((exp(s) + 1.) * (exp(s) + 1.)));
  u[2] = 0.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int pvls (integer ndim, const doublereal *u,
          doublereal *par)
{
  integer i;

  /*     ---------- ---- */

  /* Homoclinic bifurcations COMMON block needed here : */

  /* If IEQUIB=0 put analytic equilibrium in PAR(11+i), i=1,...,NDIM : */

  for (i = 0; i < ndim; ++i) {
    par[i + 11] = 0.;
  }

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

