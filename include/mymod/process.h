/* -*- c++ -*- */
/* 
 * Copyright 2021 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#ifndef INCLUDED_MYMOD_PROCESS_H
#define INCLUDED_MYMOD_PROCESS_H

#include <mymod/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace mymod {

    /*!
     * \brief <+description of block+>
     * \ingroup mymod
     *
     */
    class MYMOD_API process : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<process> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of mymod::process.
       *
       * To avoid accidental use of raw pointers, mymod::process's
       * constructor is in a private implementation
       * class. mymod::process::make is the public interface for
       * creating new instances.
       */
      static sptr make(const std::string &filename);  // , bool flag_save_data
    };

  } // namespace mymod
} // namespace gr

#endif /* INCLUDED_MYMOD_PROCESS_H */

