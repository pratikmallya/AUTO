#include <stdio.h>
#include <auto_f2c.h>
#include <auto_c.h>

int main(int argc, char *argv[]) {

  FILE *fpin, *fpout;
  int ibr,ntot,itp,lab,nfpr,isw,ntpl,nar,nrowpr,ntst,ncol,npar1;
  int i,j;

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


  fscanf(fpin,"%d %d %d %d %d %d %d %d %d %d %d %d",
	 &ibr,&ntot,&itp,&lab,&nfpr,&isw,&ntpl,&nar,
	 &nrowpr,&ntst,&ncol,&npar1);
  while(!feof(fpin)) {
    if(ntst == 0) {
      doublereal tmp;
      fprintf(fpout,"%5d%5d%5d%5d%5d%5d%5d%5d%7d%5d%5d%5d\n",
	      ibr,ntot,itp,lab,nfpr,isw,ntpl,nar,
	      nrowpr,ntst,ncol,npar1);
      /* write out first column */
      fscanf(fpin,"%lf", &tmp);
      fprintf(fpout,"    %18.10E",tmp);
      /* write out rest of columns */
      for(i=0;i<nar - 1;i++) {
	fscanf(fpin,"%lf", &tmp);
	if(i % 7 ==0 && i != 0)
	  fprintf(fpout,"\n    ");
	fprintf(fpout,"%18.10E",tmp);
      }	
      fprintf(fpout,"\n    ");
      /* write out the parameters*/
      for(i=0;i<npar1;i++) {
	fscanf(fpin,"%lf", &tmp);
	if(i % 7 ==0 && i != 0)
	  fprintf(fpout,"\n    ");
	fprintf(fpout,"%18.10E",tmp);
      }	
      fprintf(fpout,"\n");
    } else {
      doublereal *tm;
      doublereal *u;
      doublereal tmp;
      integer itmp;
      integer u_dim1;

      tm=(doublereal *)malloc(sizeof(doublereal)*ntpl);
      u=(doublereal *)malloc(sizeof(doublereal)*ntpl*(nar-1));
      u_dim1 = nar - 1;

      fprintf(fpout,"%5d%5d%5d%5d%5d%5d%5d%5d%7d%5d%5d%5d\n",
	      ibr,ntot,itp,lab,nfpr,isw,ntpl*3-2,nar,
	      nrowpr+4*ntpl-4,ntst*3,ncol,npar1);
      for(j=0;j<ntpl;j++) {
	/* write out first column */
	fscanf(fpin,"%lf", &tm[j]);
	fprintf(fpout,"    %18.10E",tm[j]/3.0);
	/* write out rest of columns */
	for(i=0;i<nar - 1;i++) {
	  fscanf(fpin,"%lf", &ARRAY2D(u,i,j));
	  if(i % 7 ==0 && i != 0)
	    fprintf(fpout,"\n    ");
	  fprintf(fpout,"%18.10E",ARRAY2D(u,i,j));
	}	
	fprintf(fpout,"\n");
      }
      for(j=1;j<ntpl;j++) {
	/* write out first column */
	fprintf(fpout,"    %18.10E",(1.0+tm[j])/3.0);
	/* write out rest of columns */
	for(i=0;i<nar - 1;i++) {
	  if(i % 7 ==0 && i != 0)
	    fprintf(fpout,"\n    ");
	  fprintf(fpout,"%18.10E",ARRAY2D(u,i,j) + ARRAY2D(u,i,ntpl-1) - ARRAY2D(u,i,0));
	}	
	fprintf(fpout,"\n");
      }

      for(j=1;j<ntpl;j++) {
	/* write out first column */
	fprintf(fpout,"    %18.10E",(2.0+tm[j])/3.0);
	/* write out rest of columns */
	for(i=0;i<nar - 1;i++) {
	  if(i % 7 ==0 && i != 0)
	    fprintf(fpout,"\n    ");
	  fprintf(fpout,"%18.10E",ARRAY2D(u,i,j) + 2.0*(ARRAY2D(u,i,ntpl-1) - ARRAY2D(u,i,0)));
	}	
	fprintf(fpout,"\n");
      }

      /* write out ICP*/
      for(i=0;i<nfpr;i++) {
	fscanf(fpin,"%ld", &itmp);
	if(i % 7 ==0 && i != 0)
	  fprintf(fpout,"\n    ");
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
      fprintf(fpout,"\n    ");
#ifdef ORIG
#define OFFSET 2
#else 
#define OFFSET 1
#endif
      for(j=0;j<ntpl;j++) {
	/* write out rest of columns */
	for(i=0;i<nar - OFFSET;i++) {
	  fscanf(fpin,"%lf", &ARRAY2D(u,i,j));
	  if(i % 7 ==0 && i != 0)
	    fprintf(fpout,"\n    ");
	  fprintf(fpout,"%18.10E",ARRAY2D(u,i,j));
	}	
	/* go to the end of line*/
	while(fgetc(fpin)!='\n');
	fprintf(fpout,"\n    ");
      }
      for(j=1;j<ntpl;j++) {
	/* write out rest of columns */
	for(i=0;i<nar - OFFSET;i++) {
	  if(i % 7 ==0 && i != 0)
	    fprintf(fpout,"\n    ");
	  fprintf(fpout,"%18.10E",ARRAY2D(u,i,j));
	}	
	fprintf(fpout,"\n    ");
      }

      for(j=1;j<ntpl;j++) {
	/* write out rest of columns */
	for(i=0;i<nar - OFFSET;i++) {
	  if(i % 7 ==0 && i != 0)
	    fprintf(fpout,"\n    ");
	  fprintf(fpout,"%18.10E",ARRAY2D(u,i,j));
	}	
	fprintf(fpout,"\n    ");
      }

      /* write out the parameters*/
      for(i=0;i<npar1;i++) {
	fscanf(fpin,"%lf", &tmp);
	if(i % 7 ==0 && i != 0)
	  fprintf(fpout,"\n    ");
	if(i==10)
	  fprintf(fpout,"%18.10E",tmp*3.0);
	else
	  fprintf(fpout,"%18.10E",tmp);
      }	
      fprintf(fpout,"\n");
      free(tm);
      free(u);

    }
    fscanf(fpin,"%d %d %d %d %d %d %d %d %d %d %d %d",
	   &ibr,&ntot,&itp,&lab,&nfpr,&isw,&ntpl,&nar,
	   &nrowpr,&ntst,&ncol,&npar1);
  }

  return 0;
}


