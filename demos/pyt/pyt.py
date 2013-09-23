import math

def func(ndim,u,icp,par,ijac,f,dfdu,dfdp):
##    Evaluates the algebraic equations or ODE right hand side 
  
##    Input arguments : 
##          ndim   :   Dimension of the ODE system 
##          u      :   State variables 
##          icp    :   Array indicating the free parameter(s) 
##          par    :   Equation parameters 
  
##    Values to be returned : 
##          f      :   ODE right hand side values 
  
##    Normally unused Jacobian arguments : IJAC, DFDU, DFDP (see manual) 
    e = math.exp(u[1])
    f[0] = -u[0] + par[1] * (1 - u[0]) * e
    f[1] = -u[1] + par[1] * par[2] * (1 - u[0]) * e - par[3] * u[1]
    return

