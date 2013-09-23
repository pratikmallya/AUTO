#include "auto_f2c.h"
/* Common Block Declarations */

extern struct {
  integer itwist, istart, iequib, nfixed, npsi, nunstab, nstab;
} blhom_1;

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   kpr : Homoclinic bifurcations in Koper's extended Van der Pol model */
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
  f[0] = par[3] * (par[2] * u[1] - u[0] * 
		   (u[0] * u[0]) + u[0] * (doublereal)3. - par[1]);
  f[1] = u[0] - u[1] * 2 + u[2];
  f[2] = u[1] - u[2];

  if (ijac == 0) {
    return 0;
  }

  ARRAY2D(dfdu,0,0) = par[3] * (u[0] * u[0] * (doublereal)-3. 
				+ (doublereal)3.);
  ARRAY2D(dfdu,0,1) = par[3] * par[2];
  ARRAY2D(dfdu,0,2) = (doublereal)0.;

  ARRAY2D(dfdu,1,0) = (doublereal)1.;
  ARRAY2D(dfdu,1,1) = (doublereal)-2.;
  ARRAY2D(dfdu,1,2) = (doublereal)1.;

  ARRAY2D(dfdu,2,0) = (doublereal)0.;
  ARRAY2D(dfdu,2,1) = (doublereal)1.;
  ARRAY2D(dfdu,2,2) = (doublereal)-1.;

  if (ijac == 1) {
    return 0;
  }

  ARRAY2D(dfdp,0,1) = -par[3];
  ARRAY2D(dfdp,1,1) = 0.;
  ARRAY2D(dfdp,2,1) = 0.;

  ARRAY2D(dfdp,0,2) = par[3] * u[1];
  ARRAY2D(dfdp,1,2) = 0.;
  ARRAY2D(dfdp,2,2) = 0.;

  ARRAY2D(dfdp,0,3) = par[2] * u[1] - u[0] * 
    (u[0] * u[0]) + u[0] * (doublereal)3. - par[1];
  ARRAY2D(dfdp,1,3) = 0.;
  ARRAY2D(dfdp,2,3) = 0.;
  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  /* Sets parameter values for homoclinic bifurcation analysis (IPS=9). */

  /* COMMON block needed if IPS=9 (homoclinic bifurcations) : */

  par[1] = (doublereal)-1.851185124;
  /* lambda */
  par[2] = -.15;
  /* kappa */
  par[3] = 10.;

  /* 1/epsilon_1 */
  par[10] = (doublereal).1;
  /* ---------------------------------------------------------------------- 
*/
/* If IEQUIB=1 then put the equilibrium in PAR(11+i), i=1,...,NDIM : */

/* truncated time interval */
  if (blhom_1.iequib != 0) {
    par[11] = (doublereal)-.9591016;
    par[12] = (doublereal)-.9591016;
    par[13] = (doublereal)-.9591016;
  }
/* ---------------------------------------------------------------------- 
*/
/* Distance along the unstable manifold : */

  if (blhom_1.istart == 3) {
    par[ndim * blhom_1.iequib + 11] = (doublereal)-1e-5;
  }
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

