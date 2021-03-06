/* fcon.f -- translated by f2c (version 19970805).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#define AUTLIB
#include "auto_f2c.h"

#define NPARX (50)
#define NIAP (41)
#define HMACH (1.0e-7)

#include <stdio.h>

/* All of these global structures correspond to common
   blocks in the original code.  They are ONLY used within
   the Homcont code.
*/
struct {
  integer itwist, istart, iequib, nfixed, npsi, nunstab, nstab, nrev;
} blhom_1;

struct {
  integer *ipsi, *ifixed, *irev;
} blhmp_1 = {NULL,NULL,NULL};


extern int stpnt(integer ndim, double t, double *u, double *par);

static void cntdif(integer n, double *d);
static int eqdf(integer ntst, integer ndim, 
                integer ncol, double *dtm, double *ups, 
                double *eqf, integer iper);
static int init(integer *iap);
static int adapt(integer *iap, integer nold, integer ncold, 
                 integer nnew, integer ncnew, double *tm, double *dtm, 
                 double *ups, double *vps);
static int interp(integer ndim, integer n, 
                  integer nc, double *tm, double *ups, 
                  integer n1, integer nc1, double *tm1, double *ups1, 
                  double *tm2, integer *itm1);
static int newmsh(integer ndim, double *ups, 
                  integer nold, integer ncold, double *tmold, 
                  double *dtmold, integer nnew, double *tmnew, integer iper);
static int wrtbv8(integer *iap, double *par, integer icp, 
                  double rldot, double *ups, 
                  double *udotps, double *tm, double *dtm);
static int intwts(integer n, double z, double *x, double *wts);
static int ordr(integer n, double * tm, 
                integer n1, double *tm1, integer *itm1);
double getp(double *code, integer ic, double *ups);


/*     ------- ------ */
int main(void)
{
  /* Local variables */
  integer ndim, ncol, nold, ntst, i, j;
  double *u, *tm, *dtm;
  double period;
  integer iap[NIAP];
  double par[NPARX], *ups, *vps;

  /* This program converts a data file into a labeled AUTO solution */

  FILE *fp3 = fopen("fort.3","r");
  if(fp3 == NULL) {
    fprintf(stderr,"Error:  Could not open fort.3\n");
    exit(1);
  }

  for (i = 0; i < NPARX; ++i) {
    par[i] = 0.;
  }

  init(iap);
  ndim = iap[0];
  u = malloc(ndim * sizeof(double));
  
  ntst = iap[4];
  ncol = iap[5];

  nold = 0;
  while(1) {
    double temp;
      
    nold++;
    if(fscanf(fp3,"%lf",&temp)!=1) 
      break;
    for(i = 0;i < ndim;i++) 
      fscanf(fp3,"%lf",&temp);
  }
  nold += -2;
  j = nold + 1;
  if ((ntst + 1) > j)
    j = (ntst + 1);
  tm = malloc(j * sizeof(double));
  dtm = malloc(j * sizeof(double));
  j = nold + 1;
  if ((ntst + 1) * ncol > j)
    j = (ntst + 1) * ncol;
  ups = malloc(j * ndim * sizeof(double));
  vps = malloc(j * ndim * sizeof(double));
  rewind(fp3);
  for (j = 0; j <= nold; j++) {
    fscanf(fp3,"%lf",&tm[j]);
    for(i = 0;i < ndim;i++) {
      fscanf(fp3,"%lf",&ups[j + i * (nold + 1)]);
      vps[j + i * (nold + 1)] = 0.;
    }
  }
  fclose(fp3);
  period = tm[nold] - tm[0];
  for (i = nold; i >= 0; --i) {
    tm[i] = (tm[i] - tm[0]) / period;
  }
  for (i = 0; i < nold; ++i) {
    dtm[i] = tm[i + 1] - tm[i];
  }
  adapt(iap, nold, 1, ntst, ncol, tm, dtm, ups, vps);

  par[10] = period;
  stpnt(ndim, 0.0, u, par);
  wrtbv8(iap, par, 1., 1., ups, vps, tm, dtm);

  free(tm);
  free(dtm);
  free(ups);
  free(vps);
  return 0;
} 


/*     ---------- ---- */
/* Subroutine */ static int init(integer *iap)
{
  /* Local variables */
  integer ndim, ncol, ntst, iad, ips, isp, isw;

  /* Reads the file of continuation constants */
  FILE *fp2 = fopen("fort.2","r");
  if(fp2 == NULL) {
    fprintf(stderr,"Error:  Could not open fort.2\n");
    exit(1);
  }

  /* read the first two ints*/
  if (fscanf(fp2,"%ld %ld\n",&ndim,&ips)!=2) {
    printf(" Error : End of file encountered in AUTO constants-file\n");
    exit(1);
  }
  /* go to the end of line*/
  while(fgetc(fp2)!='\n');
  /* skip the next line as well*/
  while(fgetc(fp2)!='\n');
  /* read the first five ints*/
  if (fscanf(fp2,"%ld %ld %ld %ld %ld\n",&ntst,&ncol,&iad,&isp,&isw)!=5) {
    printf(" Error : End of file encountered in AUTO constants-file\n");
    exit(1);
  }


  iap[0] = ndim;
  iap[1] = ips;
  iap[4] = ntst;
  iap[5] = ncol;
  iap[6] = iad;
  iap[8] = isp;
  iap[9] = isw;
  fclose(fp2);
  return 0;
} /* init_ */


/*     ---------- ----- */
/* Subroutine */
static int adapt(integer *iap, integer nold, integer ncold, 
                 integer nnew, integer ncnew, double *tm, double *dtm, 
                 double *ups, double *vps)
{
  integer ndim = iap[0], iper;
  integer i, j, noldp1 = nold + 1, nnewp1 = nnew + 1;
  integer nrwnew = ndim * ncnew;
  double *tint = malloc(nnewp1 * sizeof(double));
  double *uint = malloc(nnewp1 * nrwnew * sizeof(double));
  double *tm2 = malloc(nnewp1 * sizeof(double));
  integer *itm = malloc(nnewp1 * sizeof(double));
  integer ips, isw;

/* Adapts the distribution of the mesh points so that the increase of the */
/* monotone function EQDF becomes approximately equidistributed over the */
/* intervals. The functions UPS and VPS are interpolated on new mesh. */

  ips = iap[1];
  isw = iap[9];

  for (j = 0; j < nnewp1; ++j) {
    for (i = 0; i < nrwnew; ++i) {
      uint[j + i * nnewp1] = 0.;
    }
  }

  /* For periodic boundary conditions extrapolate by periodicity. */

  if (ips == 2 && abs(isw) != 2) {
    iper = 1;
  } else {
    iper = 0;
  }

  /* Generate the new mesh : */

  newmsh(ndim, ups, nold, ncold, tm, dtm, nnew, tint, iper);

  /* Replace UPS by its interpolant on the new mesh : */

  interp(ndim, noldp1, ncold, tm, ups, nnewp1, ncnew, tint, uint, tm2, itm);
  for (j = 0; j < nnewp1; ++j) {
    for (i = 0; i < nrwnew; ++i) {
      ups[j + i * nnewp1] = uint[j + i * nnewp1];
    }
  }

  /* Replace VPS by its interpolant on the new mesh : */

  interp(ndim, noldp1, ncold, tm, vps, nnewp1, ncnew, tint, uint, tm2, itm);
  for (j = 0; j < nnewp1; ++j) {
    for (i = 0; i < nrwnew; ++i) {
      vps[j + i * nnewp1] = uint[j + i * nnewp1];
    }
  }

  /* Replace old mesh : */

  tm[0] = 0.;
  for (j = 0; j < nnew; ++j) {
    dtm[j] = tint[j + 1] - tint[j];
    tm[j + 1] = tint[j + 1];
  }

  free(uint);
  free(tint);
  free(tm2);
  free(itm);
  return 0;
} /* adapt_ */


/*     ---------- ------ */
/* Subroutine */
static int interp(integer ndim, integer n, 
                  integer nc, double *tm, double *ups, 
                  integer n1, integer nc1, double *tm1, double *ups1, 
                  double *tm2, integer *itm1)
{
  integer i, j, k, l, j1, k1, l1, n1m1, ncp1;
  double d, ri, z;
  double *w = malloc((nc + 1) * sizeof(double));
  double *x = malloc((nc + 1) * sizeof(double));

  /* Finds interpolant (TM(.) , UPS(.) ) on new mesh TM1. */

  ncp1 = nc + 1;
  n1m1 = n1 - 1;

  for (i = 0; i < nc1; ++i) {
    ri = (double) i;
    d = ri / (double)nc1;
    for (j1 = 0; j1 < n1m1; ++j1) {
      tm2[j1] = tm1[j1] + d * (tm1[j1 + 1] - tm1[j1]);
    }
    ordr(n, tm, n1m1, tm2, itm1);
    for (j1 = 0; j1 < n1m1; ++j1) {
      j = itm1[j1];
      z = tm2[j1];
      d = (tm[j] - tm[j - 1]) / (double)nc;
      for (l = 0; l < ncp1; ++l) {
	x[l] = tm[-1 + j] + (double)l * d;
      }
      intwts(ncp1, z, x, w);
      for (k = 0; k < ndim; ++k) {
	k1 = i * ndim + k;
	ups1[j1 + k1 * n1] = w[ncp1 - 1] * ups[j + k * n];
	for (l = 0; l < nc; ++l) {
	  l1 = k + l * ndim;
	  ups1[j1 + k1 * n1] += w[l] * ups[(j - 1) + l1 * n];
	}
      }
    }
  }

  for (i = 0; i < ndim; ++i) {
    ups1[(n1 - 1) + i * n1] = ups[(n - 1) + i * n];
  }

  free(x);
  free(w);
  return 0;
} /* interp_ */


/*     ---------- ------ */
/* Subroutine */
static int newmsh(integer ndim, double *ups, 
                  integer nold, integer ncold, double *tmold, 
                  double *dtmold, integer nnew, double *tmnew, integer iper)
{

  integer j, j1, noldp1, nnewp1;
  double x, dal;
  integer *ial = malloc((nnew + 1) * sizeof(double));
  double *uneq = malloc((nnew + 1) * sizeof(double));
  double *eqf = malloc((nold + 1) * sizeof(double));

  /* Redistributes the mesh according to the function EQDF. */

  /* Put the values of the monotonely increasing function EQDF in EQF. */

  eqdf(nold, ndim, ncold, dtmold, ups, eqf, iper);

  /* Uniformly divide the range of EQDF : */

  noldp1 = nold + 1;
  nnewp1 = nnew + 1;
  dal = eqf[noldp1 - 1] / nnew;
  for (j = 0; j < nnewp1; ++j) {
    uneq[j] = j * dal;
  }

  ordr(noldp1, eqf, nnewp1, uneq, ial);

  /* Generate the new mesh in TMNEW : */

  for (j1 = 0; j1 < nnewp1; ++j1) {
    j = ial[j1];
    x = (uneq[j1] - eqf[j - 1]) / (eqf[j] - eqf[j - 1]);
    tmnew[j1] = (1. - x) * tmold[-1 + j] + x * tmold[j];
  }

  free(ial);
  free(eqf);
  free(uneq);
  return 0;
} /* newmsh_ */


/*     ---------- ---- */
/* Subroutine */
static int ordr(integer n, double * tm, 
                integer n1, double *tm1, integer *itm1)
{
  /* Local variables */
  integer j, k0, j1, k1;

  /* TM and TM1 are two ascending arrays with values in [0,1]. On exit the */
  /* value of ITM1( i ) specifies the index of the TM-interval in which */
  /* TM1(i) lies. */

  /* Function Body */
  k0 = 2;
  k1 = 1;
  for (j1 = 0; j1 < n1; ++j1) {
    for (j = k0 - 1; j < n; ++j) {
      k1 = j + 1;
      if (tm1[j1] < tm[j]) {
        break;
      }
    }
    itm1[j1] = k1 - 1;
    k0 = k1;
  }

  return 0;
} /* ordr_ */


/*     ---------- ------ */
/* Subroutine */
static int intwts(integer n, double z, double *x, double *wts)
{
  /* Local variables */
  integer k;
  double p, denom;
  integer ib;

/* Generates weights for Lagrange interpolation. */

  for (ib = 0; ib < n; ++ib) {
    p = 1.;
    denom = 1.;
    for (k = 0; k < n; ++k) {
      if (k != ib) {
	p *= z - x[k];
	denom *= x[ib] - x[k];
      }
    }
    wts[ib] = p / denom;
  }

  return 0;
} /* intwts_ */


/*     ---------- ---- */
/* Subroutine */
static int eqdf(integer ntst, integer ndim, 
                integer ncol, double *dtm, double *ups, 
                double *eqf, integer iper)
{
  /* System generated locals */
  double d2;

  /* Local variables */
  double dtav, e;
  integer i, j, k;
  logical small;
  integer k1;
  double sc;
  double *wh = malloc(sizeof(double) * (ncol + 1));
  double *hd = malloc(sizeof(double) * (ntst + 1) * ncol * ndim);
  integer jp1;
  double pwr;

  /* Function Body */
  cntdif(ncol, wh);

  small = TRUE_;
  for (j = 0; j < ntst; ++j) {
    jp1 = j + 1;
    sc = 1. / pow_di(&dtm[j], &ncol);
    for (i = 0; i < ndim; ++i) {
      hd[j + i * (ntst + 1)] = wh[ncol] * ups[jp1 + i * (ntst + 1)];
      for (k = 0; k < ncol; ++k) {
	k1 = i + k * ndim;
	hd[j + i * (ntst + 1)] += wh[k] * ups[j + k1 * (ntst + 1)];
      }
      hd[j + i * (ntst + 1)] = sc * hd[j + i * (ntst + 1)];
      if (fabs(hd[j + i * (ntst + 1)]) > HMACH) {
	small = FALSE_;
      }
    }
  }

  /* Take care of "small derivative" case. */

  if (small) {
    for (i = 0; i < ntst + 1; ++i) {
      eqf[i] = (double) i;
    }
    return 0;
  }

  if (iper != 1) {
  /* Extend by extrapolation : */

    for (i = 0; i < ndim; ++i) {
      hd[ntst + i * (ntst + 1)] = hd[(ntst - 1) + i *  (ntst + 1)] * 2 - hd[ntst - 2 + i * (ntst + 1)];
    }
    dtm[ntst] = dtm[-1 + ntst];
  } else {
  /* Extend by periodicity : */
      
    for (i = 0; i < ndim; ++i) {
      hd[ntst + i * (ntst + 1)] = hd[i *  (ntst + 1)];
    }
    dtm[ntst] = dtm[0];
  }
  
  /* Compute approximation to (NCOL+1)-st derivative : */

  for (j = 0; j < ntst; ++j) {
    jp1 = j + 1;
    dtav = (dtm[j] + dtm[j + 1]) * .5;
    sc = 1. / dtav;
    for (i = 0; i < ndim; ++i) {
      hd[j + i * (ntst + 1)] = sc * (hd[jp1 + i * (ntst + 1)] - hd[j + i * (ntst + 1)]);
    }
  }

  /* Define the equidistribution function : */

  pwr = 1. / (ncol + 1.);
  eqf[0] = 0.;
  for (j = 0; j < ntst; ++j) {
    e = 0.;
    for (i = 0; i < ndim; ++i) {
      d2 = fabs(hd[j + i * (ntst + 1)]);
      e += pow_dd(&d2, &pwr);
    }
    eqf[j + 1] = eqf[j] + dtm[j] * e;
  }

  free(wh);
  free(hd);
  return 0;
} /* eqdf_ */


/*     ---------- ------ */
/* Subroutine */ static void cntdif(integer n, double *d)
{
  /* Local variables */
  integer i, k, k1;
  double sc;
  integer np1;

/* Generates the coefficients of the central difference formula for */
/* Nth derivative at uniformly spaced points */

  d[0] = 1.;
  if (n == 0) {
    return;
  }

  for (i = 0; i < n; ++i) {
    d[i + 1] = 0.;
    for (k = 1; k <= i + 1; ++k) {
      k1 = i + 2 - k;
      d[k1] = d[k1 - 1] - d[k1];
    }
    d[0] = -d[0];
  }

  /* Scale to [0,1]  : */

  sc = (double) pow_ii(n, n);
  np1 = n + 1;
  for (i = 0; i < np1; ++i) {
    d[i] = sc * d[i];
  }

  return;
} /* cntdif_ */


/*     ---------- ------ */
/* Subroutine */
static int wrtbv8(integer *iap, double *par, integer icp, 
                  double rldot, double *ups, 
                  double *udotps, double *tm, double *dtm)
{
  /* Local variables */
  integer ndim, ncol, ntst, i, j, k, nrowpr, nrd, isw, k1, k2;
  double t, rn;
  FILE *fp8;

  /* Function Body */
  ndim = iap[0];
  ntst = iap[4];
  ncol = iap[5];
  isw = iap[9];

  /* Write information identifying the solution : */

  nrd = ndim / 7 + 2 + (ndim - 1) / 7;
  nrowpr = nrd * (ncol * ntst + 1) + 3 + (NPARX - 1) / 7;

  fp8 = fopen("fort.8","w");
  if(fp8 == NULL) {
    fprintf(stderr,"Error:  Could not open fort.8\n");
    exit(1);
  }  
  
  fprintf(fp8,"%5d",1); /* ibr */
  fprintf(fp8,"%5d",1); /* mtot */
  fprintf(fp8,"%5d",9); /* itp */
  fprintf(fp8,"%5d",1); /* lab */
  fprintf(fp8,"%5d",1); /* nfpr */
  fprintf(fp8,"%5ld",isw);
  fprintf(fp8,"%5ld",ncol * ntst + 1); /* ntpl */
  fprintf(fp8,"%5ld",ndim + 1); /* nar */
  fprintf(fp8,"%7ld",nrowpr);
  fprintf(fp8,"%5ld",ntst);
  fprintf(fp8,"%5ld",ncol);
  fprintf(fp8,"%5d\n",NPARX);

  /* Write the entire solution on unit 8 : */

  for (j = 0; j < ntst; ++j) {
    rn = 1. / ncol;
    for (i = 0; i < ncol; ++i) {
      k1 = i * ndim;
      k2 = (i + 1) * ndim - 1;
      t = tm[j] + i * rn * dtm[j];

      fprintf(fp8,"    %18.10E",t);
      for (k = k1; k <= k2; ++k) {
	fprintf(fp8,"%18.10E",ups[j + k * (ntst + 1)]);
      }
      fprintf(fp8,"\n");
    }
  }
  fprintf(fp8,"    %18.10E",tm[ntst]);
  for (i = 0; i < ndim; ++i) {
    fprintf(fp8,"%18.10E",ups[ntst + i * (ntst + 1)]);
  }
  fprintf(fp8,"\n");
    
/* Write the free parameter indices: */

  fprintf(fp8,"%5ld",icp);
  fprintf(fp8,"\n");
    
/* Write the direction of the branch: */

  fprintf(fp8,"    ");
  fprintf(fp8,"%18.10E",rldot);
  fprintf(fp8,"\n");
  for (j = 0; j < ntst; ++j) {
    for (i = 0; i < ncol; ++i) {
      k1 = i * ndim;
      k2 = (i + 1) * ndim - 1;
      fprintf(fp8,"    ");
      for (k = k1; k <= k2; ++k) {
	fprintf(fp8,"%18.10E",udotps[j + k * (ntst + 1)]);
      }
      fprintf(fp8,"\n");
    }
  }
  fprintf(fp8,"    ");
  for (k = 0; k < ndim; ++k) {
    fprintf(fp8,"%18.10E",udotps[ntst + k * (ntst + 1)]);
  }
  fprintf(fp8,"\n");
    
/* Write the parameter values. */

  for (i = 0; i < NPARX; ++i) {
    if(i%7==0)
      fprintf(fp8,"    ");
    fprintf(fp8,"%18.10E",par[i]);
    if((i+1)%7==0)
      fprintf(fp8,"\n");
  }
  fprintf(fp8,"\n");
  fclose(fp8);

  return 0;
} /* wrtbv8_ */


double getp(double *code, integer ic, double *ups)
{
  /* System generated locals */
  double ret_val=0.0;

  /* Dummy routine (in case GETP is called in the user routine PVLS) */
  return ret_val;
} /* getp_ */
