#include <stdio.h>
#include <auto_f2c.h>
#include <auto_c.h>

int main(int argc, char *argv[]) {

  FILE *fpin, *fpout;
  int ibr,ntot,itp,lab,nfpr,isw,ntpl,nar,nrowpr,ntst,ncol;
  int i,j,val;
  int icp[NPARX];
  doublereal tmp;

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

  val = fscanf(fpin,"%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d",
	       &ibr,&ntot,&itp,&lab,&nfpr,&isw,&ntpl,&nar,
	       &nrowpr,&ntst,&ncol);

  for(i=0;i<nfpr;i++)
    fscanf(fpin,"%d",&icp[i]);

  while(!feof(fpin)) {
    if(ntst != 0) 
      nrowpr = nrowpr + (nfpr+19)/20;

    nrowpr = nrowpr + (NPARX-1)/7 - 2;
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
	fprintf(fpout,"%5d",icp[i]);
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
    for(i=0;i<20;i++) {
      fscanf(fpin,"%lf", &tmp);
      if(i % 7 ==0 && i != 0)
	fprintf(fpout,"\n    ");
      fprintf(fpout,"%18.10E",tmp);
    }	
    for(i=20;i<NPARX;i++) {
      if(i % 7 ==0 && i != 0)
	fprintf(fpout,"\n    ");
      fprintf(fpout,"%18.10E",0.0);
    }	
    fprintf(fpout,"\n");

    fscanf(fpin,"%d %d %d %d %d %d %d %d %d %d %d",
	   &ibr,&ntot,&itp,&lab,&nfpr,&isw,&ntpl,&nar,
	   &nrowpr,&ntst,&ncol);
    for(i=0;i<nfpr;i++)
      fscanf(fpin,"%d",&icp[i]);

  }
  return 0;

}


