/*
  -------------------------------------------------------------------
  
  Copyright (C) 2006-2025, Andrew W. Steiner
  
  This file is part of O2scl.
  
  O2scl is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.
  
  O2scl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with O2scl. If not, see <http://www.gnu.org/licenses/>.

  -------------------------------------------------------------------
*/
/** \file inte_adapt_cern.h
    \brief File defining \ref o2scl::inte_adapt_cern
*/
#ifndef O2SCL_CERN_ADAPT_H
#define O2SCL_CERN_ADAPT_H

#include <o2scl/misc.h>
#include <o2scl/inte.h>
#include <o2scl/inte_gauss56_cern.h>
#include <o2scl/string_conv.h>
#include <o2scl/vector_derint.h>
 
#ifndef DOXYGEN_NO_O2NS
namespace o2scl {
#endif

#ifdef O2SCL_NEVER_DEFINED

  // AWS 10/8/19: I think these are unnecessary now, so I'm
  // removing them with the new ifdef given above.
  
  /** \brief A simple precision-agnostic Newton-Cotes integrator 

      \note Experimental.
  */
  template<class func_t=funct, class fp_t=double>
    class inte_newton_cotes : public inte<func_t,fp_t> {

  public:
  
  /** \brief Integrate function \c func from \c a to \c b
      giving result \c res and error \c err
  */
  virtual int integ_err(func_t &func, fp_t a, fp_t b,
			fp_t &res, fp_t &err) {
    
    std::vector<fp_t> x(8), y(8);
    fp_t seven=7;
    fp_t dx=b-a;
    dx/=seven;
    for(size_t i=0;i<8;i++) {
      x[i]=((fp_t)i)*dx+a;
      y[i]=func(x[i]);
    }
    res=o2scl::vector_integ_extended8<std::vector<fp_t>,
    fp_t>(8,y)*dx;
    fp_t res2=o2scl::vector_integ_extended4<std::vector<fp_t>,
    fp_t>(8,y)*dx;
    err=fabs(res2-res);

    return 0;
  }
  
  };
  
  /** \brief A simple precision-agnostic Newton-Cotes integrator 

      \note Experimental.
  */
  template<class func_t=funct, class fp_t=double>
    class inte_newton_cotes2 : public inte<func_t,fp_t> {

  public:
  
  /** \brief Integrate function \c func from \c a to \c b
      giving result \c res and error \c err
  */
  virtual int integ_err(func_t &func, fp_t a, fp_t b,
			fp_t &res, fp_t &err) {

    std::vector<fp_t> x(11), y(11);
    fp_t ten=10;
    fp_t dx=b-a;
    dx/=ten;
    for(size_t i=0;i<11;i++) {
      x[i]=((fp_t)i)*dx+a;
      y[i]=func(x[i]);
    }
    fp_t prenum=5;
    fp_t preden=299376;
    fp_t c1=16067;
    fp_t c2=106300;
    fp_t c3=48525;
    fp_t c4=272400;
    fp_t c5=260550;
    fp_t c6=427368;
    res=dx*prenum/preden*(c1*(y[0]+y[10])+
			  c2*(y[1]+y[9])-
			  c3*(y[2]+y[8])+
			  c4*(y[3]+y[7])-
			  c5*(y[4]+y[6])+
			  c6*y[5]);
    fp_t nine=9;
    fp_t dx2=b-a;
    dx2/=nine;
    for(size_t i=0;i<10;i++) {
      x[i]=((fp_t)i)*dx2+a;
      y[i]=func(x[i]);
    }
    prenum=9;
    preden=89600;
    c1=2857;
    c2=15741;
    c3=1080;
    c4=19344;
    c5=5778;
    fp_t res2=dx2*prenum/preden*(c1*(y[0]+y[9])+
				 c2*(y[1]+y[8])+
				 c3*(y[2]+y[7])+
				 c4*(y[3]+y[6])+
				 c5*(y[4]+y[5]));
    err=fabs(res2-res);

    return 0;
  }
  
  };
  
  /** \brief A simple precision-agnostic Newton-Cotes integrator 

      \note Experimental.
  */
  template<class func_t=funct, class fp_t=double>
    class inte_newton_cotes_open : public inte<func_t,fp_t> {

  public:
  
  /** \brief Integrate function \c func from \c a to \c b
      giving result \c res and error \c err
  */
  virtual int integ_err(func_t &func, fp_t a, fp_t b,
			fp_t &res, fp_t &err) {
    
    std::vector<fp_t> x(7), y(7);
    fp_t eight=8;
    fp_t dx=b-a;
    dx/=eight;
    //std::cout << a << " " << b << std::endl;
    for(size_t i=0;i<7;i++) {
      x[i]=((fp_t)i+1)*dx+a;
      y[i]=func(x[i]);
      //std::cout << x[i] << " " << y[i] << std::endl;
    }
    fp_t prenum=8;
    fp_t preden=945;
    fp_t c1=460;
    fp_t c2=-954;
    fp_t c3=2196;
    fp_t c4=-2459;
    res=dx*prenum/preden*(c1*y[0]+c2*y[1]+c3*y[2]+c4*y[3]+
			  c3*y[4]+c2*y[5]+c1*y[6]);
    //std::cout << res << std::endl;
    fp_t seven=7;
    fp_t dx2=b-a;
    dx2/=seven;
    for(size_t i=0;i<6;i++) {
      x[i]=((fp_t)i+1)*dx2+a;
      y[i]=func(x[i]);
      //std::cout << x[i] << " " << y[i] << std::endl;
    }
    prenum=7;
    preden=1440;
    c1=611;
    c2=-453;
    c3=562;
    fp_t res2=dx2*prenum/preden*(c1*(y[0]+y[5])+
				 c2*(y[1]+y[4])+
				 c3*(y[2]+y[3]));
    //std::cout << res2 << std::endl;
    //exit(-1);
    err=fabs(res2-res);

    return 0;
  }
  
  };
  
#endif
  
  /** \brief Adaptive integration (CERNLIB)
    
      Uses a base integration object (default is \ref
      inte_gauss56_cern) to perform adaptive integration by
      automatically subdividing the integration interval. At each
      step, the interval with the largest absolute uncertainty is
      divided in half. The routine succeeds if the absolute tolerance
      is less than \ref tol_abs or if the relative tolerance is less
      than \ref tol_rel, i.e.
      \f[
      \mathrm{err}\leq\mathrm{tol\_abs}~\mathrm{or}~
      \mathrm{err}\leq\mathrm{tol\_rel}\cdot|I|
      \f]
      where \f$ I \f$ is the current estimate for the integral and \f$
      \mathrm{err} \f$ is the current estimate for the uncertainty. If
      the number of subdivisions exceeds the template parameter \c
      nsub, the error handler is called, since the integration may not
      have been successful. The number of subdivisions used in the
      last integration can be obtained from get_nsubdivisions().

      The template parameter \c nsub, is the maximum number of
      subdivisions. It is automatically set to 100 in the original
      CERNLIB routine, and defaults to 100 here. The default base
      integration object is of type \ref inte_gauss56_cern. This is the
      CERNLIB default, but can be modified by calling set_inte().

      This class is based on the CERNLIB routines RADAPT and
      DADAPT which are documented at
      http://wwwasdoc.web.cern.ch/wwwasdoc/shortwrupsdir/d102/top.html
      
      \future 
      - Allow user to set the initial subdivisions?
      - It might be interesting to directly compare the performance
      of this class to \ref o2scl::inte_qag_gsl .
      - There is a fixme entry in the code which could be resolved.
      - Output the point where most subdividing was required?
  */
  template<class func_t=funct,
    class def_inte_t=inte_gauss56_cern<funct,double,
    inte_gauss56_coeffs_double>,
    size_t nsub=100, class fp_t=double>
    class inte_adapt_cern : public inte<func_t,fp_t> {

#ifndef DOXYGEN_INTERNAL

  protected:

  /// Lower end of subdivision
  fp_t xlo[nsub];

  /// High end of subdivision
  fp_t xhi[nsub];

  /// Value of integral for subdivision
  fp_t tval[nsub];

  /// Squared error for subdivision
  fp_t ters[nsub];
      
  /// Previous number of subdivisions
  int prev_subdiv;

  /// The base integration object
  inte<func_t,fp_t> *it;
      
#endif
      
  public:
  
  inte_adapt_cern() {
    nsubdiv=1;
    prev_subdiv=0;

    it=&def_inte;
  }

  /// \name Basic usage
  //@{
  /** \brief Integrate function \c func from \c a to \c b
      giving result \c res and error \c err
  */
  virtual int integ_err(func_t &func, fp_t a, fp_t b,
			fp_t &res, fp_t &err) {
	
    fp_t tvals=0.0, terss, xlob, xhib, yhib=0.0, te, root=0.0;
    int i, nsubdivd;
    fp_t two=2.0;

    if (nsubdiv==0) {
      if (prev_subdiv==0) {
	// If the previous binning was requested, but
	// there is no previous binning stored, then
	// just shift to automatic binning
	nsubdivd=1;
      } else {
	tvals=0.0;
	terss=0.0;
	for(i=0;i<prev_subdiv;i++) {
	  it->integ_err(func,xlo[i],xhi[i],tval[i],te);
	  ters[i]=te*te;
	  tvals+=tval[i];
	  terss+=ters[i];
	}
	err=sqrt(two*terss);
	res=tvals;
	return 0;
      }
    }
  
    // Ensure we're not asking for too many divisions
    if (nsub<nsubdiv) {
      nsubdivd=nsub;
    } else {
      nsubdivd=nsubdiv;
    }

    // Compute the initial set of intervals and integral values
    xhib=a;
    fp_t bin=(b-a)/((fp_t)nsubdivd);
    for(i=0;i<nsubdivd;i++) {
      xlo[i]=xhib;
      xlob=xlo[i];
      xhi[i]=xhib+bin;
      if (i==nsubdivd-1) xhi[i]=b;
      xhib=xhi[i];
      it->integ_err(func,xlob,xhib,tval[i],te);
      ters[i]=te*te;
    }
    prev_subdiv=nsubdivd;

    for(size_t iter=1;iter<=nsub;iter++) {

      // Compute the total value of the integrand
      // and the squared uncertainty
      tvals=tval[0];
      terss=ters[0];
      for(i=1;i<prev_subdiv;i++) {
	tvals+=tval[i];
	terss+=ters[i];
      }
	  
      // Output iteration information
      if (this->verbose>0) {
	std::cout << "inte_adapt_cern Iter: " << iter;
	std::cout.setf(std::ios::showpos);
	std::cout << " Res: " << tvals;
	std::cout.unsetf(std::ios::showpos);
	std::cout << " Err: " << sqrt(two*terss);
	if (this->tol_abs>this->tol_rel*abs(tvals)) {
	  std::cout << " Tol: " << this->tol_abs << std::endl;
	} else {
	  std::cout << " Tol: " << this->tol_rel*abs(tvals)
		    << std::endl;
	}
	if (this->verbose>1) {
	  char ch;
	  std::cout << "Press a key and type enter to continue. " ;
	  std::cin >> ch;
	}
      }

      // See if we're finished
      root=sqrt(two*terss);
      if (root<=this->tol_abs || root<=this->tol_rel*abs(tvals)) {
	res=tvals;
	err=root;
	this->last_iter=iter;
	return 0;
      }

      // Test if we've run out of intervals
      if (prev_subdiv==nsub) {
	res=tvals;
	err=root;
	this->last_iter=iter;
	std::string s="Reached maximum number ("+itos(nsub)+
	  ") of subdivisions in inte_adapt_cern::integ_err().";
	O2SCL_CONV_RET(s.c_str(),exc_etable,this->err_nonconv);
      }

      // Find the subdivision with the largest error
      fp_t bige=ters[0];
      int ibig=0;
      for(i=1;i<prev_subdiv;i++) {
	if (ters[i]>bige) {
	  bige=ters[i];
	  ibig=i;
	}
      }

      // Subdivide that subdivision further
      xhi[prev_subdiv]=xhi[ibig];
      fp_t xnew=(xlo[ibig]+xhi[ibig])/two;
      xhi[ibig]=xnew;
      xlo[prev_subdiv]=xnew;
      it->integ_err(func,xlo[ibig],xhi[ibig],tval[ibig],te);
      ters[ibig]=te*te;
      it->integ_err(func,xlo[prev_subdiv],
		    xhi[prev_subdiv],tval[prev_subdiv],te);
      ters[prev_subdiv]=te*te;
      prev_subdiv++;

    }

    // FIXME: Should we set an error here, or does this
    // only happen if we happen to need exactly nsub
    // intervals?
    res=tvals;
    err=root;
    return 0;
  }
  //@}

  /// \name Integration object
  //@{
  /// Set the base integration object to use
  int set_inte(inte<func_t,fp_t> &i) {
    it=&i;
    return 0;
  }
      
  /// Default integration object
  def_inte_t def_inte;
  //@}
      
  /// \name Subdivisions
  //@{
  /** \brief Number of subdivisions 

      The options are
      - 0: Use previous binning and do not subdivide further \n
      - 1: Automatic - adapt until tolerance is attained (default) \n
      - n: (n>1) split first in n equal subdivisions, then adapt
      until tolerance is obtained.
  */
  size_t nsubdiv;

  /// Return the number of subdivisions used in the last integration
  size_t get_nsubdivisions() {
    return prev_subdiv;
  }

  /// Return the ith subdivision
  int get_ith_subdivision(size_t i, fp_t &xlow, fp_t &xhigh, 
			  fp_t &value, fp_t &errsq) {
    if (i<prev_subdiv) {
      xlow=xlo[i];
      xhigh=xhi[i];
      value=tval[i];
      errsq=ters[i];
    }
    return 0;
  }
      
  /// Return all of the subdivisions
  template<class vec_t> 
  int get_subdivisions(vec_t &xlow, vec_t &xhigh, vec_t &value, 
		       vec_t &errsq) {

    for(int i=0;i<prev_subdiv;i++) {
      xlow[i]=xlo[i];
      xhigh[i]=xhi[i];
      value[i]=tval[i];
      errsq[i]=ters[i];
    }
    return 0;
  }
  //@}

  };

#ifdef O2SCL_NEVER_DEFINED

  /** \brief An experimental adaptive integrator from 0 to \$ \infty \f$
      based on \ref o2scl::inte_adapt_cern

      (This class is now replaced by inte_il in inte.h)
  */
  template<class func_t=funct, 
    class def_inte_t=inte_gauss56_cern<funct,double,
    inte_gauss56_coeffs_double>,
    size_t nsub=100,
    class fp_t=double>
    class inte_qagil_cern : public inte<func_t,fp_t> {
    
  protected:

  /// A pointer to the user-specified function
  func_t *user_func;
  
  /// The upper limit
  fp_t upper_limit;

  /// Transform to \f$ t \in (0,1] \f$
  virtual fp_t transform(fp_t t) {
    fp_t x=upper_limit-(1-t)/t, y;
    y=(*user_func)(x);
    /*
      if (false) {
      std::cout << upper_limit << " " << t << " " << y/t/t << std::endl;
      char ch;
      std::cin >> ch;
      }
    */
    return y/t/t;
  }

  public:

  inte_qagil_cern() {
    it=&def_inte;
    fo=std::bind(std::mem_fn<fp_t(fp_t)>(&inte_qagil_cern::transform),
		 this,std::placeholders::_1);
  }    
  
  /** \brief Internal function type based on floating-point type

      \comment 
      This type must be public so the user can change the
      base integration object
      \endcomment
  */
  typedef std::function<fp_t(fp_t)> internal_funct;

  protected:

  /// The base integration object
  inte<internal_funct,fp_t> *it;
  
  /// Function object
  internal_funct fo;
  
  public:  
  
  /** \brief Integrate function \c func from \c a to \c b
      giving result \c res and error \c err
  */
  virtual int integ_err(func_t &func, fp_t a, fp_t b,
			fp_t &res, fp_t &err) {
    user_func=&func;
    upper_limit=b;
    int ret=it->integ_err(fo,0.0,1.0,res,err);
    return ret;
  }
  
  /// \name Integration object
  //@{
  /// Set the base integration object to use
  int set_inte(inte<internal_funct,fp_t> &i) {
    it=&i;
    return 0;
  }
      
  /// Default integration object
  inte_adapt_cern<internal_funct,def_inte_t,nsub,fp_t> def_inte;
  //@}

  };

#endif
  
#ifndef DOXYGEN_NO_O2NS
}
#endif

#endif
