#include "auto_f2c.h"
/* Common Block Declarations */

extern struct {
  integer itwist, istart, iequib, nfixed, npsi, nunstab, nstab;
} blhom_1;

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   cir :    Homoclinic Bifurcation in an Electronic Circuit */
/*                (the same equations as in demo tor) */
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
  doublereal r, x, y, z, a3, b3, be, ga, rn;

  dfdp_dim1 = ndim;
  dfdu_dim1 = ndim;

  /* Function Body */
  rn = par[1];
  be = par[2];
  ga = par[3];
  r = par[4];
  a3 = par[5];
  b3 = par[6];

  x = u[0];
  y = u[1];
  z = u[2];

  f[0] = (-(be + rn) * x + be * y - a3 * (x * (x * x)) + b3 * ((y-x) * ((y-x) * (y-x)))) / r;
  f[1] = be * x - (be + ga) * y - z - b3 * ((y-x) * ((y-x) * (y-x)));
  f[2] = y;

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = (-(be + rn) - a3 * 3 * (x * x) - b3 * 3 * ((y-x) * (y-x))) / r;
  ARRAY2D(dfdu,0,1) = (be + b3 * 3 * ((y-x) * (y-x))) / r;
  ARRAY2D(dfdu,0,2) = 0.;

  ARRAY2D(dfdu,1,0) = be + b3 * 3 * ((y-x) * (y-x));
  ARRAY2D(dfdu,1,1) = -(be + ga) - b3 * 3 * ((y-x) * (y-x));
  ARRAY2D(dfdu,1,2) = -1.;

  ARRAY2D(dfdu,2,0) = 0.;
  ARRAY2D(dfdu,2,1) = 1.;
  ARRAY2D(dfdu,2,2) = 0.;

  if (ijac == 1) {
    return 0;
  }
/*      *Parameter derivatives */
  ARRAY2D(dfdp,0,1) = -x / r;
  ARRAY2D(dfdp,1,1) = 0.;
  ARRAY2D(dfdp,2,1) = 0.;

  ARRAY2D(dfdp,0,2) = (-x + y) / r;
  ARRAY2D(dfdp,1,2) = x - y;
  ARRAY2D(dfdp,2,2) = 0.;

  ARRAY2D(dfdp,0,3) = 0.;
  ARRAY2D(dfdp,1,3) = -y;
  ARRAY2D(dfdp,2,3) = 0.;

  ARRAY2D(dfdp,0,4) = -f[0] / r;
  ARRAY2D(dfdp,1,4) = 0.;
  ARRAY2D(dfdp,2,4) = 0.;

  ARRAY2D(dfdp,0,5) = x * (x * x) / r;
  ARRAY2D(dfdp,1,5) = 0.;
  ARRAY2D(dfdp,2,5) = 0.;

  ARRAY2D(dfdp,0,6) = (y-x) * ((y-x) * (y-x)) / r;
  ARRAY2D(dfdp,1,6) = -((y-x) * ((y-x) * (y-x)));
  ARRAY2D(dfdp,2,6) = 0.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  /* ---------------------------------------------------------------------- */
  /* Problem parameters (only PAR(1-9) are available to the user) : */
  
  /* Function Body */
  par[1] = -.721309;
  /* nu */
  par[2] = (doublereal).6;
  /* beta */
  par[3] = (doublereal)0.;
  /* gamma */
  par[4] = (doublereal).6;
  /* r */
  par[5] = (doublereal).328578;
  /* a_3 */
  par[6] = (doublereal).933578;
  
  /* b_3 */
  par[10] = (doublereal)36.13;

  /* ---------------------------------------------------------------------- */
  /* If IEQUIB >0 put initial equilibrium in PAR(11+i), i=1,...,NDIM : */

  /* Truncated time interval */
  par[11] = (doublereal)0.;
  par[12] = (doublereal)0.;
  par[13] = (doublereal)0.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int pvls (integer ndim, const doublereal *u,
          doublereal *par)
{
  /* Local variables */
integer i;

/* Homoclinic bifurcations COMMON block needed here : */

/* If IEQUIB =0 put analytic equilibrium in PAR(11+i), i=1..NDIM */
  if (blhom_1.iequib == 0) {
    for (i = 1; i <= ndim; ++i) {
      par[i + 11] = (doublereal)0.;
    }
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
