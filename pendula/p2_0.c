/*************************************************************************
	Problem :     DOUBLE PENDULA.
	Written by :  NGUYEN, THANH LONG.
	For :         Dr. SEBIUS DOEDEL.
	Date :        JAN, 4, 1990.
	Modify :      APR, 21, 1990.
 *************************************************************************/
#include <math.h>
#include <stdio.h>
#include <gl.h>
#include <device.h>
#include <fcntl.h>
#include <string.h>

#define radius 0.15
#define npoint   18

#define NMAX 200 
float **dpendula ;
float **pd,  **band,  **bar ;
float **npd, **nband, **nbar ;

float PI ;
int npoint2 ;

int   plabel[NMAX], ppoint[NMAX], pindex[NMAX] ;
int   nlabel, cur_label, id_label ;
float cvec2[3] = {0.05, 0.05, 0.05} ;

float cvec[24][3] = {{0.0, 1.0, 1.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 1.0},
		     {1.0, 1.0, 0.0}, {1.0, 1.0, 1.0}, {1.0, 0.0, 0.0},
		     {0.0, 0.0, 0.0}, {0.0, 0.0, 0.5}, {0.0, 0.5, 0.0},
		     {0.5, 0.5, 0.0}, {0.5, 0.5, 0.5}, {0.5, 0.5, 1.0},
		     {0.5, 1.0, 1.0}, {1.0, 0.5, 1.0}, {1.0, 0.5, 0.5},
		     {0.0, 0.5, 0.5}, {1.0, 0.5, 0.0}, {0.5, 0.0, 0.5},
		     {0.5, 0.0, 0.5}, {1.0, 0.0, 0.5}, {0.0, 0.5, 1.0},
		     {0.5, 1.0, 0.5}, {1.0, 1.0, 0.5}, {0.05, 0.05, 0.05}} ;

float pd1_m[] =
  {
    AMBIENT,    0.0,  0.0,  0.2,
    DIFFUSE,    0.6,  0.3,  0.0,
    SPECULAR,   0.35, 0.25, 0.1,
    SHININESS, 47.0,
    LMNULL
  } ;

float pd2_m[] =
  {
    AMBIENT,    0.0,  0.0,  0.2,
    DIFFUSE,    0.35, 0.25,  0.0,
    SPECULAR,   0.45, 0.38, 0.0,
    SHININESS, 65.0,
    LMNULL
  } ;

float band_m[] =
  {
    AMBIENT,    0.1, 0.1, 0.1,
    DIFFUSE,    0.3, 0.3, 0.3,
    SPECULAR,   0.4, 0.4, 0.4,
    SHININESS, 20.0,
    LMNULL
  } ;

float bar1_m[] =
  {
    DIFFUSE,    0.0, 0.3, 0.0,
    SPECULAR,   0.5, 0.6, 0.0,
    SHININESS, 70.0,
    LMNULL
  } ;

float bar2_m[] =
  {
    DIFFUSE,    0.0, 0.35, 0.35,
    SPECULAR,   0.0, 0.55, 0.55,
    SHININESS, 45.0,
    LMNULL
  } ;

float light1[] =
  {
    POSITION, 2.0, 2.0, 2.0, 0.0,
    LMNULL
  } ;

float light2[] =
  {
    POSITION, 0.0, 2.0, 2.0, 0.0,
    LMNULL
  } ;

float light3[] =
  {
    POSITION, -2.0, 2.0, 2.0, 0.0,
    LMNULL
  } ;

long gid1, gid2 ;
int  number[10] = {46, 8, 14, 15, 22, 23, 30, 31, 38, 39} ;

/************************************************************************
	Window size:
        	xmin = -0.6		xmax = 0.6
        	ymin = -0.6		ymax = 0.6
        	zmin = -0.6		zmax = 0.6
 ************************************************************************/
float  norm() ;
int    getnum() ;
int    get_index() ;
double geo_dot() ;


float norm(x, y, z)
float x, y, z ;
{
  return x * x + y * y + z * z ;
}

copyval(float x1[3], float x[3])
{
  x1[0] = x[0] ;
  x1[1] = x[1] ;
  x1[2] = x[2] ;
}

geo_cross(float v0[3], float v1[3], float v2[3])
{
  v2[0] = v0[1] * v1[2] - v0[2] * v1[1] ;
  v2[1] = v0[2] * v1[0] - v0[0] * v1[2] ;
  v2[2] = v0[0] * v1[1] - v0[1] * v1[0] ;
}

double geo_dot(v0, v1)
float v0[3], v1[3] ;
{
  return sqrt(v0[0] * v1[0] + v0[1] * v1[1] + v0[2] * v1[2]) ;
}

geo_norm(float v0[3])
{
  double len ;
  if ((len = geo_dot(v0, v0)) <= 0.0)
    return ;
  v0[0] /= len ;
  v0[1] /= len ;
  v0[2] /= len ;
}

geo_line(float p0[3], float p1[3], float p2[3])
{
  p2[0] = p1[0] - p0[0] ;
  p2[1] = p1[1] - p0[1] ;
  p2[2] = p1[2] - p0[2] ;
}

/**********************************************************************
		Create memory for dynamic array.
 **********************************************************************/
float **FDIM2(int row, int col)
{
  int i ;
  float **prow, *pdata ;

  pdata = (float *) calloc(row * col, sizeof(float)) ;
  if (pdata == (float *) NULL)
    {
      printf(" Error, FDIM2: no memory for data input 1.\n") ;
      exit(1) ;
    }

  prow = (float **) calloc(row, sizeof(float *)) ;
  if (prow == (float **) NULL)
    {
      printf(" Error, FDIM2: no memory for data input 2.\n") ;
      exit(1) ;
    }

  for (i = 0; i < row; i++)
    {
      prow[i] = pdata ;
      pdata  += col ;
    }
  return prow ;
}

/**********************************************************************
			Free memory allocation.
 **********************************************************************/
FFREE2 (a)
float **a ;
{
  free(*a) ;
  free(a) ;
}

/**********************************************************************
			Free all data.
 **********************************************************************/
free_data() 
{
  FFREE2(dpendula) ;
  FFREE2(pd) ;
  FFREE2(npd) ;
  FFREE2(band) ;
  FFREE2(nband) ;
  FFREE2(bar) ;
  FFREE2(nbar) ;
}

/**********************************************************************/

cpnorm(ob, low, high, nob)
float **ob, **nob ;
int low, high ;
{
  int i, i0, i2, j ;
  float v1[3], v2[3], v3[3] ;

  for (i = low; i <= high; i++)
    {
      if (i == low)
	i0 = high ;
      else
	i0 = i - 1 ;
      if (i == high)
	i2 = low ;
      else
	i2 = i + 1 ;
      geo_line(ob[i0], ob[i],  v1) ;
      geo_line(ob[i],  ob[i2], v2) ;
      geo_cross(v1, v2, nob[i]) ;
      geo_norm(nob[i]) ; 
    }
}

/***************    create cylinder, bar, band     *******************/
create_cylinder()
{
  float c1[npoint][3], c2[npoint][3], st, a, r1 ;
  int   i, j, i1, n, low, high ;

  n   = npoint * 14 ;
  pd  = FDIM2(n, 3) ;
  npd = FDIM2(n, 3) ;
  a   = PI * 2.0 / npoint ;
  st  = a / 2.0 ;
  n   = j = 2 * npoint - 1 ;
  r1  = radius - 0.015 ;

  for (i = 0; i < npoint; i++)
    {
      pd[i][0] =  0.02 ;
      pd[j][0] = -0.02 ;
      pd[i][1] = pd[j][1] = r1 * cos(st) - 0.45 ;
      pd[i][2] = pd[j][2] = r1 * sin(st) ;

      c1[i][0] =  0.01 ;
      c2[i][0] = -0.01 ;
      c1[i][1] = c2[i][1] = radius * cos(st) - 0.45 ;
      c1[i][2] = c2[i][2] = radius * sin(st) ;
      j-- ;
      st += a ;
    }

  for (i = 0; i < npoint; i++)
    {
      i1 = (i + 1) % npoint ;
      copyval(pd[++n], c1[i]) ;
      copyval(pd[++n], c2[i]) ;
      copyval(pd[++n], c2[i1]) ;
      copyval(pd[++n], c1[i1]) ;
    }

  for (i = 0; i < npoint; i++)
    {
      i1 = (i + 1) % npoint ;
      copyval(pd[++n], pd[i]) ;
      copyval(pd[++n], c1[i]) ;
      copyval(pd[++n], c1[i1]) ;
      copyval(pd[++n], pd[i1]) ;
    }

  for (i = 0; i < npoint; i++)
    {
      i1 = (i + 1) % npoint ;
      copyval(pd[++n], c2[i]) ;
      copyval(pd[++n], pd[i]) ;
      pd[n][0] = - pd[i][0] ;
      copyval(pd[++n], pd[i1]) ;
      pd[n][0] = - pd[i1][0] ;
      copyval(pd[++n], c2[i1]) ;
    }

  low   = 0 ;
  high  = npoint - 1 ;
  cpnorm(pd, low, high, npd) ;
  low   = high + 1 ;
  high += npoint ;
  cpnorm(pd, low, high, npd) ;

  n = npoint * 3 ;
  for (i = 0; i < n; i++)
    {
      low   = high + 1 ;
      high += 4 ;
      cpnorm(pd, low, high, npd) ;
    }
}

/**********************************************************************
		Create data object for the bar.
 **********************************************************************/
create_bar()
{
  float st, a, d, r ;
  float s1[4][3], s2[4][3] ;
  int i, i1, n, low, high ;

  n    = 20 ;
  bar  = FDIM2(n, 3) ;
  nbar = FDIM2(n, 3) ;
  a    = PI / 12.0 ;
  st   = - a / 2.0 ;
  d    = radius * sin(-st) ;
  r    = 0.005 ;

  for (i = 3; i > 1; i--)
    {
      bar[i][0] = r ;
      bar[i][1] = radius * cos(st) - 0.45 ;
      bar[i][2] = radius * sin(st) ;
      st += a ;
    }

  bar[1][0] = r ;
  bar[1][1] = d ;
  bar[1][2] = bar[2][2] ;

  bar[0][0] = r ;
  bar[0][1] = d ;
  bar[0][2] = bar[3][2] ;

  for (i = 0; i < 4; i++)
    {
      if (i == 0)
        i1 = 5 ;
      else if (i == 1)
	i1 = 4 ;
      else if (i == 2)
	i1 = 7 ;
      else
	i1 = 6 ;

      s2[i][0] = bar[i1][0] = -r ;
      s1[i][1] = s2[i][1] = bar[i1][1] = bar[i][1] ;
      s1[i][2] = s2[i][2] = bar[i1][2] = bar[i][2] ;
      s1[i][0] = bar[i][0] ;
    }

  n = 7 ;
  copyval(bar[++n], s1[1]) ;
  copyval(bar[++n], s2[1]) ;
  copyval(bar[++n], s2[2]) ;
  copyval(bar[++n], s1[2]) ;

  copyval(bar[++n], s2[0]) ;
  copyval(bar[++n], s1[0]) ;
  copyval(bar[++n], s1[3]) ;
  copyval(bar[++n], s2[3]) ;

  copyval(bar[++n], s1[0]) ;
  copyval(bar[++n], s2[0]) ;
  copyval(bar[++n], s2[1]) ;
  copyval(bar[++n], s1[1]) ;

  low  = 0 ;
  high = 3 ;
  for (i = 0; i < 5; i++)
    {
      cpnorm(bar, low, high, nbar) ;
      low   = high + 1 ;
      high += 4 ;
    }
}

/***********************************************************************
		Create data object for elastic band.
 ***********************************************************************/
create_band()
{
  int   i, j, n, n1, i1, i2, low, high ;
  float d, d1, d2, d3, st, a1 ;

  n     = npoint2 * 16 ;
  band  = FDIM2(n, 3) ;
  nband = FDIM2(n, 3) ;
  a1    = 82.5 * PI / 180.0 ;
  d     = 0.245 ;
  d1    = radius * cos(a1) ;
  d2    = - d1 ;
  d3    = (d * 2.0) / (float) npoint2 ;

  band[0][0] = band[1][0] = d ;
  band[2][0] = band[3][0] = d - d3 ;
  band[0][1] = band[1][1] = band[2][1] = band[3][1] = d1 ;
  band[0][2] = band[3][2] = d1 ;
  band[1][2] = band[2][2] = d2 ;

  for (i = 1; i < npoint2; i++)
    {
      i1 = i * 4 ;
      i2 = (i - 1) * 4 ;
      for (j = 0; j < 4; j++)
	{
	  band[i1+j][0] = band[i2+j][0] - d3 ;
	  band[i1+j][1] = band[i2+j][1] ;
	  band[i1+j][2] = band[i2+j][2] ;
	}
    }

  n1 = npoint2 * 4 ;
  n  = n1 - 1 ;
  a1 = st = PI / 2.0 ;

  for (j = 0; j < 3; j++)
    {
      for (i = 0; i < n1; i++)
	{
	  n++ ;
	  band[n][0] = band[i][0] ;
	  band[n][1] = band[i][1] * cos(st) - band[i][2] * sin(st) ;
          band[n][2] = band[i][1] * sin(st) + band[i][2] * cos(st) ;
	}
      st += a1 ;
    }

  low  = 0 ;
  high = 3 ;
  for (i = 0; i < n1; i++)
    {
      cpnorm(band, low, high, nband) ;
      low   = high + 1 ;
      high += 4 ;
    }
}


draw_polygon(ob, nob, low, high)
float **ob, **nob ;
int low, high ;
{
  int i ;

  bgnpolygon() ;
  for (i = low; i <= high; i++)
    {
      n3f(nob[i]) ;
      v3f(ob[i]) ;
    }
  endpolygon() ;
}


draw_cylinder()
{
  int i, low, high, n ;

  low  = 0 ;
  high = npoint - 1 ;
  draw_polygon(pd, npd, low, high) ;

  low   = high + 1 ;
  high += npoint ;
  draw_polygon(pd, npd, low, high) ;

  n = npoint * 3 ;
  for (i = 0; i < n; i++)
    {
      low   = high + 1 ;
      high += 4 ;
      draw_polygon(pd, npd, low, high) ;
    }
}


draw_bar()
{
  int i, low, high ;

  low  = 0 ;
  high = 3 ;
  for (i = 0; i < 5; i++)
    {
      draw_polygon(bar, nbar, low, high) ;
      low  += 4 ;
      high += 4 ;
    }
}


draw_band(float rx1, float rx2)
{
  int i, j, low ;
  float dx ;
  float a[161] ;

  dx   = (rx2 - rx1) / (float) npoint2 ;
  a[0] = rx2 ;

  for (i = 1; i <= npoint2; i++)
    a[i] = a[i-1] - dx ;
  low = 0 ;

  for (i = 0; i < 4; i++)
    for (j = 0; j < npoint2; j++)
      {
	bgnpolygon() ;
	  pushmatrix() ;
	    rot(a[j], 'x') ;
	    n3f(nband[low]) ;
	    v3f(band[low]) ;
	    n3f(nband[low+1]) ;
	    v3f(band[low+1]) ;
	  popmatrix() ;

	  pushmatrix() ;
            rot(a[j+1], 'x') ;
	    n3f(nband[low+2]) ;
	    v3f(band[low+2]) ;
        endpolygon() ;

        bgnpolygon() ;
            n3f(nband[low+2]) ;
	    v3f(band[low+2]) ;
	    n3f(nband[low+3]) ;
	    v3f(band[low+3]) ;
	  popmatrix() ;

	  pushmatrix() ;
	    rot(a[j], 'x') ;
	    n3f(nband[low]) ;
	    v3f(band[low]) ;
	  popmatrix() ;
	endpolygon() ;
	low += 4 ;
      }
}

ident(Matrix m)
{
  int i, j ;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (i == j)
	m[i][j] = 1.0 ;
      else
	m[i][j] = 0.0 ;
}

/******************   Copy matrix  A = B    ******************************/
copyma(Matrix a, Matrix b)
{
  int i, j ;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4 ; j++)
      a[i][j] = b[i][j] ;
}

/*****************      Mutiply two matrices  A = A * B     **************/
multma(Matrix a, Matrix b)
{
  Matrix c ;
  int    i, j, l ;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      {
	c[i][j] = 0.0 ;
	for (l = 0; l < 4; l++)
	  c[i][j] += a[i][l] * b[l][j] ;
      }
  copyma(a, c) ;
}

transformation(Matrix t, float a, int code)
{
  ident(t) ;
  if (code == 1)
    {
      t[1][1] = t[2][2] = cos(a) ;
      t[2][1] = - sin(a) ;
      t[1][2] =   sin(a) ;
    }
  else if (code == 2)
    {
      t[0][0] = t[2][2] = cos(a) ;
      t[2][0] =   sin(a) ;
      t[0][2] = - sin(a) ;
    }
  else
    {
      t[0][0] = t[1][1] = cos(a) ;
      t[1][0] = - sin(a) ;
      t[0][1] =   sin(a) ;
    }
}

def_light()
{
  lmdef(DEFMATERIAL, 1, 15, pd1_m) ;
  lmdef(DEFMATERIAL, 2, 15, pd2_m) ;
  lmdef(DEFMATERIAL, 3, 15, band_m) ;
  lmdef(DEFMATERIAL, 4, 11, bar1_m) ;
  lmdef(DEFMATERIAL, 5, 11, bar2_m) ;
  lmdef(DEFLIGHT,    1,  6, light1) ;
  lmdef(DEFLIGHT,    2,  6, light2) ;
  lmdef(DEFLIGHT,    3,  6, light3) ;
  lmdef(DEFLMODEL,   1,  0, NULL) ;
}

use_light()
{
  lmbind(LIGHT0, 1) ;
  lmbind(LIGHT1, 2) ;
  lmbind(LIGHT2, 3) ;
  lmbind(LMODEL, 1) ;
}

/**********************************************************************
		Store data into dpendula array.
 **********************************************************************/
store_data(argv)
char **argv ;
{
  int   branch, point, type, label, npairs, iso, ntpl, pairs, totalp ;
  int   i, n ;
  float st, x1, x2, dt ;
  FILE *fd ;

  n = 0 ;
  for (i = 0; i < nlabel; i++)
    n += ppoint[i] ;

  dpendula = FDIM2(n, 2) ;
  st = PI / 2.0 ;
  n  = 0 ;
  fd = fopen(argv[1], "r") ;

  while (fscanf(fd, "%d %d %d %d %d %d %d %d %d", &branch, &point, &type,
	 &label, &npairs, &iso, &ntpl, &pairs, &totalp) != EOF)
    {
      if( ntpl > 1 ) ntpl = ntpl - 1;
      while (getc(fd) != '\n') ;
      for (i = 0; i < ntpl; i++)
	{
	  fscanf(fd, "%f %f %f", &dt, &x1, &x2) ;
	  dpendula[n][0] = x1 * 180.0 / PI + st ;
	  dpendula[n][1] = x2 * 180.0 / PI + st ;
	  n++ ;
	  while (getc(fd) != '\n') ;
	}

      for (i = ntpl; i < totalp; i++)
	while (getc(fd) != '\n') ;
    }
  fclose(fd) ;
}

/**********************************************************************
	Read data from input file and error checking.
 **********************************************************************/
read_data(argv, error)
char **argv ;
int *error ;
{
  int branch, point, type, label, npairs, iso, ntpl, pairs, totalp ;
  int i, n ;
  FILE *fd ;
  float x1, x2, dt ;

  *error = 0 ;
  n = nlabel = 0 ;

  fd = fopen(argv[1], "r") ;
  if (fd == NULL)
    {
      *error = 1 ;
      return ;
    }

  while (fscanf(fd, "%d %d %d %d %d %d %d %d %d", &branch, &point, &type,
		&label, &npairs, &iso, &ntpl, &pairs, &totalp) != EOF)
    {
      if( ntpl > 1 ) ntpl = ntpl - 1;
      while (getc(fd) != '\n') ;
      if (nlabel > NMAX)
	{
	  *error = 3 ;
	  fclose(fd) ;
	  return ;
	}
      if (ntpl <= 0)
	{
	  *error = 2 ;
	  fclose(fd) ;
	  return ;
	}

      plabel[nlabel] = label ;
      ppoint[nlabel] = ntpl ;
      pindex[nlabel] = n ;

      for (i = 0; i < ntpl; i++)
	if (fscanf(fd, "%f %f %f", &dt, &x1, &x2) == NULL)
	  {
	    *error = 4 ;
	    fclose(fd) ;
	    return ;
	  }
	else
	  {
	    while (getc(fd) != '\n') ;
	    n++ ;
	  }

      for (i = ntpl; i < totalp; i++)
	if (fscanf(fd, "%f", &dt) == NULL)
	  {
	    *error = 4 ;
	    fclose(fd) ;
	    return ;
	  }
	else
	  while (getc(fd) != '\n') ;
      nlabel++ ;
    }

  if (nlabel == 0)
    *error = 5 ;
  fclose(fd) ;
}

check_command(argc, argv)
int argc ;
char **argv ;
{
  npoint2 = 40 ;
  if (argc == 3)
    {
      if (argv[2][0] == '1')
	npoint2 = 20 ;
      else if (argv[2][0] == '2')
	npoint2 = 40 ;
      else if (argv[2][0] == '3') 
 	npoint2 = 80 ;
      else if (argv[2][0] == '4')
	npoint2 = 160 ;
      else
	npoint2 = 40 ;
    }
  else if (argc == 1)
    {
      printf(" Error, in comand line.\n") ;
      exit(1) ;
    }
}

open_gl()
{
  Matrix t ;

  keepaspect(1, 1) ;
  gid1 = winopen("Double_pendula.") ; 
  RGBmode() ;
  doublebuffer() ;
  gconfig() ;
  lsetdepth(0, 0x7FFFFF) ;

  zbuffer(TRUE) ;
  mmode(MVIEWING) ;
  perspective(100, 1.0, 4.0, 12.0) ;
  ident(t) ;
  loadmatrix(t) ;
  lookat(0.0, 0.0, 8.0, 0.0, 0.0, 0.0, 0) ;
  def_light() ;
  use_light() ;
  cpack(0) ;
  clear() ;
}

close_gl()
{
  winclose(gid1) ; 
}

open_gl2()
{
  prefposition(280, 1000, 320, 712) ;
  gid2 = winopen("Label window") ;
  RGBmode() ;
  gconfig() ;
  c3f(cvec2) ;
  clear() ;
}

close_gl2()
{
  winclose(gid2) ;
}

create_pendula()
{
  create_bar() ;
  create_band() ;
  create_cylinder() ;
}

get_return()
{
  while (TRUE)
    if (qtest())
      if (getbutton(RETKEY) || getbutton(ESCKEY))
	{
	  qreset() ;
	  break ;
	}
}

pr_error(char str[])
{
  int col, row ;

  row = 23 ;
  col = (80 - strlen(str)) / 2 ;
  stpos(str, row, col, 5, 0) ;
  get_return() ;
}

int get_num(int row, int col, int icol)
{
  int num, index, i ;
  char str[10][2] ;

  for (i = 0; i < 10; i++)
    {
      str[i][0] = i + '0' ;
      str[i][1] = '\0' ;
    }
  num = 0 ;
  index = 0 ;

  while (TRUE)
    {
      if (qtest())
	{
	  for (i = 0; i < 10; i++)
	    if (getbutton(number[i]) && index < 4)
	      {
		num = num * 10 + i ;
		stpos(str[i], row, col +index, icol, 0) ;
		index++ ;
	      }
	  if (getbutton(DELKEY) || getbutton(BACKSPACEKEY))
	    {
	      if (index > 0)
		{
		  i = num % 10 ;
		  num /= 10 ;
		  index-- ;
		  stpos(str[i], row, col + index, 23, 0) ;
		}
	    }
	  if (getbutton(RETKEY) || getbutton(ESCKEY))
	    {
	      qreset() ;
	      break ;
	    }
	  qreset() ;
	}
    }
  if (index == 0)
    num = -1 ;
  return num ;
}

iload(int num, char str[])
{
  int i, n ;

  for (i = 0; i < 4; i++)
    str[i] = ' ' ;
  str[4] = '\0' ;

  n = num ;
  i = 3 ;
  while (n > 0 && i >= 0)
    {
      str[i] = n % 10 + '0' ;
      i-- ;
      n /= 10 ;
    }
}

hline(x1, y1, x2, y2, icol)
int x1, y1, x2, y2, icol ;
{
  int v1, h1 ;

  c3f(cvec[icol]) ;
  v1 = (25 - x1) * 16 - 8 ;
  h1 = (y1 - 1) * 9 ;
  move2i(h1, v1) ;
  v1 = (25 - x2) * 16 - 8 ;
  h1 = (y2 - 1) * 9 ;
  draw2i(h1, v1) ;
}

/***********************************************************************
     att = 0     normal display.
     att = 1     display the string and under line.
 ***********************************************************************/
stpos (str, row, col, icol, att)
char str[] ;
int row, col, icol, att ;
{
  int h, h1, v ;

  v = (25 - row) * 16 - 8 ;
  h = col * 9 ;
  c3f(cvec[icol]) ;
  cmov2i(h, v) ;
  charstr(str) ;

  if (att == 1)
    {
      h1 = h + strlen(str) * 9 ;
      v -= 4 ;
      move2i(h, v) ;
      draw2i(h1, v) ;
    }
}

def_devices()
{
  int i ;

  for (i = 0; i < 10; i++)
    qdevice(number[i]) ;
  qdevice(RETKEY) ;
  qdevice(ESCKEY) ;
  qdevice(LKEY) ;
  qdevice(SKEY) ;
  qdevice(DELKEY) ;
  qdevice(BACKSPACEKEY) ;
  qdevice(XKEY) ;
  qdevice(YKEY) ;
  qdevice(ZKEY) ;
  qdevice(RKEY) ;
  qdevice(MINUSKEY) ;
}

pr_label()
{
  int nrow, ncol, i, j, nspace, ns, index ;
  char str[5] ;

  ncol = nlabel / 10 ;
  if ((nlabel % 10) != 0)
    ncol++ ;

  nrow = nlabel / ncol ;
  if ((nlabel % ncol) != 0)
    nrow++ ;

  nspace = (80 - ncol * 4) / (ncol + 1) ;
  index = ns = 0 ;
 
  for (i = 0; i < ncol; i++)
    {
      ns += nspace ;
      for (j = 0; j < nrow; j++)
	{
	  if (index >= nlabel) break ;
	  iload(plabel[index], str) ;
	  stpos(str, 7 + j, ns, 12, 0) ;
	  index++ ;
	}
      ns += 4 ;
    }
}

int get_index (int nlabel1)
{
  int i ;

  for (i = 0; i < nlabel; i++)
    if (nlabel1 == plabel[i])
      return i ;
  return -1 ;
}

pr_head_label()
{
  char *str ;

  str = "CONCORDIA UNIVERSITY" ;
  stpos(str, 1, 1, 0, 0) ;
  str = "(c)Copyright 1990" ;
  stpos(str, 2, 1, 0, 0) ;
  str = "version 1.0" ;
  stpos(str, 1, 68, 0, 0) ;
  str = "PENDULA 3" ;
  stpos(str, 2, 35, 1, 0) ;

  hline(3, 1, 3, 81, 20) ;
  str = "Labels" ;
  stpos(str, 5, 37, 21, 1) ;
  hline(22, 1, 22, 81, 20) ;
}

get_label()
{
  int vindex, nlabel ;
  char *str;
  char str1[5] ;

  open_gl2() ;
  pr_head_label() ;
  pr_label() ;

  str = "Label default is: " ;
  stpos(str, 18, 29, 21, 0) ;
  iload(cur_label, str1) ;
  stpos(str1, 18, 47, 0, 0) ;

  str = "Please enter index number: " ;
  stpos(str, 19, 29, 1, 0) ;
  nlabel= get_num(19, 57, 12) ;
  str = "Error input, hit <RETURN> to continue..." ;
  if (nlabel != -1)
    {
      vindex = get_index(nlabel) ;
      if (vindex == -1)
	pr_error(str) ;
      else if (cur_label != plabel[vindex])
	{
	  id_label = vindex ;
	  cur_label = plabel[vindex] ;
	}
    }
  close_gl2() ;
}

error_file (int code)
{
  char *str ;

  if (code == 1)
    str = "Error, file is not found, please sheck it again." ;
  else if (code == 2)
    str = "Error, number of points <= 0\n" ;
  else if (code == 3)
    str = "Warning, number of labels > 200." ;
  else if (code == 4)
    str = "Error in data input file, please check it again." ;
  else if (code == 5)
    str = "Error, empty input file." ;

  printf(" %s\n", str) ;
  if (code == 1 || code == 4 || code == 5)
    exit(1) ;
}

check_input_file(argc, argv)
int argc ;
char **argv ;
{
  int error ;

  check_command(argc, argv) ;
  read_data(argv, &error) ;
  if (error)
    error_file(error) ;

  store_data(argv) ;
  id_label = 0 ;
  cur_label = plabel[0] ;
}

get_key (p1, p2, code, active, i, angle)
Matrix p1, p2 ;
int *code, *active, *i ;
float *angle ;
{
  int l ;
  float a ;

  if (getbutton(ESCKEY) || getbutton(RETKEY))
    *code = -1 ;
  else if (getbutton(LKEY))
    {
      l = cur_label ;
      get_label() ;
      if (l != cur_label)
	*i = -1 ;
    }
  else if (getbutton(SKEY))
    *active = 0 ;
  else if (getbutton(MINUSKEY))
    {
      *angle = - *angle ;
      if (*code > 0)
	{
	  *active = 1 ;
	  transformation(p2, *angle, *code) ;
	}
    }
  else if (getbutton(RKEY))
    {
      a = PI / 6.0 ;
      transformation(p1, a, 2) ;
      *active = 0 ;
      if (*angle < 0.0)
	*angle = - *angle ;
    }
  else if (getbutton(XKEY))
    {
      *code = 1 ;
      *active = 1 ;
      transformation(p2, *angle, *code) ;
    }
  else if (getbutton(YKEY))
    {
      *code = 2 ;
      *active = 1 ;
      transformation(p2, *angle, *code) ;
    }
  else if (getbutton(ZKEY))
    {
      *code = 3 ;
      *active = 1 ;
      transformation(p2, *angle, *code) ;
    }
  qreset() ;
}


/*******************        MAIN PROGRAM       **************************/
main (argc, argv)
int argc ;
char **argv ;
{
  int i, code, active, n ;
  float a, angle, r ;
  Matrix p1, p2 ;

  PI = acos(-1.0) ;
  check_input_file(argc, argv) ;
  angle = PI / 180.0 ;
  a = PI / 6.0 ;
  create_pendula() ;
  open_gl() ;
  def_devices() ;
  transformation(p1, a, 2) ;
  i = -1 ;
  code = active = 0 ;
  r = 0.25 ;

  while (TRUE)
    {
      if (qtest())
	{
	  get_key(p1, p2, &code, &active, &i, &angle) ;
	  if (code < 0)
	    break ;
	}
      i = (i + 1) % ppoint[id_label] ;
      n = i + pindex[id_label] ;
      if (active)
	multma(p1, p2) ;

      cpack(0) ;
      clear() ;
      zclear() ;
      pushmatrix() ;
      multmatrix(p1) ;
      backface(TRUE) ;
      pushmatrix() ;
        rot(dpendula[n][1], 'x') ;
        translate(r, 0.0, 0.0) ;
        lmbind(MATERIAL, 1) ;
        draw_cylinder() ;
        lmbind(MATERIAL, 4) ;
        draw_bar() ;
      popmatrix() ;

      pushmatrix() ;
        rot(dpendula[n][0], 'x') ;
        translate(-r, 0.0, 0.0) ;
        lmbind(MATERIAL, 2) ;
        draw_cylinder() ;
        lmbind(MATERIAL, 5) ;
        draw_bar() ;
      popmatrix() ;
      backface(FALSE) ;
        lmbind(MATERIAL, 3) ;
        draw_band(dpendula[n][0], dpendula[n][1]) ;
      popmatrix() ;
      swapbuffers() ;
    }
  close_gl() ;
  free_data() ;
}
