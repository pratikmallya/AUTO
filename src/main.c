
#include "auto_f2c.h"
#include "auto_c.h"

#include <unistd.h> /* for getopt */

FILE *fp3;
FILE *fp7;
FILE *fp9;
FILE *fp12;
int global_conpar_type=CONPAR_DEFAULT;
int global_setubv_type=SETUBV_DEFAULT;
int global_reduce_type=REDUCE_DEFAULT;
int global_num_procs=1;
int global_verbose_flag=0;

#ifdef FLOATING_POINT_TRAP
#if defined(__GLIBC__) && (__GLIBC__ == 2) && (__GLIBC_MINOR__ < 2)
#include <fpu_control.h>
/* This is a x86 specific function only used for debugging.
   It turns on various floating point traps.  */
static void trapfpe(void)
{
  fpu_control_t traps;
  traps = _FPU_DEFAULT & (~(_FPU_MASK_IM | _FPU_MASK_ZM | _FPU_MASK_OM));
  _FPU_SETCW(traps);
}
#else
#define _GNU_SOURCE 1
#define __USE_GNU 1
#include <fenv.h>
/* this trapfpe variety is slightly more portable */
static void trapfpe(void)
{
  feenableexcept(FE_INVALID|FE_DIVBYZERO|FE_OVERFLOW);
}
#endif
#endif

static void options(void){
  printf("-v:    Give verbose output.\n");
  printf("-m:    Use the Message Passing Interface library for parallelization.\n");
  printf("-t:    Use the Pthreads library for parallelization.\n");
  printf("       This option takes one of three arguements.\n"); 
  printf("       'conpar' parallelizes the condensation of parameters routine.\n");
  printf("       'setubv' parallelizes the jacobian setup routine.\n");
  printf("       'reduce' parallelizes the nested dissection routine.\n");
  printf("       'all'    parallelizes all routines.\n");
  printf("       In general the recommeneded option is 'all'.\n");
  printf("-#:    The number of processing units to use (currently only used with the -t option)\n");
}

static void scheme_not_supported_error(char *scheme) {
  printf("'%s' not available in this binary\n",scheme);
  printf("Support for '%s' needs to be included at compile time\n",scheme);
  abort();
}

int main (int argc,char *argv[])
{
#ifdef HAVE_GETTIMEOFDAY
  struct timeval  *time0,*time1;
#else
  clock_t time0, time1;
#endif
  doublereal par[NPARX2];
  doublereal *thu;
  void *thl;
  integer *iuz, *icu, *icp;
  doublereal *vuz;
  iap_type iap;
  rap_type rap;
  function_list list;

#ifdef USAGE
  struct rusage *init_usage,*total_usage;
  usage_start(&init_usage);
  usage_start(&total_usage);
#endif

#ifdef FLOATING_POINT_TRAP
  trapfpe();
#endif

#ifdef MPI
  MPI_Init(&argc,&argv);
#endif

  fp3 = fopen("fort.3","r");
  if(fp3 == NULL) {
    fprintf(stderr,"Error:  Could not open fort.3\n");
    abort();
  }
  fp7 = fopen("fort.7","w");
  if(fp7 == NULL) {
    fprintf(stderr,"Error:  Could not open fort.7\n");
    abort();
  }
  fp9 = fopen("fort.9","w");
  if(fp9 == NULL) {
    fprintf(stderr,"Error:  Could not open fort.9\n");
    abort();
  }
  {
    int c;
    while (1)
      {
	c = getopt(argc, argv, "mt:?#:v");
	if (c == -1)
	  break;
	switch (c){
	case 'v':
	  global_verbose_flag=1;
	  break;
	case 'm':
#ifdef MPI
	  global_conpar_type = CONPAR_MPI;
	  global_setubv_type = SETUBV_MPI;
	  break;
#endif
	  scheme_not_supported_error("mpi");
	  break;
	case 't':
#ifdef PTHREADS
	  if(strcmp(optarg,"setubv")==0) {
	    global_setubv_type = SETUBV_PTHREADS;
	  }
	  else if(strcmp(optarg,"conpar")==0) {
	    global_conpar_type = CONPAR_PTHREADS;
	  }
	  else if(strcmp(optarg,"reduce")==0) {
	    global_conpar_type = REDUCE_PTHREADS;
	  }
	  else if(strcmp(optarg,"all")==0) {
	    global_conpar_type = CONPAR_PTHREADS;
	    global_setubv_type = SETUBV_PTHREADS;
	    global_reduce_type = REDUCE_PTHREADS;
	  }
	  else {
	    fprintf(stderr,"Unknown type for threads '%s'.  Using 'all'\n",optarg);
	    global_conpar_type = CONPAR_PTHREADS;
	    global_setubv_type = SETUBV_PTHREADS;
	  }
	  break;
#endif
	  scheme_not_supported_error("threads");
	  break;
	case '#':
	  global_num_procs=atoi(optarg);
	  break;
	case '?':
	  options();
	  abort();
	  break;
	default:
	  printf ("?? getopt returned character code 0%o ??\n", c);
	  options();
	  abort();
	}
      }
      
  }
#ifdef MPI
  {
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int myid,namelen;
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    MPI_Get_processor_name(processor_name,&namelen);
    if(global_verbose_flag) {
      fprintf(stderr,"Process %d on %s with pid %ld\n",
	      myid, processor_name, (long int)getpid());
    }
    if(myid!=0) {
      global_conpar_type = CONPAR_MPI;
      global_setubv_type = SETUBV_MPI;
      mpi_worker();
    }
  }    
#endif    
  /* Initialization : */

  iap.mynode = mynode();
  iap.numnodes = numnodes();
  if (iap.numnodes > 1) {
    iap.parallel_flag = 1;
  } else {
    iap.parallel_flag = 0;
  }


  while(1){
    time_start(&time0);
    time_start(&time1);
    /* NOTE:  thu is allocated inside this function, and the
       pointer is passed back.  I know this is ugly, but
       this function does a bit of work to get thu setup correctly,
       as well as figuring out the size the array should be.
       What really should happen is to have one function which
       reads fort.2 and another fuction which initializes the array.
       That way the allocation could happen between the two calles.
    */
    {
      logical eof;
      /* The final argument is the dimension of the manifold to compute.
	 This main routine only computes 1D manifolds, but this is
	 set to 1, but init can be called from other driver routines
	 (such as MF) to compute higher dimensional manifolds */
      init(&iap, &rap, par, &icu, &thl, &thu, &iuz, &vuz, &eof,1);
      
      if (eof) {
	break;
      }
    }

    /* Find restart label and determine type of restart point. */
    if (iap.irs > 0) {
      logical found = FALSE_;

      findlb(&iap, &rap, iap.irs, &(iap.nfpr), &found);
      if (! found) {
	if (iap.mynode == 0) {
	  fprintf(stderr,"\nRestart label %4ld not found\n",iap.irs);
	}
	abort();
      }
    }
#ifdef MPI
    
    if(global_setubv_type==SETUBV_MPI) {
      /* A few words about what is going on here.  ips, irs, isw, itp, and
	 nfpr are used to choose which functions are used for funi, icni, bcni, etc.
	 unfortunately, their values are changed in init1 and chdim.  In the
	 old version of AUTO the functions were already choosen by the point
	 these values were modified, so there was no problem.  Now, in the
	 message passing parallel version, the workers need both versions, since
	 they both need to select the appropriate functions (using the old values)
	 and actually compute (using the new values).  */
      int comm_size,i;
      integer funi_icni_params[5];
      MPI_Comm_size(MPI_COMM_WORLD,&comm_size);
      funi_icni_params[0]=iap.ips;
      funi_icni_params[1]=iap.irs;
      funi_icni_params[2]=iap.isw;
      funi_icni_params[3]=iap.itp;
      funi_icni_params[4]=iap.nfpr;
      for(i=1;i<comm_size;i++){
	/*Send message to get worker into init mode*/
	{
	  int message=AUTO_MPI_INIT_MESSAGE;
	  MPI_Send(&message,1,MPI_INT,i,0,MPI_COMM_WORLD);
	}
      }
      MPI_Bcast(funi_icni_params,5,MPI_LONG,0,MPI_COMM_WORLD);
    }
#endif
    set_function_pointers(iap,&list);
    init1(&iap, &rap, &icp, &thl, icu, par);
    chdim(&iap);

    /* Create the allocations for the global structures used in 
       autlib3.c and autlib5.c.  These are purely an efficiency thing.
       The allocation and deallocation of these scratch areas takes
       up a nontrivial amount of time if done directly in the
       wrapper functions in autlib3.c*/
    allocate_global_memory(iap);

    /* ---------------------------------------------------------- */
    /* ---------------------------------------------------------- */
    /*  One-parameter continuations */
    /* ---------------------------------------------------------- */
    /* ---------------------------------------------------------- */

#ifdef AUTO_CONSTRUCT_DESTRUCT
    user_construct(argc,argv);
#endif
#ifdef USAGE
    usage_end(init_usage,"main initialization");
#endif
    
    if(list.type==AUTOAE)
      autoae(&iap, &rap, par, icp, icu, list.aelist.funi, list.aelist.stpnt, list.aelist.pvli, thl, thu, iuz, vuz);
    if(list.type==AUTOBV)
      autobv(&iap, &rap, par, icp, icu, list.bvlist.funi, list.bvlist.bcni, 
	     list.bvlist.icni, list.bvlist.stpnt, list.bvlist.pvli, thl, thu, iuz, vuz);

#ifdef USAGE
    usage_end(total_usage,"total");

#endif
    time_end(time0,"Total Time ",fp9);
    fprintf(fp9,"----------------------------------------------");
    fprintf(fp9,"----------------------------------------------\n");
    time_end(time1,"",stdout);
#ifdef AUTO_CONSTRUCT_DESTRUCT
    user_destruct();
#endif


  }
#ifdef MPI
  {
    int message = AUTO_MPI_KILL_MESSAGE;
    int size,i;
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    for(i=1;i<size;i++)
      MPI_Send(&message,1,MPI_INT,i,0,MPI_COMM_WORLD);
  }

  MPI_Finalize();
#endif

  free(thu);
  free(icu);
  free(icp);
  free(iuz);
  free(vuz);
  fclose(fp3);
  fclose(fp7);
  fclose(fp9);
  return 0;
} 




