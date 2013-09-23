#include "auto_f2c.h"

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*     brc  :  A parabolic PDE (the Brusselator) */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* (Discretized in space by polynomial collocation at Chebyshev points) */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* NOTE: The values of the constants NE and NN are defined in the file */
/*       brc.inc. If they are changed then the equations-file brc.f must */
/*       be rewritten with an editor or with the GUI Write button. */

/*      NE  :  the dimension of the PDE system */
/*      NN  :  the number of Chebyshev collocation points in space */

/* The AUTO-constant NDIM must be set equal to the value of NE*NN */
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

  /* ----------------------------------------------------------------------*/
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /*     pde  :  A parabolic PDE (the Brusselator) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* (Discretized in space by polynomial collocation at Chebyshev points) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* NOTE: The values of the constants NE and NN are defined above. */
  /*       If they are changed then the equations file brc.f must */
  /*       be rewritten with an editor or with the GUI Write button. */

  /*      NE  :  the dimension of the PDE system */
  /*      NN  :  the number of Chebyshev collocation points in space */

  /* The AUTO-constant NDIM must be set equal to the value of NE*NN */
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

  /* Set the starting solution at the Chebyshev collocation points */
  for (i = 0; i < 6; ++i) {
    u[i] = a;
    u[i + 6] = b / a;
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
  doublereal u0[2], u1[2], dc[2];
  doublereal fw[2];
  static doublereal d2[6][8];
  static ifrst = 0;

  /*     ---------- ---- */

  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /*     pde  :  A parabolic PDE (the Brusselator) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* (Discretized in space by polynomial collocation at Chebyshev points) */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */
  /* NOTE: The values of the constants NE and NN are defined above. */
  /*       If they are changed then the equations file brc.f must */
  /*       be rewritten with an editor or with the GUI Write button. */

  /*      NE  :  the dimension of the PDE system */
  /*      NN  :  the number of Chebyshev collocation points in space */

  /* The AUTO-constant NDIM must be set equal to the value of NE*NN */
  /* ---------------------------------------------------------------------- */
  /* ---------------------------------------------------------------------- */

  /* Problem-independent initialization : */

  if (ifrst != 1234) {
    gencf(par, d2);
    ifrst = 1234;
  }

  setdc(2, dc, par);
  setbc(2, par, u0, u1);

  for (i = 0; i < 6; ++i) {
    for (k = 0; k < 2; ++k) {
      w[k] = u[i + k * 6];
      /* L1: */
    }
    ff(2, w, par, fw);
    for (j = 0; j < 2; ++j) {
      f[i + j * 6] = fw[j] + dc[j] * (u0[j] * d2[i][0] + u1[j] * d2[i][7]);
      for (k = 0; k < 6; ++k) {
	f[i + j * 6] += dc[j] * d2[i][k + 1] * u[k + j * 6];
	/* L2: */
      }
/* L3: */
    }
/* L4: */
  }

  return 0;
}
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
int gencf (doublereal *par, doublereal d2[][8])
{
  /* System generated locals */
integer i1;
  /* Local variables */
  extern int ge(integer n, integer m1a, doublereal *a, integer nrhs, integer ndxloc, doublereal *u, integer m1f, doublereal *f, doublereal *det);
  extern double **dmatrix(integer, integer);
 
  doublereal c;
  integer i, j, k;
  doublereal x[8];
  doublereal **cc = dmatrix(8, 8);
  integer ic[8];
  doublereal **ri = dmatrix(8, 8);
  integer ir[8];
  doublereal **xx = dmatrix(8, 8);
  doublereal det, pi;

/*     ---------- ----- */

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*     pde  :  A parabolic PDE (the Brusselator) */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* (Discretized in space by polynomial collocation at Chebyshev points) */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/* NOTE: The values of the constants NE and NN are defined above. */
/*       If they are changed then the equations file brc.f must */
/*       be rewritten with an editor or with the GUI Write button. */

/*      NE  :  the dimension of the PDE system */
/*      NN  :  the number of Chebyshev collocation points in space */

/* The AUTO-constant NDIM must be set equal to the value of NE*NN */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */

  /* Function Body */
  pi = atan(1.) * 4;
  x[0] = 0.;
  for (k = 1; k < 7; ++k) {
    c = cos((((k + 1) * 2) - 3) * pi / 12);
    x[k] = (c + 1) / 2;
    /* L1: */
  }
  x[7] = 1.;

  for (i = 0; i < 8; ++i) {
    for (j = 0; j < 8; ++j) {
      ri[i][j] = 0.;
      i1 = j;
      xx[i][j] = pow_di(&x[i], &i1);
      /* L2: */
    }
    ri[i][i] = 1.;
    /* L3: */
  }

  ge(8, 8, *xx, 8, 8, *cc, 8, *ri, &det);

  for (i = 0; i < 6; ++i) {
    for (j = 0; j < 8; ++j) {
      d2[i][j] = 0.;
      for (k = 1; k < 7; ++k) {
	i1 = k - 1;
	d2[i][j] += cc[k + 1][j] * (k + 1) * k * pow_di(&x[i + 1], &i1);
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
