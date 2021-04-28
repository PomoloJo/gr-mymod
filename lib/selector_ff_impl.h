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

#ifndef INCLUDED_MYMOD_SELECTOR_FF_IMPL_H
#define INCLUDED_MYMOD_SELECTOR_FF_IMPL_H

#include <mymod/selector_ff.h>

namespace gr {
  namespace mymod {

    class selector_ff_impl : public selector_ff
    {
     private:
     	int d_sum_count;
     	float d_sum0;
        float d_sum1;
        float d_sum2;
        float d_sum3;
        float d_sum4;
      // Nothing to declare in this block.

     public:
      selector_ff_impl();
      ~selector_ff_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace mymod
} // namespace gr

#endif /* INCLUDED_MYMOD_SELECTOR_FF_IMPL_H */

