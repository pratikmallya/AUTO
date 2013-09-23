#include "auto_f2c.h"
#include "math.h"
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   abc :            The A --> B --> C reaction */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  doublereal beta, b, d, e, s, alpha, x1, x2, x3, x1c;
  
  x1 = u[0];
  x2 = u[1];
  x3 = u[2];
  
  d = par[1];
  alpha = par[2];
  beta = par[3];
  b = par[4];
  s = par[5];
  
  e = exp(x3);
  x1c = 1 - x1;
  
  f[0] = -x1 + d * x1c * e;
  f[1] = -x2 + d * e * (x1c - s * x2);
  f[2] = -x3 - beta * x3 + d * b * e * (x1c + alpha * s * x2);
  
  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  par[1] = (doublereal)0.;
  par[2] = (doublereal)1.;
  par[3] = (doublereal)1.55;
  par[4] = (doublereal)8.;
  par[5] = (doublereal).04;
  
  u[0] = (doublereal)0.;
  u[1] = (doublereal)0.;
  u[2] = (doublereal)0.;
  
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
