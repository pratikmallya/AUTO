/* wrapper functions for user files written in FORTRAN */

#include "config.h"
#include "auto_f2c.h"
#include "auto_c.h"

#ifdef F77_FUNC

extern int F77_FUNC(func,FUNC)(integer *, const doublereal *, const integer *,
			       const doublereal *, const integer *, doublereal *,
			       doublereal *, doublereal *);

static int f77_func(integer ndim, const doublereal *u, const integer *icp,
		    const doublereal *par, integer ijac, doublereal *f,
		    doublereal *dfdu, doublereal *dfdp)
{
  F77_FUNC(func,FUNC)(&ndim, u, icp, par, &ijac, f, dfdu, dfdp);
  return 0;
}

extern int F77_FUNC(stpnt,STPNT)(integer *, doublereal *, doublereal *, ...);

static int f77_stpnt(integer ndim, doublereal t, doublereal *u, doublereal *par)
{
  F77_FUNC(stpnt,STPNT)(&ndim, u, par, &t);
  return 0;
}

extern int F77_FUNC(bcnd,BCND)(integer *, const doublereal *, const integer *,
			       integer *, const doublereal *, const doublereal *,
			       doublereal *, integer *, doublereal *);

static int f77_bcnd(integer ndim, const doublereal *par, const integer *icp,
		    integer nbc, const doublereal *u0, const doublereal *u1,
		    integer ijac, doublereal *fb, doublereal *dbc)
{
  F77_FUNC(bcnd,BCND)(&ndim, par, icp, &nbc, u0, u1, fb, &ijac, dbc);
  return 0;
}

extern int F77_FUNC(icnd,ICND)(integer *, const doublereal *, const integer *,
			       integer *, const doublereal *, const doublereal *,
			       const doublereal *, const doublereal *,
			       doublereal *, integer *, doublereal *);

static int f77_icnd(integer ndim, const doublereal *par, const integer *icp,
		    integer nint, const doublereal *u, const doublereal *uold,
		    const doublereal *udot, const doublereal *upold, integer ijac,
		    doublereal *fi, doublereal *dint)
{
  F77_FUNC(icnd,ICND)(&ndim, par, icp, &nint, u, uold, udot, upold, fi, &ijac, dint);
  return 0;
}

extern int F77_FUNC(fopt,FOPT)(integer *, const doublereal *, const integer *,
			       const doublereal *, integer *, doublereal *,
			       doublereal *, doublereal *);

static int f77_fopt(integer ndim, const doublereal *u, const integer *icp,
		    const doublereal *par, integer ijac,
		    doublereal *fs, doublereal *dfdu, doublereal *dfdp)
{
  F77_FUNC(fopt,FOPT)(&ndim, u, icp, par, &ijac, fs, dfdu, dfdp);
  return 0;
}

extern int F77_FUNC(pvls,PVLS)(integer *, const void *, doublereal *);

static int f77_pvls(integer ndim, const void *u, doublereal *par)
{
  F77_FUNC(pvls,PVLS)(&ndim, u, par);
  return 0;
}

/* user function pointers */
const user_function_list user = { f77_func, f77_stpnt, f77_bcnd,
				  f77_icnd, f77_fopt, f77_pvls, 1 };

#endif
