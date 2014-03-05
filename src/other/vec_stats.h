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
#ifndef O2SCL_VEC_STATS_H
#define O2SCL_VEC_STATS_H

/** \file vec_stats.h
    \brief Statistical functions for vector types

    This file contains several function templates for computing
    statistics of vectors of double-precision data. It includes mean,
    median, variance, standard deviation, covariance, correlation, and
    other functions.

    No additional range checking is done on the vectors.

    \future Consider generalizing to other data types.
*/

#include <o2scl/err_hnd.h>
#include <o2scl/vector.h>

#ifndef DOXYGEN_NO_O2NS
namespace o2scl {
#endif

  /// \name Vector functions
  //@{
  /** \brief Compute the mean of the first \c n elements of a vector

      This function produces the same results
      as <tt>gsl_stats_mean()</tt>.

      If \c n is zero, this function will return zero.
  */
  template<class vec_t> double vector_mean(size_t n, const vec_t &data) {
    long double mean=0.0;
    for(size_t i=0;i<n;i++) {
      mean+=(data[i]-mean)/(i+1);
    }
    return mean;
  }

  /** \brief Compute the mean of the first \c n elements of a vector

      This function produces the same results
      as <tt>gsl_stats_mean()</tt>.

      If the vector size is zero, this function will return zero.
  */
  template<class vec_t> double vector_mean(const vec_t &data) {
    return vector_mean(data.size(),data);
  }

  /** \brief Compute variance with specified mean known in advance
      
      This function computes
      \f[
      \frac{1}{N} \sum_{i} \left( x_i - \mu \right)^2
      \f]
      where the value of \f$ \mu \f$ is given in \c mean. 

      This function produces the same results
      as <tt>gsl_stats_variance_with_fixed_mean()</tt>.
  */
  template<class vec_t>
    double vector_variance_fmean(size_t n, const vec_t &data, double mean) {
    long double var=0.0;
    for(size_t i=0;i<n;i++) {
      long double delta=(data[i]-mean);
      var+=(delta*delta-var)/(i+1);
    }
    return var;
  }

  /** \brief Compute variance with specified mean known in advance
      
      This function computes
      \f[
      \frac{1}{N} \sum_{i} \left( x_i - \mu \right)^2
      \f]
      where the value of \f$ \mu \f$ is given in \c mean. 

      This function produces the same results
      as <tt>gsl_stats_variance_with_fixed_mean()</tt>.
  */
  template<class vec_t>
    double vector_variance_fmean(const vec_t &data, double mean) {
    return vector_variance_fmean(data.size(),data,mean);
  }

  /** \brief Compute the variance with specified mean

      This function computes
      \f[
      \frac{1}{N-1} \sum_{i} \left( x_i - \mu \right)^2
      \f]
      where the value of \f$ \mu \f$ is given in \c mean.
      
      This function produces the same results
      as <tt>gsl_stats_variance_m</tt>.

      If \c n is 0 or 1, this function will call the error
      handler.
  */
  template<class vec_t>
    double vector_variance(size_t n, const vec_t &data, double mean) {

    if (n<2) {
      O2SCL_ERR2_RET("Cannot compute variance with less than 2 elements",
		     " in vector_variance().",exc_einval);
    }

    double var=vector_variance_fmean<vec_t>(n,data,mean);
    return var*n/(n-1);
  }

  /** \brief Compute the variance with specified mean

      This function computes
      \f[
      \frac{1}{N-1} \sum_{i} \left( x_i - \mu \right)^2
      \f]
      where the value of \f$ \mu \f$ is given in \c mean.
      
      This function produces the same results
      as <tt>gsl_stats_variance_m</tt>.

      If \c n is 0 or 1, this function will call the error
      handler.
  */
  template<class vec_t>
    double vector_variance(const vec_t &data, double mean) {
    return vector_variance(data.size(),data,mean);
  }

  /** \brief Compute the variance 

      This function computes
      \f[
      \frac{1}{N-1} \sum_{i} \left( x_i - \mu \right)^2
      \f]
      where \f$ \mu \f$ is the mean computed with \ref vector_mean().
      
      This function produces the same results
      as <tt>gsl_stats_variance</tt>.

      If \c n is 0 or 1, this function will call the error handler.
  */
  template<class vec_t> double vector_variance(size_t n, const vec_t &data) {

    if (n<2) {
      O2SCL_ERR2_RET("Cannot compute variance with less than 2 elements",
		     " in vector_variance().",exc_einval);
    }
    
    double mean=vector_mean<vec_t>(n,data);
    double var=vector_variance_fmean<vec_t>(n,data,mean);
    return var*n/(n-1);
  }

  /** \brief Compute the variance 

      This function computes
      \f[
      \frac{1}{N-1} \sum_{i} \left( x_i - \mu \right)^2
      \f]
      where \f$ \mu \f$ is the mean computed with \ref vector_mean().
      
      This function produces the same results
      as <tt>gsl_stats_variance</tt>.

      If \c n is 0 or 1, this function will call the error handler.
  */
  template<class vec_t> double vector_variance(const vec_t &data) {
    return vector_variance(data.size(),data);
  }

  /** \brief Standard deviation with specified mean known in advance

      This function computes
      \f[
      \sqrt{\frac{1}{N} \sum_{i} \left( x_i - \mu \right)^2}
      \f]
      where the value of \f$ \mu \f$ is given in \c mean. 

      This function produces the same results
      as <tt>gsl_stats_sd_with_fixed_mean()</tt>.

      If \c n is zero, this function will return zero without calling
      the error handler.
  */
  template<class vec_t>
    double vector_stddev_fmean(size_t n, const vec_t &data, 
			       double mean) {
    double sd=vector_variance_fmean<vec_t>(n,data,mean);
    return std::sqrt(sd);
  }

  /** \brief Standard deviation with specified mean known in advance

      This function computes
      \f[
      \sqrt{\frac{1}{N} \sum_{i} \left( x_i - \mu \right)^2}
      \f]
      where the value of \f$ \mu \f$ is given in \c mean. 

      This function produces the same results
      as <tt>gsl_stats_sd_with_fixed_mean()</tt>.

      If \c n is zero, this function will return zero without calling
      the error handler.
  */
  template<class vec_t>
    double vector_stddev_fmean(const vec_t &data, double mean) {
    return vector_stddev_fmean(data.size(),data,mean);
  }

  /** \brief Standard deviation with specified mean

      This function computes
      \f[
      \sqrt{\frac{1}{N-1} \sum_{i} \left( x_i - \mu \right)^2}
      \f]
      where \f$ \mu \f$ is the mean computed with \ref vector_mean().

      This function produces the same results
      as <tt>gsl_stats_sd()</tt>.

      If \c n is 0 or 1, this function will call the error handler.
  */
  template<class vec_t> double vector_stddev(size_t n, const vec_t &data) {
    
    if (n<2) {
      O2SCL_ERR2_RET("Cannot compute std. dev. with less than 2 elements",
		     " in vector_stddev().",exc_einval);
    }
    
    double mean=vector_mean<vec_t>(n,data);
    double var=vector_variance_fmean<vec_t>(n,data,mean);
    return std::sqrt(var*n/(n-1));
  }

  /** \brief Standard deviation with specified mean

      This function computes
      \f[
      \sqrt{\frac{1}{N-1} \sum_{i} \left( x_i - \mu \right)^2}
      \f]
      where \f$ \mu \f$ is the mean computed with \ref vector_mean().

      This function produces the same results
      as <tt>gsl_stats_sd()</tt>.

      If \c n is 0 or 1, this function will call the error handler.
  */
  template<class vec_t> double vector_stddev(const vec_t &data) {
    return vector_stddev(data.size(),data);
  }

  /** \brief Standard deviation with specified mean

      This function computes
      \f[
      \sqrt{\frac{1}{N-1} \sum_{i} \left( x_i - \mu \right)^2}
      \f]
      where the value of \f$ \mu \f$ is given in \c mean. 

      This function produces the same results
      as <tt>gsl_stats_sd_m()</tt>.

      If \c n is 0 or 1, this function will call the error
      handler.
  */
  template<class vec_t> double vector_stddev(size_t n, const vec_t &data, 
					     double mean) {

    if (n<2) {
      O2SCL_ERR2_RET("Cannot compute std. dev. with less than 2 elements",
		     " in vector_stddev().",exc_einval);
    }
    
    double sd=vector_variance_fmean<vec_t>(n,data,mean);
    return std::sqrt(sd*n/(n-1));
  }

  /** \brief Standard deviation with specified mean

      This function computes
      \f[
      \sqrt{\frac{1}{N-1} \sum_{i} \left( x_i - \mu \right)^2}
      \f]
      where the value of \f$ \mu \f$ is given in \c mean. 

      This function produces the same results
      as <tt>gsl_stats_sd_m()</tt>.

      If \c n is 0 or 1, this function will call the error
      handler.
  */
  template<class vec_t> double vector_stddev(const vec_t &data, double mean) {
    return vector_stddev(data.size(),data,mean);
  }
  
  /** \brief Absolute deviation from the specified mean

      This function computes
      \f[
      \sum_i | x_i - \mu |
      \f]
      where the value of \f$ \mu \f$ is given in \c mean. 

      This function produces the same results
      as <tt>gsl_stats_absdev_m()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t> double vector_absdev(size_t n, const vec_t &data, 
					     double mean) {
    
    if (n==0) return 0.0;

    long double sum=0.0;
    for(size_t i=0;i<n;i++) {
      sum+=fabs(data[i]-mean);
    }
    return sum/n;
  }

  /** \brief Absolute deviation from the specified mean

      This function computes
      \f[
      \sum_i | x_i - \mu |
      \f]
      where the value of \f$ \mu \f$ is given in \c mean. 

      This function produces the same results
      as <tt>gsl_stats_absdev_m()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t> double vector_absdev(const vec_t &data, 
					     double mean) {
    return vector_absdev(data.size(),data,mean);
  }
  
  /** \brief Absolute deviation from the computed mean

      This function computes
      \f[
      \sum_i | x_i - \mu |
      \f]
      where the value of \f$ \mu \f$ is mean as computed
      from \ref vector_mean().

      This function produces the same results
      as <tt>gsl_stats_absdev()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t>
    double vector_absdev(size_t n, const vec_t &data) {
    double mean=vector_mean<vec_t>(n,data);
    return vector_absdev(n,data,mean);
  }

  /** \brief Absolute deviation from the computed mean

      This function computes
      \f[
      \sum_i | x_i - \mu |
      \f]
      where the value of \f$ \mu \f$ is mean as computed
      from \ref vector_mean().

      This function produces the same results
      as <tt>gsl_stats_absdev()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t>
    double vector_absdev(const vec_t &data) {
    return vector_absdev(data.size(),data);
  }

  /** \brief Skewness with specified mean and standard deviation

      This function computes 
      \f[
      \frac{1}{N} \sum_i \left[ 
      \frac{ \left(x_i - \mu \right)}{ \sigma }\right]^3
      \f]
      where the values of \f$ \mu \f$ and \f$ \sigma \f$ 
      are given in \c mean and \c stddev.

      This function produces the same results
      as <tt>gsl_stats_skew_m_sd()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t> double vector_skew(size_t n, const vec_t &data, 
					   double mean, double stddev) {
    long double skew=0.0;
    for(size_t i=0;i<n;i++) {
      long double x=(data[i]-mean)/stddev;
      skew+=(x*x*x-skew)/(i+1);
    }
    return skew;
  }

  /** \brief Skewness with specified mean and standard deviation

      This function computes 
      \f[
      \frac{1}{N} \sum_i \left[ 
      \frac{ \left(x_i - \mu \right)}{ \sigma }\right]^3
      \f]
      where the values of \f$ \mu \f$ and \f$ \sigma \f$ 
      are given in \c mean and \c stddev.

      This function produces the same results
      as <tt>gsl_stats_skew_m_sd()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t> double vector_skew(const vec_t &data, 
					   double mean, double stddev) {
    return vector_skew(data.size(),data,mean,stddev);
  }

  /** \brief Skewness with computed mean and standard deviation

      This function computes 
      \f[
      \frac{1}{N} \sum_i \left[ 
      \frac{ \left(x_i - \mu \right)}{ \sigma }\right]^3
      \f]
      where the values of \f$ \mu \f$ and \f$ \sigma \f$ 
      are computed using \ref vector_mean() and \ref vector_stddev().

      This function produces the same results
      as <tt>gsl_stats_skew()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t> double vector_skew(size_t n, const vec_t &data) {
    double mean=vector_mean<vec_t>(n,data);
    double sd=vector_stddev<vec_t>(n,data,mean);
    return vector_skew(n,data,mean,sd);
  }

  /** \brief Skewness with computed mean and standard deviation

      This function computes 
      \f[
      \frac{1}{N} \sum_i \left[ 
      \frac{ \left(x_i - \mu \right)}{ \sigma }\right]^3
      \f]
      where the values of \f$ \mu \f$ and \f$ \sigma \f$ 
      are computed using \ref vector_mean() and \ref vector_stddev().

      This function produces the same results
      as <tt>gsl_stats_skew()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t> double vector_skew(const vec_t &data) {
    return vector_skew(data.size(),data);
  }

  /** \brief Kurtosis with specified mean and standard deviation

      This function computes 
      \f[
      -3 + \frac{1}{N} \sum_i \left[ 
      \frac{ \left(x_i - \mu \right)}{ \sigma }\right]^4
      \f]
      where the values of \f$ \mu \f$ and \f$ \sigma \f$ 
      are given in \c mean and \c stddev.

      This function produces the same results
      as <tt>gsl_stats_kurtosis_m_sd()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t>
    double vector_kurtosis(size_t n, const vec_t &data, double mean,
			   double stddev) {
    long double avg=0.0;
    for(size_t i=0;i<n;i++) {
      long double x=(data[i]-mean)/stddev;
      avg+=(x*x*x*x-avg)/(i+1);
    }
    return avg-3.0;
  }

  /** \brief Kurtosis with specified mean and standard deviation

      This function computes 
      \f[
      -3 + \frac{1}{N} \sum_i \left[ 
      \frac{ \left(x_i - \mu \right)}{ \sigma }\right]^4
      \f]
      where the values of \f$ \mu \f$ and \f$ \sigma \f$ 
      are given in \c mean and \c stddev.

      This function produces the same results
      as <tt>gsl_stats_kurtosis_m_sd()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t>
    double vector_kurtosis(const vec_t &data, double mean,
			   double stddev) {
    return vector_kurtosis(data.size(),data,mean,stddev);
  }

  /** \brief Kurtosis with computed mean and standard deviation

      This function computes 
      \f[
      -3 + \frac{1}{N} \sum_i \left[ 
      \frac{ \left(x_i - \mu \right)}{ \sigma }\right]^4
      \f]
      where the values of \f$ \mu \f$ and \f$ \sigma \f$ 
      are computed using \ref vector_mean() and \ref vector_stddev().

      This function produces the same results
      as <tt>gsl_stats_kurtosis()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t> double vector_kurtosis(size_t n, const vec_t &data) {
    double mean=vector_mean<vec_t>(n,data);
    double sd=vector_stddev<vec_t>(n,data,mean);
    return vector_kurtosis(n,data,mean,sd);
  }

  /** \brief Kurtosis with computed mean and standard deviation

      This function computes 
      \f[
      -3 + \frac{1}{N} \sum_i \left[ 
      \frac{ \left(x_i - \mu \right)}{ \sigma }\right]^4
      \f]
      where the values of \f$ \mu \f$ and \f$ \sigma \f$ 
      are computed using \ref vector_mean() and \ref vector_stddev().

      This function produces the same results
      as <tt>gsl_stats_kurtosis()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t> double vector_kurtosis(const vec_t &data) {
    return vector_kurtosis(data.size(),data);
  }

  /** \brief Lag-1 autocorrelation

      This function computes
      \f[
      \left[
      \sum_i \left(x_i - \mu\right) \left(x_{i-1} - \mu \right)
      \right] \left[ 
      \sum_i \left(x_i - \mu\right)^2 
      \right]^{-1}
      \f]

      This function produces the same results
      as <tt>gsl_stats_lag1_autocorrelation_m()</tt>.

      If \c n is less than 2, this function will call the error handler.
  */
  template<class vec_t>
    double vector_lag1_autocorr(size_t n, const vec_t &data, double mean) {
    
    if (n<2) {
      O2SCL_ERR2_RET("Cannot compute lag1 with less than 2 elements",
		     " in vector_lag1_autocorr().",exc_einval);
    }

    long double q=0.0;
    long double v=(data[0]-mean)*(data[0]-mean);
    for(size_t i=1;i<n;i++) {
      long double delta0=data[i-1]-mean;
      long double delta1=data[i]-mean;
      q+=(delta0*delta1-q)/(i+1);
      v+=(delta1*delta1-v)/(i+1);
    }

    return q/v;
  }

  /** \brief Lag-1 autocorrelation

      This function computes
      \f[
      \left[
      \sum_i \left(x_i - \mu\right) \left(x_{i-1} - \mu \right)
      \right] \left[ 
      \sum_i \left(x_i - \mu\right)^2 
      \right]^{-1}
      \f]

      This function produces the same results
      as <tt>gsl_stats_lag1_autocorrelation_m()</tt>.

      If \c n is less than 2, this function will call the error handler.
  */
  template<class vec_t>
    double vector_lag1_autocorr(const vec_t &data, double mean) {
    return vector_lag1_autocorr(data.size(),data,mean);
  }

  /** \brief Lag-1 autocorrelation

      This function computes
      \f[
      \left[
      \sum_i \left(x_i - \mu\right) \left(x_{i-1} - \mu \right)
      \right] \left[ 
      \sum_i \left(x_i - \mu\right)^2 
      \right]^{-1}
      \f]
      
      This function produces the same results
      as <tt>gsl_stats_lag1_autocorrelation()</tt>.

      If \c n is less than 2, this function will call the error handler.
  */
  template<class vec_t> double vector_lag1_autocorr
    (size_t n, const vec_t &data) {
    double mean=vector_mean<vec_t>(n,data);
    return vector_lag1_autocorr(n,data,mean);
  }

  /** \brief Lag-1 autocorrelation

      This function computes
      \f[
      \left[
      \sum_i \left(x_i - \mu\right) \left(x_{i-1} - \mu \right)
      \right] \left[ 
      \sum_i \left(x_i - \mu\right)^2 
      \right]^{-1}
      \f]
      
      This function produces the same results
      as <tt>gsl_stats_lag1_autocorrelation()</tt>.

      If \c n is less than 2, this function will call the error handler.
  */
  template<class vec_t> double vector_lag1_autocorr(const vec_t &data) {
    return vector_lag1_autocorr(data.size(),data);
  }

  /** \brief Lag-k autocorrelation

      This function computes
      \f[
      \left[
      \sum_i \left(x_i - \mu\right) \left(x_{i-k} - \mu \right)
      \right] \left[ 
      \sum_i \left(x_i - \mu\right)^2 
      \right]^{-1}
      \f]

      If <tt>n<=k</tt>, this function will call the error handler.
  */
  template<class vec_t>
    double vector_lagk_autocorr(size_t n, const vec_t &data, size_t k,
				double mean) {
    
    if (n<=k) {
      O2SCL_ERR2_RET("Not enough elements ",
		     " in vector_lagk_autocorr().",exc_einval);
    }

    long double q=0.0, v=0.0;
    for(size_t i=0;i<k;i++) {
      q+=0.0;
      v+=(data[i]-mean)*(data[i]-mean)/(i+1);
    }
    for(size_t i=k;i<n;i++) {
      long double delta0=data[i-k]-mean;
      long double delta1=data[i]-mean;
      q+=(delta0*delta1-q)/(i+1);
      v+=(delta1*delta1-v)/(i+1);
    }
    return q/v;
  }

  /** \brief Lag-k autocorrelation

      This function computes
      \f[
      \left[
      \sum_i \left(x_i - \mu\right) \left(x_{i-k} - \mu \right)
      \right] \left[ 
      \sum_i \left(x_i - \mu\right)^2 
      \right]^{-1}
      \f]

      If <tt>n<=k</tt>, this function will call the error handler.
  */
  template<class vec_t>
    double vector_lagk_autocorr(const vec_t &data, size_t k,
				double mean) {
    return vector_lagk_autocorr(data.size(),k,mean);
  }

  /** \brief Lag-k autocorrelation

      This function computes
      \f[
      \left[
      \sum_i \left(x_i - \mu\right) \left(x_{i-k} - \mu \right)
      \right] \left[ 
      \sum_i \left(x_i - \mu\right)^2 
      \right]^{-1}
      \f]

      If <tt>n<=k</tt>, this function will call the error handler.
  */
  template<class vec_t> double vector_lagk_autocorr
    (size_t n, const vec_t &data, size_t k) {
    double mean=vector_mean<vec_t>(n,data);
    return vector_lagk_autocorr(n,data,k,mean);
  }

  /** \brief Lag-k autocorrelation

      This function computes
      \f[
      \left[
      \sum_i \left(x_i - \mu\right) \left(x_{i-k} - \mu \right)
      \right] \left[ 
      \sum_i \left(x_i - \mu\right)^2 
      \right]^{-1}
      \f]

      If <tt>n<=k</tt>, this function will call the error handler.
  */
  template<class vec_t> double vector_lagk_autocorr
    (const vec_t &data, size_t k) {
    return vector_lagk_autocorr(data.size(),data,k);
  }

  /** \brief Compute the covariance of two vectors

      This function computes
      \f[
      \frac{1}{n-1} \sum_i \left(x_i - {\bar{x}}\right)
      \left(y_i - {\bar{y}}\right)
      \f]
      where \f$ {\bar{x}} \f$ and \f$ {\bar{y}} \f$ are specified
      in \c mean1 and \c mean2, respectively.

      This function produces the same results
      as <tt>gsl_stats_covariance_m()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t, class vec2_t>
    double vector_covariance(size_t n, const vec_t &data1, const vec2_t &data2,
			     double mean1, double mean2) {
    double covar=0.0;
    for(size_t i=0;i<n;i++) {
      double delta1=(data1[i]-mean1);
      double delta2=(data2[i]-mean2);
      covar+=(delta1*delta2-covar)/(i+1);
    }
    return covar*n/(n-1);
  }

  /** \brief Compute the covariance of two vectors

      This function computes
      \f[
      \frac{1}{n-1} \sum_i \left(x_i - {\bar{x}}\right)
      \left(y_i - {\bar{y}}\right)
      \f]
      where \f$ {\bar{x}} \f$ and \f$ {\bar{y}} \f$ are specified
      in \c mean1 and \c mean2, respectively.

      This function produces the same results
      as <tt>gsl_stats_covariance_m()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t, class vec2_t>
    double vector_covariance(const vec_t &data1, const vec2_t &data2,
			     double mean1, double mean2) {
    return vector_covariance(data1.size(),data1,data2,mean1,mean2);
  }

  /** \brief Compute the covariance of two vectors

      This function computes
      \f[
      \frac{1}{n-1} \sum_i \left(x_i - {\bar{x}}\right)
      \left(y_i - {\bar{y}}\right)
      \f]
      where \f$ {\bar{x}} \f$ and \f$ {\bar{y}} \f$ are 
      the averages of \c data1 and \c data2 and are computed
      automatically using \ref vector_mean().

      This function produces the same
      results as <tt>gsl_stats_covariance()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t, class vec2_t>
    double vector_covariance(size_t n, const vec_t &data1, 
			     const vec2_t &data2) {
    double covar=0.0;
    double mean1=vector_mean<vec_t>(n,data1);
    double mean2=vector_mean<vec_t>(n,data2);
    for(size_t i=0;i<n;i++) {
      long double delta1=(data1[i]-mean1);
      long double delta2=(data2[i]-mean2);
      covar+=(delta1*delta2-covar)/(i+1);
    }
    return covar*n/(n-1);
  }
  
  /** \brief Compute the covariance of two vectors

      This function computes
      \f[
      \frac{1}{n-1} \sum_i \left(x_i - {\bar{x}}\right)
      \left(y_i - {\bar{y}}\right)
      \f]
      where \f$ {\bar{x}} \f$ and \f$ {\bar{y}} \f$ are 
      the averages of \c data1 and \c data2 and are computed
      automatically using \ref vector_mean().

      This function produces the same
      results as <tt>gsl_stats_covariance()</tt>.

      If \c n is zero, this function will return zero
      without calling the error handler.
  */
  template<class vec_t, class vec2_t>
    double vector_covariance(const vec_t &data1, 
			     const vec2_t &data2) {
    return vector_covariance(data1.size(),data1,data2);
  }
  
  /** \brief Pearson's correlation

      This function computes the Pearson correlation coefficient 
      between \c data1 and \c data2 .
      
      This function produces the same
      results as <tt>gsl_stats_correlation()</tt>.

      \comment
      r = cov(x, y) / (\Hat\sigma_x \Hat\sigma_y)
      = {1/(n-1) \sum (x_i - \Hat x) (y_i - \Hat y)
      \over
      \sqrt{1/(n-1) \sum (x_i - \Hat x)^2} \sqrt{1/(n-1) 
      \sum (y_i - \Hat y)^2}
      }
      \endcomment

      If \c n is zero, this function will call the error handler.
  */
  template<class vec_t, class vec2_t>
    double vector_correlation(size_t n, const vec_t &data1, 
			      const vec2_t &data2) {
    size_t i;

    if (n<1) {
      O2SCL_ERR2_RET("Cannot compute correlation with no elements",
		     " in vector_correlation().",exc_einval);
    }

    double sum_xsq = 0.0;
    double sum_ysq = 0.0;
    double sum_cross = 0.0;
    double ratio;
    double delta_x, delta_y;
    double mean_x, mean_y;
    double r;

    /*
     * Compute:
     * sum_xsq = Sum [ (x_i - mu_x)^2 ],
     * sum_ysq = Sum [ (y_i - mu_y)^2 ] and
     * sum_cross = Sum [ (x_i - mu_x) * (y_i - mu_y) ]
     * using the above relation from Welford's paper
     */

    mean_x = data1[0];
    mean_y = data2[0];

    for (i = 1; i < n; ++i) {
      ratio = i / (i + 1.0);
      delta_x = data1[i] - mean_x;
      delta_y = data2[i] - mean_y;
      sum_xsq += delta_x * delta_x * ratio;
      sum_ysq += delta_y * delta_y * ratio;
      sum_cross += delta_x * delta_y * ratio;
      mean_x += delta_x / (i + 1.0);
      mean_y += delta_y / (i + 1.0);
    }
    
    r = sum_cross / (std::sqrt(sum_xsq) * std::sqrt(sum_ysq));
    
    return r;
  }

  /** \brief Pearson's correlation

      This function computes the Pearson correlation coefficient 
      between \c data1 and \c data2 .
      
      This function produces the same
      results as <tt>gsl_stats_correlation()</tt>.

      \comment
      r = cov(x, y) / (\Hat\sigma_x \Hat\sigma_y)
      = {1/(n-1) \sum (x_i - \Hat x) (y_i - \Hat y)
      \over
      \sqrt{1/(n-1) \sum (x_i - \Hat x)^2} \sqrt{1/(n-1) 
      \sum (y_i - \Hat y)^2}
      }
      \endcomment

      If \c n is zero, this function will call the error handler.
  */
  template<class vec_t, class vec2_t>
    double vector_correlation(const vec_t &data1, 
			      const vec2_t &data2) {
    return vector_correlation(data1.size(),data1,data2);
  }

  /** \brief Pooled variance

      \todo Document this

      This function produces the same
      results as <tt>gsl_stats_pvariance()</tt>.
      
      If \c n is zero, this function will return zero without calling
      the error handler.
  */
  template<class vec_t, class vec2_t>
    double vector_pvariance(size_t n1, const vec_t &data1, 
			    size_t n2, const vec2_t &data2) {
    double var1=vector_variance<vec_t>(n1,data1);
    double var2=vector_variance<vec2_t>(n2,data2);
    return (((n1-1)*var1)+((n2-1)*var2))/(n1+n2-2);
  }

  /** \brief Pooled variance

      \todo Document this

      This function produces the same
      results as <tt>gsl_stats_pvariance()</tt>.
      
      If \c n is zero, this function will return zero without calling
      the error handler.
  */
  template<class vec_t, class vec2_t>
    double vector_pvariance(const vec_t &data1, 
			    const vec2_t &data2) {
    return vector_pvariance(data1.size(),data1,data2.size(),data2);
  }

  /** \brief Quantile from sorted data (ascending only)

      This function returns the quantile \c f of data which
      has already been sorted in ascending order. The quantile,
      \f$ q \f$ , is
      found by interpolation using 
      \f[
      q = \left(1-\delta\right) x_i \delta x_{i+1}
      \f]
      where \f$ i = \mathrm{floor}[ (n-1)f ] \f$ and 
      \f$ \delta = (n-1)f -i \f$ .

      This function produces the same
      results as <tt>gsl_stats_quantile_from_sorted_data()</tt>.

      No checks are made to ensure the data is sorted, or to ensure
      that \f$ 0 \leq 0 \leq 1 \f$. If \c n is zero, this function
      will return zero without calling the error handler.
  */
  template<class vec_t>
    double vector_quantile_sorted(size_t n, const vec_t &data, 
				  const double f) {

    double index=f*(n-1);
    size_t lhs=((size_t)index);
    double delta=index-lhs;
    if (n==0) return 0.0;
    if (lhs==n-1) return data[lhs];
    return (1-delta)*data[lhs]+delta*data[lhs+1];
  }
  
  /** \brief Return the median of sorted (ascending or descending) data

      This function returns the median of sorted data (either
      ascending or descending), assuming the data has already been
      sorted. When the data set has an odd number of elements, the
      median is the value of the element at index \f$ (n-1)/2 \f$,
      otherwise, the median is taken to be the average of the elements
      at indices \f$ (n-1)/2 \f$ and \f$ n/2 \f$ .

      This function produces the same
      results as <tt>gsl_stats_median_from_sorted_data()</tt>.

      No checks are made to ensure the data is sorted. If \c n is
      zero, this function will return zero without calling the error
      handler.
  */
  template<class vec_t>
    double vector_median_sorted(size_t n, const vec_t &data) {
    
    if (n==0) return 0.0;
    
    size_t lhs=(n-1)/2;
    size_t rhs=n/2;
    
    if (lhs==rhs) return data[lhs];

    return (data[lhs]+data[rhs])/2.0;
  }

  /** \brief Compute the chi-squared statistic

      This function computes
      \f[
      \sum_i \left( \frac{\mathrm{obs}_i - \mathrm{exp}_i}
      {\mathrm{err}_i}\right)^2
      \f]
      where \f$ \mathrm{obs} \f$ are the observed values,
      \f$ \mathrm{exp} \f$ are the expected values, and 
      \f$ \mathrm{err} \f$ are the errors.
   */
  template<class vec_t, class vec2_t, class vec3_t>
    double vector_chi_squared(size_t n, const vec_t &obs, const vec2_t &exp,
			      const vec3_t &err) {
    double chi2=0.0;
    for(size_t i=0;i<n;i++) {
      chi2+=pow((obs[i]-exp[i])/err[i],2.0);
    }
    return chi2;
  }
  //@}

  /// \name Weighted vector functions
  //@{
  /** \brief Compute the mean of weighted data

      This function computes 
      \f[
      \left( \sum_i w_i x_i \right) \left( \sum_i w_i \right)^{-1}
      \f]

      This function produces the same results
      as <tt>gsl_stats_wmean()</tt>.

      \comment
      M(n) = M(n-1) + (data[n] - M(n-1)) (w(n)/(W(n-1) + w(n)))
      W(n) = W(n-1) + w(n)
      \endcomment
  */
  template<class vec_t, class vec2_t>
    double wvector_mean(size_t n, const vec_t &data, const vec2_t &weights) {

    long double wmean=0.0;
    long double W=0.0;
    for(size_t i=0;i<n;i++) {
      double wi=weights[i];
      if (wi>0.0) {
	W+=wi;
	wmean+=(data[i]-wmean)*(wi/W);
      }
    }
    
    return wmean;
  }

  /** \brief Compute a normalization factor for weighted data

      This function is used internally in \ref wvector_variance(size_t
      n, vec_t &data, const vec2_t &weights, double wmean) and \ref
      wvector_stddev(size_t n, vec_t &data, const vec2_t &weights, double
      wmean) .
  */
  template<class vec_t> double wvector_factor(size_t n, const vec_t &weights) {
    
    long double a=0.0;
    long double b=0.0;
    long double factor;
    for(size_t i=0;i<n;i++) {
      double wi=weights[i];
      if (wi>0.0) {
	a+=wi;
	b+=wi*wi;
      }
    }
    factor=a*a/(a*a-b);
    return factor;
  }
  
  /** \brief Compute the variance of a weighted vector with a mean
      known in advance

      This function computes
      \f[
      \left[ \sum_i w_i \left(x_i-\mu\right)^2 \right] 
      \left[ \sum_i w_i \right]^{-1}
      \f]

      This function produces the same results
      as <tt>gsl_stats_wvariance_with_fixed_mean()</tt>.

  */
  template<class vec_t, class vec2_t>
    double wvector_variance_fmean(size_t n, const vec_t &data,
				  const vec2_t &weights, double wmean) {
    long double wvariance=0.0;
    long double W=0.0;
    for(size_t i=0;i<n;i++) {
      double wi=weights[i];
      if (wi>0.0) {
	const long double delta=data[i]-wmean;
	W+=wi;
	wvariance+=(delta*delta-wvariance)*(wi/W);
      }
    }

    return wvariance;
  }

  /** \brief Compute the variance of a weighted vector with
      specified mean

      This function produces the same results
      as <tt>gsl_stats_wvariance_m()</tt>.
  */
  template<class vec_t, class vec2_t>
    double wvector_variance(size_t n, const vec_t &data,
			    const vec2_t &weights, double wmean) {

    const double variance=wvector_variance_fmean
      (n,data,weights,wmean);
    const double scale=wvector_factor(n,weights);
    const double wvar=scale*variance;
    return wvar;
  }

  /** \brief Compute the variance of a weighted vector where mean
      is computed automatically

      This function produces the same results
      as <tt>gsl_stats_wvariance()</tt>.
   */
  template<class vec_t, class vec2_t>
    double wvector_variance(size_t n, const vec_t &data,
			    const vec2_t &weights) {

    double wmean=wvector_mean(n,data,weights);
    return wvector_variance<vec_t,vec2_t>(n,data,weights,wmean);
  }

  /** \brief Compute the standard deviation of a weighted vector 
      with a mean known in advance

      This function produces the same results
      as <tt>gsl_stats_wsd_with_fixed_mean()</tt>.
  */
  template<class vec_t, class vec2_t>
    double wvector_stddev_fmean(size_t n, const vec_t &data,
				const vec2_t &weights, double wmean) {
    return sqrt(wvector_variance_fmean(n,data,weights,wmean));
  }

  /** \brief Compute the standard deviation of a weighted vector where mean
      is computed automatically

      This function produces the same results
      as <tt>gsl_stats_wsd()</tt>.
   */
  template<class vec_t, class vec2_t>
    double wvector_stddev(size_t n, const vec_t &data,
			  const vec2_t &weights) {
    double wmean=wvector_mean(n,data,weights);
    return sqrt(wvector_variance(n,data,weights,wmean));
  }

  /** \brief Compute the standard deviation of a weighted vector with
      specified mean

      This function produces the same results
      as <tt>gsl_stats_wsd_m()</tt>.
  */
  template<class vec_t, class vec2_t>
    double wvector_stddev(size_t n, const vec_t &data,
			  const vec2_t &weights, double wmean) {
    const double variance=wvector_variance_fmean
      (n,data,weights,wmean);
    const double scale=wvector_factor(n,weights);
    double wvar=scale*variance;
    return sqrt(wvar);
  }

  /** \brief Compute the weighted sum of squares of data about the 
      specified weighted mean

      This function produces the same results
      as <tt>gsl_stats_wtss_m()</tt>.
   */
  template<class vec_t, class vec2_t>
    double wvector_sumsq(size_t n, const vec_t &data,
			 const vec2_t &weights, double wmean) {
    long double wtss=0.0;
    for(size_t i=0;i<n;i++) {
      double wi=weights[i];
      if (wi>0.0) {
	const long double delta=data[i]-wmean;
	wtss+=wi*delta*delta;
      }
    }
    
    return wtss;
  }

  /** \brief Compute the weighted sum of squares of data about the 
      weighted mean

      This function produces the same results
      as <tt>gsl_stats_wtss()</tt>.
   */
  template<class vec_t, class vec2_t>
    double wvector_sumsq(size_t n, const vec_t &data,
			 const vec2_t &weights) {
    
    double wmean=wvector_mean(n,data,weights);
    return wvector_sumsq(n,data,weights,wmean);
  }

  /** \brief Compute the absolute deviation of data about a specified mean

      This function produces the same results
      as <tt>gsl_stats_wabsdev_m()</tt>.
   */
  template<class vec_t, class vec2_t> 
    double wvector_absdev(size_t n, const vec_t &data, const vec2_t &weights, 
			  double wmean) {
    long double wabsdev=0.0;
    long double W=0.0;
    for(size_t i=0;i<n;i++) {
      double wi=weights[i];
      if (wi>0.0) {
	const long double delta=fabs(data[i]-wmean);
	W+=wi;
	wabsdev+=(delta-wabsdev)*(wi/W);
      }
    }
    return wabsdev;
  }

  /** \brief Compute the absolute deviation of data about a specified mean
      
      This function produces the same results
      as <tt>gsl_stats_wabsdev()</tt>.
  */
  template<class vec_t, class vec2_t>
    double wvector_absdev(size_t n, const vec_t &data,
			  const vec2_t &weights) {
    
    double wmean=wvector_mean(n,data,weights);
    return wvector_absdev(n,data,weights,wmean);
  }

  /** \brief Compute the skewness of data with specified mean
      and standard deviation

      This function produces the same results
      as <tt>gsl_stats_wskew_m_sd()</tt>.
  */
  template<class vec_t, class vec2_t>
    double wvector_skew(size_t n, const vec_t &data, const vec2_t &weights,
			double wmean, double wsd) {
    long double wskew=0.0;
    long double W=0.0;
    for(size_t i=0;i<n;i++) {
      double wi=weights[i];
      if (wi>0.0) {
	const long double x=(data[i]-wmean)/wsd;
	W+=wi;
	wskew+=(x*x*x-wskew)*(wi/W);
      }
    }
    return wskew;
  }
  
  /** \brief Compute the skewness of data with specified mean
      and standard deviation
      
      This function produces the same results
      as <tt>gsl_stats_wskew()</tt>.
  */
  template<class vec_t, class vec2_t>
    double wvector_skew(size_t n, const vec_t &data, const vec2_t &weights) {
    double wmean=wvector_mean(n,data,weights);
    double wsd=wvector_stddev(n,data,weights,wmean);
    return wvector_skew(n,data,weights,wmean,wsd);
  }

  /** \brief Compute the kurtosis of data with specified mean
      and standard deviation

      This function produces the same results
      as <tt>gsl_stats_wkurtosis_m_sd()</tt>.
  */
  template<class vec_t, class vec2_t>
    double wvector_kurtosis(size_t n, const vec_t &data, const vec2_t &weights,
			    double wmean, double wsd) {
    long double wavg=0.0;
    long double W=0.0;
    for(size_t i=0;i<n;i++) {
      double wi=weights[i];
      if (wi>0.0) {
	const long double x=(data[i]-wmean)/wsd;
	W+=wi;
	wavg+=(x*x*x*x-wavg)*(wi/W);
      }
    }
    return wavg-3.0;
  }

  /** \brief Compute the kurtosis of data with specified mean
      and standard deviation
      
      This function produces the same results
      as <tt>gsl_stats_wkurtosis()</tt>.
  */
  template<class vec_t, class vec2_t>
    double wvector_kurtosis(size_t n, const vec_t &data, 
			    const vec2_t &weights) {
    double wmean=wvector_mean(n,data,weights);
    double wsd=wvector_stddev(n,data,weights,wmean);
    return wvector_kurtosis(n,data,weights,wmean,wsd);
  }
  //@}

#ifndef DOXYGEN_NO_O2NS
}
#endif

#endif
