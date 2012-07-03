// $Id: error_vector.h,v 1.3 2005-02-22 22:17:35 jwpeterson Exp $

// The libMesh Finite Element Library.
// Copyright (C) 2002-2005  Benjamin S. Kirk, John W. Peterson
  
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
  
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
  
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef __error_vector_h__
#define __error_vector_h__

// C++ includes

// Local Includes
#include "statistics.h"


// Forward Declarations

/**
 * The \p ErrorVector is a specialization of the
 * \p StatisticsVector for error data computed on a finite element
 * mesh.  In general, when computing the error on a mesh only the
 * active elements are considered, but the \p ErrorVector is sized
 * according to the total number of elements in the mesh.  The
 * \p ErrorVector is thus padded with zeros for all the inactive
 * elements, and this must be taken into account when calculating
 * the statistics.  Since the error is a positive quantity this class
 * assumes it contains positive data (i.e. min_val >= 0.).
 *
 * @author Benjamin S. Kirk, 2003.
 */
class ErrorVector : public StatisticsVector<float>
{
  
public:
  
  /**
   * Returns the minimum nonzero value in the data set.
   */
  virtual float minimum() const;

  /**
   * Returns the mean value of the data set. Ignores
   * zero values.
   */
  virtual Real mean() const;
  
  /**
   * Returns the median (e.g. the middle)
   * value of the data set, ignoring zero values.
   * This function modifies the
   * original data by sorting, so it
   * can't be called on const objects.
   * Source: GNU Scientific Library
   */
  virtual Real median();

  /**
   * A const version of the median funtion.
   * Requires twice the memory of original
   * data set but does not change the original.
   */
  virtual Real median() const;

  /**
   * Computes the variance of the data set
   * ignoring zero values.
   * Uses a recurrence relation to prevent
   * data overflow for large sums.
   * Note: The variance is equal to the
   * standard deviation squared.  The variance
   * is normalized by N in this case.
   * Source: GNU Scientific Library
   */
  virtual Real variance() const
  { return this->variance(this->mean()); }

  /**   
   * Computes the variance of the data set
   * (and ignoring zero values)
   * where the \p mean is provided. This is useful
   * for efficiency when you have already calculated
   * the mean. Uses a recurrence relation to prevent
   * data overflow for large sums.
   * Note: The variance is equal to the
   * standard deviation squared.
   * Source: GNU Scientific Library
   */
  virtual Real variance(const Real mean) const;

  /**
   * Returns a vector of unsigned ints which correspond
   * to the indices of every member of the data set
   * below the cutoff value cut ignoring zero values.
   */
  virtual std::vector<unsigned int> cut_below(Real cut) const;

  /**
   * Returns a vector of unsigned ints which correspond
   * to the indices of every member of the data set
   * above the cutoff value cut ignoring zero values.
   */
  virtual std::vector<unsigned int> cut_above(Real cut) const;

  
};


#endif
