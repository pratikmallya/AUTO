#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   pvl :  Setting functional parameter values (for Bratu's equation) */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  doublereal e;
  e = exp(u[0]);
  f[0] = u[1];
  f[1] = -par[1] * e;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  par[1] = 0.;
  u[0] = (doublereal)0.;
  u[1] = (doublereal)0.;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublereal *u0, const doublereal *u1, integer ijac,
          doublereal *fb, doublereal *dbc)
{
  fb[0] = u0[0];
  fb[1] = u1[0];

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int pvls (integer ndim, const doublereal *u,
          doublereal *par)
{
  integer tmp;
  extern doublereal getp();

  /* ---------------------------------------------------------------------- 
   */
  /* NOTE : */
  /* Parameters set in this subroutine should be considered as ``solution */
  /* measures'' and be used for output purposes only. */

  /* They should never be used as `true'' continuation parameters. */

  /* They may, however, be added as ``over-specified parameters'' in the */
  /* parameter list associated with the AUTO-Constant NICP, in order to */
  /* print their values on the screen and in the ``p.xxx file. */

  /* They may also appear in the list associated with AUTO-constant NUZR. */

  /* ---------------------------------------------------------------------- 
   */
  /* For algebraic problems the argument U is, as usual, the state vector. 
   */
  /* For differential equations the argument U represents the approximate */
  /* solution on the entire interval [0,1]. In this case its values must */
  /* be accessed indirectly by calls to GETP, as illustrated below. */
  /* ---------------------------------------------------------------------- 
   */

  /* Set PAR(2) equal to the L2-norm of U(1) */
  par[2] = getp("NRM", 1, u);

  /* Set PAR(3) equal to the minimum of U(2) */
  par[3] = getp("MIN", 2, u);

  /* Set PAR(4) equal to the value of U(2) at the left boundary. */
  par[4] = getp("BV0", 2, u);

  /* ---------------------------------------------------------------------- 
   */
  /* The first argument of GETP may be one of the following: */
  /*        'NRM' (L2-norm),     'MAX' (maximum), */
  /*        'INT' (integral),    'BV0 (left boundary value), */
  /*        'MIN' (minimum),     'BV1' (right boundary value). */

  /* Also available are */
  /*   'STP' (Pseudo-arclength step size used). */
  /*   'FLD' (`Fold function', which vanishes at folds). */
  /*   'BIF' (`Bifurcation function', which vanishes at singular points). */
  /*   'HBF' (`Hopf function'; which vanishes at Hopf points). */
  /*   'SPB' ( Function which vanishes at secondary periodic bifurcations). 
   */
  /* ---------------------------------------------------------------------- 
   */

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
