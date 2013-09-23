#include <stdio.h>
#include <auto_f2c.h>
#include <auto_c.h>

int main(int argc, char *argv[]) {

  FILE *fpin, *fpout;
  int ibr,ntot,itp,lab,nfpr,isw,ntpl,nar,nrowpr,ntst,ncol;
  int i,j;
  doublereal tmp;
  integer itmp;

  fpin = fopen("fort.28","r");
  fpout = fopen("fort.38","w");

  if(fpin == NULL) {
    fprintf(stderr,"Could not open input file fort.28, exitting\n");
    exit(1);
  }

  if(fpout == NULL) {
    fprintf(stderr,"Could not open output file fort.38, exitting\n");
    exit(1);
  }

  fscanf(fpin,"%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d",
	       &ibr,&ntot,&itp,&lab,&nfpr,&isw,&ntpl,&nar,
	       &nrowpr,&ntst,&ncol);

  while(!feof(fpin)) {
    fprintf(fpout,"%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d\n",
	    ibr,ntot,itp,lab,nfpr,isw,ntpl,nar,
	    nrowpr,ntst,ncol,NPARX);
    /* write out ups */
    for(j=0;j<ntpl;j++) {
      fprintf(fpout,"    ");
      for(i=0;i<nar;i++) {
	fscanf(fpin,"%lf", &tmp);
	if(i % 7 ==0 && i != 0)
	  fprintf(fpout,"\n    ");
	fprintf(fpout,"%18.10E",tmp);
      }	
      fprintf(fpout,"\n");
    }

    if(ntst != 0) {
      /* write out ICP*/
      for(i=0;i<nfpr;i++) {
	fscanf(fpin,"%ld", &itmp);
	fprintf(fpout,"%5ld",itmp);
      }	
      fprintf(fpout,"\n    ");

      /* write out RLDOT*/
      for(i=0;i<nfpr;i++) {
	fscanf(fpin,"%lf", &tmp);
	if(i % 7 ==0 && i != 0)
	  fprintf(fpout,"\n    ");
	fprintf(fpout,"%18.10E",tmp);
      }	

      for(j=0;j<ntpl;j++) {
	/* write out UDOTPS */
	fprintf(fpout,"\n    ");
	for(i=0;i<nar-1;i++) {
	  fscanf(fpin,"%lf", &tmp);
	  if(i % 7 ==0 && i != 0)
	    fprintf(fpout,"\n    ");
	  fprintf(fpout,"%18.10E",tmp);
	}	
      }
      fprintf(fpout,"\n    ");
    }
    /* write out the parameters*/
    for(i=0;i<NPARX;i++) {
      fscanf(fpin,"%lf", &tmp);
      if(i % 7 ==0 && i != 0)
	fprintf(fpout,"\n    ");
      fprintf(fpout,"%18.10E",tmp);
    }	
    fprintf(fpout,"\n");

    fscanf(fpin,"%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d",
	   &ibr,&ntot,&itp,&lab,&nfpr,&isw,&ntpl,&nar,
	   &nrowpr,&ntst,&ncol);
  }
  return 0;
}





