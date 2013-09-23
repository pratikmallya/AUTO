#include "auto_f2c.h"

extern struct {
  integer itwist, istart, iequib, nfixed, npsi, nunstab, nstab;
} blhom_1;

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   she : Heteroclinic Orbits In a Model of Shearing Instabilities */
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
  doublereal a01cs, p01cs, p12cs, t02cs, zeta, p11ss;
  integer i, j;
  doublereal q, sigma, pi2, mus;

  dfdp_dim1 = ndim;
  dfdu_dim1 = ndim;

  p11ss = u[0];
  t02cs = u[1];
  p12cs = u[2];
  p01cs = u[3];
  a01cs = u[4];

  mus = par[1];
  q = par[2];
  sigma = par[3];
  zeta = par[4];
  pi2 = 9.8696044036667647;

  f[0] = p11ss * t02cs + p11ss * mus - p12cs * p01cs;
  f[1] = -(p11ss * p11ss + t02cs);
  f[2] = (sigma * (doublereal)4. * p11ss * p01cs + sigma * (doublereal)4. * p12cs * 
	  mus - sigma * (doublereal)9. * p12cs + p11ss * (doublereal)4. * p01cs + 
	  p12cs * (doublereal)4. * mus) / ((sigma + (doublereal)1.) * (doublereal)4.);
  f[3] = (-q * (sigma * sigma) * a01cs - pi2 * (sigma * sigma) * p01cs + pi2 * 
	  (doublereal)3. * sigma * p11ss * p12cs + pi2 * (doublereal)3. * p11ss * 
	  p12cs) / (pi2 * (doublereal)4. * sigma);
  f[4] = zeta * (p01cs - a01cs) / (doublereal)4.;

  if (ijac == 0) {
    return 0;
  }

  for (i = 0; i < 5; ++i) {
    for (j = 0; j < 5; ++j) {
      ARRAY2D(dfdu, i, j) = 0.;
      /* L100: */
    }
  }

  ARRAY2D(dfdu,0,0) = t02cs + mus;
  ARRAY2D(dfdu,0,1) = p11ss;
  ARRAY2D(dfdu,0,2) = -p01cs;
  ARRAY2D(dfdu,0,3) = -p12cs;

  ARRAY2D(dfdu,1,0) = p11ss * (doublereal)-2.;
  ARRAY2D(dfdu,1,1) = (doublereal)-1.;

  ARRAY2D(dfdu,2,0) = p01cs;
  ARRAY2D(dfdu,2,2) = (sigma * (doublereal)4. * mus - sigma * (doublereal)9. + 
		       mus * (doublereal)4.) / ((sigma + (doublereal)1.) * (doublereal)4.);
  ARRAY2D(dfdu,2,3) = p11ss;

  ARRAY2D(dfdu,3,0) = p12cs * (doublereal)3. * (sigma + (doublereal)1.) / (sigma * (doublereal)4.);
  ARRAY2D(dfdu,3,2) = p11ss * (doublereal)3. * (sigma + (doublereal)1.) / (sigma * (doublereal)4.);
  ARRAY2D(dfdu,3,3) = -sigma / (doublereal)4.;
  ARRAY2D(dfdu,3,4) = -q * sigma / (pi2 * (doublereal)4.);

  ARRAY2D(dfdu,4,1) = zeta / (doublereal)4.;
  ARRAY2D(dfdu,4,4) = -zeta / (doublereal)4.;

  if (ijac == 1) {
    return 0;
  }
/* no parameter derivatives are specified with this example */

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  /* ---------------------------------------------------------------------- */
  /* Problem parameters (only PAR(1-9) are available to the user) : */

  par[1] = .163875;
  /* mu */
  par[2] = 0.;
  /* q */
  par[3] = .5;
  /* sigma */
  par[4] = (doublereal).2;

  /* zeta */
  par[10] = (doublereal)85.07;

  /* ---------------------------------------------------------------------- 
*/
/* If IEQUIB =-2 put initial approximations to equilibria in */
/*   PAR(11+i), i=1,...,NDIM :        left-hand equilibrium */
/*   PAR(11+i), i=NDIM+1,...,2*NDIM   right-hand equilibrium */

/* Truncated time interval */
  par[11] = .4048147;
  par[12] = -.163875;
  par[13] = (doublereal)0.;
  par[14] = (doublereal)0.;
  par[15] = (doublereal)0.;

  par[16] = (doublereal)0.;
  par[17] = (doublereal)0.;
  par[18] = (doublereal)0.;
  par[19] = (doublereal)0.;
  par[20] = (doublereal)0.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int pvls (integer ndim, const doublereal *u,
          doublereal *par)
{
  integer i;

  /* Homoclinic bifurcations COMMON block needed here : */

  /* If IEQUIB =-1 put analytic expressions for equilibria in */
  /*   PAR(11+i), i=1,..,NDIM         left-hand equilibrium */
  /*   PAR(11+i), i=NDIM+1,...,2*NDIM right-hand equilibrium */

  if (blhom_1.iequib == -1) {
    par[11] = sqrt(par[1]);
    par[12] = -par[1];
    par[13] = 0.;
    par[14] = 0.;
    par[15] = 0.;
    for (i = ndim; i < ndim * 2; ++i) {
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

