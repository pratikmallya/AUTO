#include "auto_f2c.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   tim :    A test problem for timing AUTO */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
doublereal lexp(const doublereal *u)
{
  /* System generated locals */
  integer i1;
  doublereal ret_val;

  /* Local variables */
  integer k, nterms;
  doublereal trm;

  nterms = 25;
  ret_val = 1.;
  trm = ret_val;
  for (k = 0; k < nterms; ++k) {
    trm = trm * *u / (k + 1);
    ret_val += trm;
  }

  return ret_val;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp) {
  /* Local variables */
  doublereal e;
  integer i, i1, i2;

  for (i = 0; i < ndim / 2; ++i) {
    i1 = (i * 2);
    i2 = i1 + 1;
    e = lexp(&u[i1]);
    f[i1] = u[i2];
    f[i2] = -par[1] * e;
    /* L1: */
  }

  return 0;
} 
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par) {
  integer i;

  for (i = 0; i < ndim; ++i) {
    u[i] = (doublereal)0.;
  }

  return 0;
} 
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int bcnd (integer ndim, const doublereal *par, const integer *icp,
          integer nbc, const doublereal *u0, const doublereal *u1, integer ijac,
          doublereal *fb, doublereal *dbc) {
  integer i, i1, i2;

  for (i = 0; i < ndim / 2; ++i) {
    i1 = (i * 2);
    i2 = i1 + 1;
    fb[i1] = u0[i1];
    fb[i2] = u1[i1];
  }

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
