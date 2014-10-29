/*
  -------------------------------------------------------------------
  
  Copyright (C) 2006-2014, Andrew W. Steiner
  
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
/** \file eos_had_skyrme.h
    \brief File defining \ref o2scl::eos_had_skyrme
*/
#ifndef O2SCL_SKYRME_EOS_H
#define O2SCL_SKYRME_EOS_H

#include <iostream>
#include <string>
#include <cmath>

#include <o2scl/constants.h>
#include <o2scl/mroot.h>
#include <o2scl/eos_had_base.h>
#include <o2scl/part.h>
#include <o2scl/fermion_nonrel.h>

#ifndef DOXYGEN_NO_O2NS
namespace o2scl {
#endif

  /** \brief Skyrme hadronic equation of state 

      Equation of state of nucleonic matter based on 
      the Skryme interaction from \ref Skyrme59 .

      \hline
      \b Background:

      The Hamiltonian is defined (using the notation of 
      \ref Steiner05b ) as
      \f[
      {\cal H} = 
      {\cal H}_{k1} +
      {\cal H}_{k2} +
      {\cal H}_{k3} +
      {\cal H}_{p1} +
      {\cal H}_{p2} +
      {\cal H}_{p3} +
      {\cal H}_{g1} +
      {\cal H}_{g2} \, .
      \f]
      
      The kinetic terms are:
      \f[
      {\cal H}_{k1} = \frac{\tau_n}{2 m_n} +
      \frac{\tau_p}{2 m_p} 
      \f]
      \f[
      {\cal H}_{k2} =
      n \left(\tau_n + \tau_p \right) \left[ \frac{t_1}{4} 
      \left( 1 + \frac{x_1}{2} \right)
      + \frac{t_2}{4} \left( 1 + \frac{x_2}{2} \right) \right]
      \f]
      \f[
      {\cal H}_{k3} =
      \left( \tau_n n_n + \tau_p n_p \right) \left[ \frac{t_2}{4} 
      \left( \frac{1}{2} + x_2 \right)
      - \frac{t_1}{4} \left( \frac{1}{2} + x_1 \right) \right]
      \f]
      where \f$ \tau_i \f$ is the Fermi gas energy density
      of particle \f$ i \f$ .
      
      The potential terms are:
      \f[
      {\cal H}_{p1} = 
      \frac{t_0}{2} 
      \left[ \left( 1 + \frac{x_0}{2} \right) n^2 - 
      \left( {\textstyle \frac{1}{2}} + x_0 \right) 
      \left( n_n^2 + n_p^2 \right) \right] 
      \f]
      \f[
      {\cal H}_{p2} = 
      \frac{a t_3}{6} \left[ \left( 1 + \frac{x_3}{2} \right) n^{\alpha} 
      n_n n_p + 2^{\alpha-2} \left(1 - x_3\right)
      \left(n_n^{\alpha+2} + n_p^{\alpha+2}\right) \right] 
      \f]
      \f[
      {\cal H}_{p3} = 
      \frac{b t_3}{12} \left[ \left(1 + \frac{x_3}{2} \right) n^{\alpha+2} -
      \left(\frac{1}{2} + x_3 \right) n^{\alpha} 
      \left( n_n^2+n_p^2 \right) \right]
      \f]
      
      The gradient terms are displayed here for completeness even though
      they are not computed in the code:
      \f[
      {\cal H}_{g1} = 
      \frac{3}{32} \left[ t_1 \left(1 - x_1 \right) - 
      t_2 \left(1 + x_2 \right) \right] \left[ \left( \nabla n_n\right)^2 + 
      \left( \nabla n_p \right)^2 \right] 
      \f]
      \f[
      {\cal H}_{g2} = 
      \frac{1}{8} \left[ 3 t_1 \left( 1 + 
      \frac{x_1}{2} \right) - t_2 \left(1 + \frac{x_2}{2} \right) \right] 
      \nabla n_n \nabla n_p
      \f]

      The values \f$ a=0, b=1 \f$ give the standard definition of the
      Skyrme Hamiltonian \ref Skyrme59, while \f$a=1, b=0\f$ contains
      the modifications suggested by \ref Onsi94.

      The spin-orbit term is (following \ref Steiner05)
      \f[
      {\cal H}_{J} = -\frac{W_0}{2} \left( n_n \vec{\nabla} \cdot 
      \vec{J}_n + n_p \vec{\nabla} \cdot \vec{J}_p + n \vec{\nabla} 
      \cdot \vec{J} \right) + \frac{t_1}{16} \left(\vec{J}_n^2 + 
      \vec{J}_p^2 - x_1 \vec{J}^2\right) - \frac{t_2}{16} 
      \left(\vec{J}_n^2 + \vec{J}_p^2 + x_2 \vec{J}^2\right)
      \f]
      where sometimes the \f$ \vec{J}^2 \f$ terms are not included. 
      Alternatively, one can separate the isoscalar and isovector
      parts in the first term
      \f[
      {\cal H}_{J} = - b_4 n \vec{\nabla} \cdot \vec{J} -
      b_4^{\prime} n_n \vec{\nabla} \cdot \vec{J}_n - 
      b_4^{\prime} n_p \vec{\nabla} \cdot \vec{J}_p
      \f]
      then the earlier Skyrme interactions have \f$ b_4 = 
      b_4^{\prime} = W_0/2 \f$. For example, for SLy4, 
      \f$ b_4 = b_4^{\prime} = W_0/2 = 61.5~\mathrm{MeV} \f$.

      Also, couple useful definitions
      \f[
      t_3^{\prime} = \left(a + b\right) t_3 \, ,
      \f]
      \f[
      C = \frac{3 }{10 m} \left( \frac{3 \pi^2 }{2} \right)^{2/3}  \, ,
      \f]
      and
      \f[
      \beta = \frac{M}{2} \left[ \frac{1}{4} \left( 3 t_1 + 5 t_2 \right) \, .
      + t_2 x_2 \right] \\
      \f]
      
      \hline
      \b Units:

      Quantities which have units containing powers of energy are
      divided by \f$\hbar c\f$ to ensure all quantities are in units
      of \f$ \mathrm{fm} \f$. The \f$x_i\f$ and \f$\alpha\f$ are
      unitless, while the original units of the \f$t_i\f$ are:
      - \f$t_0\f$ - \f$\mathrm{MeV}\f$ \f$\mathrm{fm}^3\f$
      - \f$t_1\f$ - \f$\mathrm{MeV}\f$ \f$\mathrm{fm}^5\f$
      - \f$t_2\f$ - \f$\mathrm{MeV}\f$ \f$\mathrm{fm}^5\f$
      - \f$t_3\f$ - \f$\mathrm{MeV}\f$ \f$\mathrm{fm}^{3(1+\alpha)}\f$
      
      These are stored internally with units of:
      - \f$t_0\f$ - \f$\mathrm{fm}^2\f$
      - \f$t_1\f$ - \f$\mathrm{fm}^4\f$
      - \f$t_2\f$ - \f$\mathrm{fm}^4\f$
      - \f$t_3\f$ - \f$\mathrm{fm}^{2+3 \alpha}\f$
      
      \hline
      \b Misc:

      The functions for the usual saturation properties are based 
      partly on \ref Brack85.
      
      Models are taken from the references: \ref Bartel79, \ref
      Beiner75, \ref Chabanat95, \ref Chabanat97, \ref Danielewicz08,
      \ref Dobaczewski94, \ref Dutta86, \ref Friedrich86, \ref Onsi94,
      \ref Reinhard95, and \ref Tondeur84, and \ref VanGiai81 .
      
      The variables \f$ \nu_n\f$ and \f$ \nu_p\f$ contain the
      expressions \f$ (-\mu_n+V_n)/T \f$ and \f$ (-\mu_p+V_p)/T \f$
      respectively, where \f$ V \f$ is the potential part of the
      single particle energy for particle i (i.e. the derivative of
      the Hamiltonian w.r.t. density while energy density held
      constant). Equivalently, \f$ \nu_n\f$ is just \f$ -k_{F_n}^2/ 2
      m^{*} \f$.
     
      \note The finite temperature code does not include attempt to
      include antiparticles and uses \ref
      o2scl::fermion_nonrel::calc_density().
      
      \note Since this EOS uses the effective masses and chemical
      potentials in the fermion class, the values of
      <tt>part::non_interacting</tt> for neutrons and protons are set
      to false in many of the functions.

      \hline
      
      \todo
      - Convert W0 to b4 and b4p everywhere
      - Remove use of mnuc in calparfun()?
      - Document load() file format.
      - Update reference list.

      \future
      - There is some code duplication between calc_e() and
      calc_temp_e() which could be simplified.
      - This EOS typically converges very well. One exception seems
      to be using <tt>calc_temp_p()</tt> at very low densities. I have
      had problems, for example, with <tt>mun=5.0, mup=6.5</tt>
      at <tt>T=1.0/197.33</tt>. 

      \hline
      
  */
  class eos_had_skyrme : public eos_had_temp_eden_base {

  public:

    /// \name Basic usage
    //@{
    /// Create a blank Skyrme EOS
    eos_had_skyrme();

    /// Destructor
    virtual ~eos_had_skyrme() {};

    /** \brief Equation of state as a function of densities

	\note Runs the zero temperature code if \c temper is less
	than or equal to zero.
     */
    virtual int calc_temp_e(fermion &ne, fermion &pr, double temper, 
			    thermo &th);

    /// Equation of state as a function of density.
    virtual int calc_e(fermion &ne, fermion &pr, thermo &lt);
    //@}

    /// \name Basic Skyrme model parameters
    //@{
    double t0,t1,t2,t3,x0,x1,x2,x3,alpha,a,b;
    //@}

    /** \brief Spin-orbit splitting (in \f$ \mathrm{fm}^{-1} \f$)

	This is unused, but included for possible future use and
	present in the internally stored models.
    */
    double W0;

    /// Isoscalar spin-orbit term (in \f$ \mathrm{fm}^{-1} \f$)
    double b4;

    /// Isovector spin-orbit term (in \f$ \mathrm{fm}^{-1} \f$)
    double b4p;

    /// Bibliographic reference
    std::string reference;

    /** \name Saturation properties

	These calculate the various saturation properties exactly from
	the parameters at any density. These routines often assume that 
	the neutron and proton masses are equal.
    */
    //@{
  
    /** \brief Calculate binding energy
      
	\f[
	\frac{E}{A} = C n_B^{2/3} \left( 1 + \beta n_B \right) + 
	\frac{3 t_0}{8} n_B + \frac{t_3^{\prime}}{16} n_B^{\alpha+1} 
	\f]
    */
    virtual double feoa(double nb);
  
    /** \brief Calculate effective mass
      
	\f[
	M^{*}/M = \left(1+ \beta n_B \right)^{-1} \\
	\f]
    */
    virtual double fmsom(double nb);

    /** \brief Calculate compressibility

	\f[
	K = 10 C n_B^{2/3} + \frac{27}{4} t_0 n_B + 40 C \beta n_B^{5/3} + 
	\frac{9 t_3^{\prime}}{16} 
	\alpha \left( \alpha+1 \right) n_B^{1 + \alpha} +
	\frac{9 t_3^{\prime}}{8} \left( \alpha+1 \right) n_B^{1 + \alpha}
	\f]
    */
    virtual double fcomp(double nb);

    /** \brief Calculate symmetry energy

	If pf=0.5, then the exact expression below is used.
	Otherwise, the method from class eos_had_base is used.

	\f[
	E_{sym} = \frac{5}{9} C n^{2/3} + \frac{10 C m}{3}
	\left[ \frac{t_2}{6} \left(1 + \frac{5}{4} x_2 \right) - 
	\frac{1}{8} t_1 x_1 \right] n^{5/3} 
	- \frac{t_3^{\prime}}{24} 
	\left({\textstyle \frac{1}{2}} + x_3 \right) n^{1+\alpha} - 
	\frac{t_0}{4} \left( {\textstyle \frac{1}{2}} + x_0 \right) n 
	\f]
    */
    virtual double fesym(double nb, double alpha=0.0);

    /** \brief skewness

	\f[
	2 C n_B^{2/3} \left(9-5/M^{*}/M\right)+
	\frac{27 t_3^{\prime}}{16} n^{1+\alpha} \alpha 
	\left(\alpha^2-1\right)
	\f]
    */
    virtual double fkprime(double nb);
    //@}

    /** \brief Calculate \f$ t_0,t_1,t_2,t_3 \f$ and \f$ \alpha \f$ from 
	the saturation properties.
      
	In nuclear matter: 
      
	\f$ E_b=E_b(n_0,M^{*},t_0,t_3,\alpha) \f$ \n
	\f$ P=P(n_0,M^{*},t_0,t_3,\alpha) \f$ \n
	\f$ K=K(n_0,M^{*},t_3,\alpha) \f$ 
	(the \f$ t_0 \f$ dependence vanishes) \n
	\f$ M^{*}=M^{*}(n_0,t_1,t_2,x_2) \f$ 
	(the \f$ x_1 \f$ dependence cancels), \n
	\f$ E_{sym}=E_{sym}(x_0,x_1,x_2,x_3,t_0,t_1,t_2,t_3,\alpha) \f$
      
	To fix the couplings from the saturation properties, we take
	\f$ n_0, M^{*}, E_b, K \f$ as inputs, and we can fix \f$
	t_0,t_3,\alpha \f$ from the first three relations, then use
	\f$ M^{*}, E_b \f$ to fix \f$ t_2 \f$ and \f$ t_1 \f$.  The
	separation into two solution steps should make for better
	convergence. All of the x's are free parameters and should be
	set before the function call.
      
	The arguments \c gt0, \c gt3, \c galpha, \c gt1, and \c gt2
	are used as initial guesses for skyme_eos::t0, eos_had_skyrme::t3,
	eos_had_skyrme::alpha, eos_had_skyrme::t1, and eos_had_skyrme::t2
	respectively.
      
	\todo Does this work for both 'a' and 'b' non-zero?
      
	\todo Compare to similar formulae from \ref Margueron02
    */

    int calpar(double gt0=-10.0, double gt3=70.0, double galpha=0.2,
	       double gt1=2.0, double gt2=-1.0);

    // Unfinished.
    /* \brief 
	From \ref Margueron02
    */
    //  int calpar_new(double m);

    /** \brief Use eos_had_base methods for saturation properties
      
	This can be set to true to check the difference between
	the exact expressions and the numerical values from
	class eos_had_base.
    */
    bool parent_method;
  
    /** \brief Check the Landau parameters for instabilities

	This returns zero if there are no instabilities.
     */
    int check_landau(double nb, double m);

    /** \brief Calculate the Landau parameters for nuclear matter

	Given \c n0 and \c m, this calculates the Landau parameters in
	nuclear matter as given in \ref Margueron02
     
	\todo This needs to be checked.
	
	(Checked once on 11/05/03)
    */
    void landau_nuclear(double n0, double m,
		       double &f0, double &g0, double &f0p,
		       double &g0p, double &f1, double &g1,
		       double &f1p, double &g1p);

    /** \brief Calculate the Landau parameters for neutron matter
	    
	Given 'n0' and 'm', this calculates the Landau parameters in
	neutron matter as given in \ref Margueron02
	
	\todo This needs to be checked
	
	(Checked once on 11/05/03)
    */
    void landau_neutron(double n0, double m, double &f0, double &g0, 
			double &f1, double &g1);

    /// Return string denoting type ("eos_had_skyrme")
    virtual const char *type() { return "eos_had_skyrme"; }

    /// If true, compute the chemical potentials even at zero density
    bool mu_at_zero_density;

    /** \brief Set using alternate parameterization

	From \ref Bender03 as in, e.g. \ref Kortelainen14
	\f{eqnarray*}
        C^{\rho \rho}_{00} &=& 3 t_0/8 \nonumber \\
        C^{\rho \rho}_{10} &=& -t_0/4 \left(\frac{1}{2}+x_0 \right) 
	\nonumber \\
        C^{\rho \rho}_{0D} &=& t_3/16 \nonumber \\
        C^{\rho \rho}_{1D} &=& -t_3/24 \left(\frac{1}{2}+x_3\right)
        \nonumber \\
        C^{\rho \tau}_{0} &=& 3 t_1/16+t_2/4\left(\frac{5}{4}+x_2\right)
        \nonumber \\
        C^{\rho \tau}_{1} &=& -t_1/8 \left(\frac{1}{2}+x_1\right) +
        t_2/8 \left(\frac{1}{2}+x_2\right) \nonumber \\
        C^{\rho \Delta \rho}_{0} &=& -9/64 t_1+t_2/16 
        \left(\frac{5}{4}+x_2\right) \nonumber \\
        C^{\rho \Delta \rho}_{1} &=& 3/32 t_1 \left(\frac{1}{2}+x_1\right) +
        t_2/32 \left(\frac{1}{2}+x_2\right) \nonumber \\
        C^{\rho \nabla J}_{0} &=& -b_4 -b_4^{\prime}/2 \nonumber \\
        C^{\rho \nabla J}_{1} &=& -b_4^{\prime}/2
	\f}
    */
    void alt_params_set
      (double Crr00, double Crr10, double Crr0D, double Crr1D, 
       double Crt0, double Crt1, double CrDr0, double CrDr1, 
       double CrnJ0, double CrnJ1, double alpha2);

    /** \brief Get alternate parameterization
	
	See \ref eos_had_skyrme::alt_params_set().
    */
    void alt_params_get
      (double &Crr00, double &Crr10, double &Crr0D, double &Crr1D, 
       double &Crt0, double &Crt1, double &CrDr0, double &CrDr1, 
       double &CrnJ0, double &CrnJ1, double &alpha2);

    void alt_params_saturation
      (double n0, double EoA, double K, double Ms_star, double a, double L,
       double Mv_star, double CrDr0, double CrDr1, double CrnJ0, double CrnJ1);
 
#ifndef DOXYGEN_NO_O2NS
    
  protected:

    /// Thermodynamics of non-relativistic fermions
    fermion_nonrel nrf;
    
    /// \name Functions and parameters for calpar()
    //@{
    int calparfun(size_t nv, const ubvector &x, ubvector &y);
    int calparfun2(size_t nv, const ubvector &x, ubvector &y);
    double fixn0, fixeoa, fixesym, fixcomp, fixmsom;
    //@}

#endif

  };

#ifndef DOXYGEN_NO_O2NS
}
#endif

#endif
