#include "auto_f2c.h"

struct {
  doublereal **d0, **d2, **di, **dd,
    **ri, u0[2], u1[2], f0[2], f1[2], v[10];
} blppde_;

#define blppde_1 blppde_

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*     brf  :  A parabolic PDE (the Brusselator) */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*     (Discretized in space by fourth order finite differences) */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* NOTE: The values of the constants NE and NX are defined in the file */
/*       brf.inc. If they are changed then the equations-file brf.f must */
/*       be rewritten with an editor or with the GUI Write button. */

/*      NE  :  the dimension of the PDE system */
/*      NX  :  the number of space intervals for the discretization */

/* The AUTO-constant NDIM must be set equal to the value of NE*(NX-1) */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int ff (integer ne, doublereal *u, const doublereal *par, doublereal *f)
{
  /* Local variables */
  doublereal a, b, x, y;

/*     ---------- -- */
/*     Define the nonlinear term */

  x = u[0];
  y = u[1];
  a = par[1];
  b = par[2];

  f[0] = x * x * y - (b + 1) * x + a;
  f[1] = -(x * x) * y + b * x;

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int setdc (integer ne, doublereal *dc, const doublereal *par)
{
  /*     ---------- ----- */
  /*     Set the diffusion constants (constant, or in terms of PAR) */

  dc[0] = par[3] / (par[5] * par[5]);
  dc[1] = par[4] / (par[5] * par[5]);

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int setbc (integer ne, const doublereal *par, doublereal *u0, doublereal *u1)
{
  doublereal a, b;

  /*     ---------- ----- */
  /* Set the boundary values (to be kept fixed in time) */
  a = par[1];
  b = par[2];

  u0[0] = a;
  u0[1] = b / a;
  u1[0] = a;
  u1[1] = b / a;


  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int stpnt (integer ndim, doublereal t,
           doublereal *u, doublereal *par)
{
  doublereal a, b;
  integer i;
  doublereal dx, dy, rl;

  /*     ---------- ----- */
  /* Define the starting stationary solution on the spatial mesh */

  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /*     brf  :  A parabolic PDE (the Brusselator) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /*     (Discretized in space by fourth order finite differences) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* NOTE: The values of the constants NE and NX are defined above. */
  /*       If they are changed then the equations-file brf.f must */
  /*       be rewritten with an editor or with the GUI Write button. */

  /*      NE  :  the dimension of the PDE system */
  /*      NX  :  the number of space intervals for the discretization */

  /* The AUTO-constant NDIM must be set equal to the value of NE*(NX-1) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */

  /* Set the parameter values */
  /* Function Body */
  a = 2.;
  b = 5.45;
  dx = .008;
  dy = .004;
  rl = (doublereal).4;

  par[1] = a;
  par[2] = b;
  par[3] = dx;
  par[4] = dy;
  par[5] = rl;

  /* Set the starting solution at space-points i/NX, i=1,2,...,NX-1 */
  for (i = 0; i < 5; ++i) {
    u[i] = a;
    u[i + 5] = b / a;
    /* L1: */
  }

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*                Problem-independent subroutines */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int func (integer ndim, const doublereal *u, const integer *icp,
          const doublereal *par, integer ijac,
          doublereal *f, doublereal *dfdu, doublereal *dfdp)
{
  integer i, j, k;
  doublereal w[2];
  doublereal dc[2];
  doublereal fw[2];
  static integer ifrst = 0;

  /*     ---------- ---- */

  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /*     brf  :  A parabolic PDE (the Brusselator) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /*     (Discretized in space by fourth order finite differences) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* NOTE: The values of the constants NE and NX are defined above. */
  /*       If they are changed then the equations-file brf.f must */
  /*       be rewritten with an editor or with the GUI Write button. */

  /*      NE  :  the dimension of the PDE system */
  /*      NX  :  the number of space intervals for the discretization */

  /* The AUTO-constant NDIM must be set equal to the value of NE*(NX-1) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */

  /* Problem-independent initialization : */
  if (ifrst != 1234) {
    gencf(par);
    ifrst = 1234;
  }

  setdc(2, dc, par);
  setbc(2, par, blppde_1.u0, blppde_1.u1);
  ff(2, blppde_1.u0, par, blppde_1.f0);
  ff(2, blppde_1.u1, par, blppde_1.f1);

  for (i = 0; i < 5; ++i) {
    for (j = 0; j < 2; ++j) {
      blppde_1.v[i + j * 5] = blppde_1.di[0][i] * (dc[j] * 
						    36 * blppde_1.u0[j] + blppde_1.f0[j] / 12) + 
	blppde_1.di[4][i] * (dc[j] * 36 * blppde_1.u1[j] + 
				 blppde_1.f1[j] / 12);
      /* L1: */
    }
/* L2: */
  }

  for (i = 0; i < 5; ++i) {
    for (k = 0; k < 2; ++k) {
      w[k] = u[i + k * 5];
      /* L3: */
    }
    ff(2, w, par, fw);
    for (j = 0; j < 2; ++j) {
      f[i + j * 5] = blppde_1.v[i + j * 5] + fw[j];
      for (k = 0; k < 5; ++k) {
	f[i + j * 5] += dc[j] * blppde_1.dd[i][k] * 
	  u[k + j * 5];
	/* L4: */
      }
/* L5: */
    }
/* L6: */
  }

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int gencf (doublereal *par)
{
  integer i, j, k;
  doublereal s;
  integer ic[5];
  extern int ge(integer n, integer m1a, doublereal *a, integer nrhs, integer ndxloc, doublereal *u, integer m1f, doublereal *f, doublereal *det);
  extern double **dmatrix(integer, integer);
  integer ir[5];
  doublereal det;

  /*     ---------- ----- */

  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /*     brf  :  A parabolic PDE (the Brusselator) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /*     (Discretized in space by fourth order finite differences) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* NOTE: The values of the constants NE and NX are defined above. */
  /*       If they are changed then the equations-file brf.f must */
  /*       be rewritten with an editor or with the GUI Write button. */

  /*      NE  :  the dimension of the PDE system */
  /*      NX  :  the number of space intervals for the discretization */

  /* The AUTO-constant NDIM must be set equal to the value of NE*(NX-1) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */

  /* Function Body */
  blppde_1.d0 = dmatrix(5, 5);
  blppde_1.d2 = dmatrix(5, 5);
  blppde_1.di = dmatrix(5, 5);
  blppde_1.dd = dmatrix(5, 5);
  blppde_1.ri = dmatrix(5, 5);
  for (i = 0; i < 5; ++i) {
    for (j = 0; j < 5; ++j) {
      blppde_1.d0[i][j] = 0.;
      blppde_1.d2[i][j] = 0.;
      blppde_1.di[i][j] = 0.;
      blppde_1.dd[i][j] = 0.;
      blppde_1.ri[i][j] = 0.;
      /* L1: */
    }
    blppde_1.d0[i][i] = .83333333333333337;
    blppde_1.d2[i][i] = -72.;
    blppde_1.ri[i][i] = 1.;
    /* L2: */
  }

  for (i = 0; i < 4; ++i) {
    blppde_1.d0[i + 1][i] = .083333333333333329;
    blppde_1.d0[i][i + 1] = .083333333333333329;
    blppde_1.d2[i + 1][i] = 36.;
    blppde_1.d2[i][i + 1] = 36.;
    /* L3: */
  }

  ge(5, 5, *blppde_1.d0, 5, 5, *blppde_1.di, 5, *blppde_1.ri, &det);

  for (i = 0; i < 5; ++i) {
    for (j = 0; j < 5; ++j) {
      s = 0.;
      for (k = 0; k < 5; ++k) {
	s += blppde_1.di[i][k] * blppde_1.d2[j][k];
	/* L4: */
      }
      blppde_1.dd[i][j] = s;
      /* L5: */
    }
/* L6: */
  }

  return 0;
}
/* gencf_ */
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








