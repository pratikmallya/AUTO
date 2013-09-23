#include "auto_f2c.h"
#include "Python.h"
#define NPARX 36

/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */
/*   pyt :            test of the Python interface */
/* ---------------------------------------------------------------------- */
/* ---------------------------------------------------------------------- */

static struct {
  PyObject *module;
  PyObject *Pu,*Picp,*Ppar;
  PyObject *Pf,*Pdfdu,*Pdfdp;
  
  
} state = {NULL,
	   NULL,NULL,NULL,
	   NULL,NULL,NULL}; 

int user_construct(int argc, char **argv) {
  Py_SetProgramName(argv[0]);
  Py_Initialize();
  PySys_SetArgv(argc, argv);

  state.module = PyImport_ImportModule("pyt");
  if(PyErr_Occurred() != NULL)
    PyErr_Print();
}

int user_destruct() {
  Py_Finalize();
}

int set_list(PyObject *list, int size, double *data) {
  int i;
  PyObject *tmp=NULL;
  for(i=0;i<size;i++) {
    tmp = PyFloat_FromDouble(data[i]);
    if(tmp != NULL)
      PyList_SetItem(list,i,tmp);
    /* I really want to do this here, but it seems to break the
       code when I do it.  On the other hand, not having it doesn't
       seem to cause a memory leak, so I guess it is ok... */
    //Py_DECREF(tmp);
  }
}

/* Create a list, initialize to 0.0 or the contents of data, if non-NULL, 
   with the list having the only
   reference to the elements (so a Py_DECREF list allows the list and
   the elements to be garbage collected. */
PyObject *make_list(int size,double *data) {
  PyObject *list;
  int i;
  PyObject *tmp=NULL;

  list = PyList_New(size);
  if(list!=NULL) {
    for(i=0;i<size;i++) {
      if(data == NULL)
	tmp = PyFloat_FromDouble(0.0);
      else
	tmp = PyFloat_FromDouble(data[i]);
      if(tmp != NULL)
	PyList_SetItem(list,i,tmp);
      /* I really want to do this here, but it seems to break the
	 code when I do it.  On the other hand, not having it doesn't
	 seem to cause a memory leak, so I guess it is ok... */
      //Py_DECREF(tmp);
    }
  }
  if(PyErr_Occurred() != NULL)
    PyErr_Print();
  return list;
}


int func(integer *ndim, doublereal *u, integer *icp, 
	 doublereal *par, integer ijac, doublereal *f, 
	 doublereal *dfdu, doublereal *dfdp) {
  int i;
  PyObject *Presult;

  PyObject *Pu,*Picp,*Ppar;
  PyObject *Pf,*Pdfdu,*Pdfdp;
  // Pack arrays into Python lists
  if(state.Picp == NULL) {
    Picp = make_list(0,NULL);
    Pdfdu = make_list(0,NULL);
    Pdfdp = make_list(0,NULL);
    Pf = make_list(*ndim,NULL);
    Pu = make_list(*ndim,u);
    Ppar = make_list(NPARX,par);
  } else {
    set_list(Pu,*ndim,u);
    set_list(Ppar,NPARX,par);
  }

  Presult = PyObject_CallMethod(state.module,"func","lOOOlOOO",*ndim,Pu,Picp,Ppar,ijac,Pf,Pdfdu,Pdfdp);
  if(PyErr_Occurred() != NULL)
    PyErr_Print();

  // Unpack Python lists into arrays
  for(i=0;i<*ndim;i++) {
    f[i] = PyFloat_AsDouble(PyList_GetItem(Pf,i));
  }

  Py_DECREF(Presult);
  Py_DECREF(Picp);
  Py_DECREF(Pdfdu);
  Py_DECREF(Pdfdp);
  Py_DECREF(Pf);
  Py_DECREF(Pu);
  Py_DECREF(Ppar);

  if(PyErr_Occurred() != NULL)
    PyErr_Print();
  return 0;
} 


int stpnt(integer *ndim, doublereal *u, doublereal *par) {
  /* Input arguments : */
  /*      ndim   :   Dimension of the ODE system */
  
  /* Values to be returned : */
  /*      u      :   A starting solution vector */
  /*      par    :   The corresponding equation-parameter values */
  
  
  /* Initialize the equation parameters */
  
  par[0] = (doublereal)0.;
  par[1] = (doublereal)14.;
  par[2] = (doublereal)2.;
  
  /* Initialize the solution */
  u[0] = (doublereal)0.;
  u[1] = (doublereal)0.;
  
  return 0;
} 

/* The following subroutines are not used here, */
/* but they must be supplied as dummy routines */

int bcnd() {
  return 0;
} 

int icnd() {
    return 0;
}

int fopt() {
    return 0;
}

int pvls() {
    return 0;
}




